#include "TempoSyncProcessor.h"
#include "TempoSyncEditor.h"


//==============================================================================
TempoSyncProcessor::TempoSyncProcessor ()
        : AudioProcessor (BusesProperties ()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
                                  .withInput ("Input", juce::AudioChannelSet::stereo (), true)
#endif
                                  .withOutput ("Output", juce::AudioChannelSet::stereo (), true)
#endif
)
{
    addParameter (subdivisionParameter);
}

TempoSyncProcessor::~TempoSyncProcessor ()
{
}

//==============================================================================
const juce::String TempoSyncProcessor::getName () const
{
    return JucePlugin_Name;
}

bool TempoSyncProcessor::acceptsMidi () const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool TempoSyncProcessor::producesMidi () const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool TempoSyncProcessor::isMidiEffect () const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double TempoSyncProcessor::getTailLengthSeconds () const
{
    return 0.0;
}

int TempoSyncProcessor::getNumPrograms ()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int TempoSyncProcessor::getCurrentProgram ()
{
    return 0;
}

void TempoSyncProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused (index);
}

const juce::String TempoSyncProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}

void TempoSyncProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}

//==============================================================================
void TempoSyncProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::ignoreUnused (sampleRate, samplesPerBlock);
    transport.prepare (sampleRate, samplesPerBlock);
    whiteNoiseOsc.prepare (sampleRate, samplesPerBlock);

}

void TempoSyncProcessor::releaseResources ()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool TempoSyncProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet () != juce::AudioChannelSet::mono ()
        && layouts.getMainOutputChannelSet () != juce::AudioChannelSet::stereo ())
        return false;

    // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet () != layouts.getMainInputChannelSet ())
        return false;
#endif

    return true;
#endif
}

void TempoSyncProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                       juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused (midiMessages);
    transport.process (getPlayHead (), buffer.getNumSamples ());
    juce::AudioPlayHead::CurrentPositionInfo* info_p = &transport.getInfo ();

    auto currentSubDivision = subdivisionParameter->getDivisionPPQ ();
    auto halfCurrentSubDivision = currentSubDivision / 2.0f;
    for (auto sample = 0; sample < buffer.getNumSamples (); ++sample)
    {

        for (auto channel = 0; channel < buffer.getNumChannels (); ++channel)
        {
            auto relativePosition = fmod (transport.getPpqPositions ()[sample],
                                          subdivisionParameter->getDivisionPPQ ());
            float sampleVal = 0.f;

            if (isNoiseOn (halfCurrentSubDivision, relativePosition))
                sampleVal = whiteNoiseOsc.getNextSample();

            auto* writePointer = buffer.getWritePointer (channel, sample);

            *writePointer = sampleVal;

            if (info_p->isPlaying)
                *writePointer *= 1.0f;
            else
                *writePointer *= 0.0f;
        }
    }
    buffer.applyGain (0.1f);

    //whiteNoiseOsc.process (buffer);

}
bool TempoSyncProcessor::isNoiseOn (double halfCurrentSubDivision, double relativePosition) const
{
    return relativePosition < halfCurrentSubDivision;
}

//==============================================================================
bool TempoSyncProcessor::hasEditor () const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* TempoSyncProcessor::createEditor ()
{
    return new TempoSyncEditor (*this);
}

//==============================================================================
void TempoSyncProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::ignoreUnused (destData);
}

void TempoSyncProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    juce::ignoreUnused (data, sizeInBytes);
}
Transport& TempoSyncProcessor::getTransport ()
{
    return transport;
}


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter ()
{
    return new TempoSyncProcessor ();
}
