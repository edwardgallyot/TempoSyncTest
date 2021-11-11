#include "TempoSyncProcessor.h"
#include "TempoSyncEditor.h"

//==============================================================================
TempoSyncEditor::TempoSyncEditor (TempoSyncProcessor& processorToUse)
        : AudioProcessorEditor (&processorToUse), processorRef (processorToUse), atomicLabel (processorToUse.currentPosition)
{
    juce::ignoreUnused (processorRef);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

TempoSyncEditor::~TempoSyncEditor ()
{
}

//==============================================================================
void TempoSyncEditor::paint (juce::Graphics& g)
{
//     (Our component is opaque, so we must completely fill the background with a solid colour)
    addAndMakeVisible (atomicLabel);
}

void TempoSyncEditor::resized ()
{
    atomicLabel.setBounds(getLocalBounds());
}
