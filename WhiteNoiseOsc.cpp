//
// Created by edgallyot on 11/11/2021.
//

#include "WhiteNoiseOsc.h"

void WhiteNoiseOsc::prepare (double sampleRate, int samplesPerBlock)
{
    d_sampleRate = sampleRate;
    d_samplesPerBlock = samplesPerBlock;

}
void WhiteNoiseOsc::process (juce::AudioBuffer<float>& buffer)
{
    for (auto channel = 0; channel < buffer.getNumChannels(); ++channel){
        for (auto sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            auto* writePointer = buffer.getWritePointer (channel, sample);
            *writePointer = getNextSample();
        }
    }

}
float WhiteNoiseOsc::getNextSample ()
{
    return (random1.nextFloat() * 2.0f) - 1.0f;
}
