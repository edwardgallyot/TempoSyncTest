#pragma once

#include "TempoSyncProcessor.h"
#include "AtomicLabel.h"

//==============================================================================
class TempoSyncEditor  : public juce::AudioProcessorEditor
{
public:
    explicit TempoSyncEditor (TempoSyncProcessor&);
    ~TempoSyncEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TempoSyncProcessor& processorRef;
    //AtomicLabel atomicLabel;
    juce::GenericAudioProcessorEditor editor;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TempoSyncEditor)
};
