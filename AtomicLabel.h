//
// Created by edgallyot on 11/11/2021.
//

#ifndef TEMPOSYNCTEST_ATOMICLABEL_H
#define TEMPOSYNCTEST_ATOMICLABEL_H
#include "JuceHeader.h"
#include <atomic>

class AtomicLabel : public juce::Component, juce::Timer
{
public:
    AtomicLabel (std::atomic<double>& valueToUse);
    void resized() override;
    void timerCallback () override;
    juce::Label label;
    std::atomic<double>& value;
};


#endif //TEMPOSYNCTEST_ATOMICLABEL_H
