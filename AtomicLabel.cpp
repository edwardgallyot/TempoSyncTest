//
// Created by edgallyot on 11/11/2021.
//

#include "AtomicLabel.h"


void AtomicLabel::timerCallback ()
{
    label.setText (juce::String (value.load ()), juce::dontSendNotification);

}
AtomicLabel::AtomicLabel (std::atomic<double>& valueToUse) : value (valueToUse)
{
    startTimerHz (60);
    addAndMakeVisible (label);
}
void AtomicLabel::resized ()
{
    label.setBounds (getLocalBounds ());
}
