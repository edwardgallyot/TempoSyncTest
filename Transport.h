//
// Created by edgallyot on 11/11/2021.
//

#ifndef TEMPOSYNCTEST_TRANSPORT_H
#define TEMPOSYNCTEST_TRANSPORT_H

#include "JuceHeader.h"


class Transport
{
public:
    void prepare (double sampleRate, int maxBlockSize);
    void process (juce::AudioPlayHead* playHead, int numSamples);
    double getPPQPerSample () const;
    std::atomic<double>& getCurrentPosition ();
    std::vector<double>& getPpqPositions ();
    juce::AudioPlayHead::CurrentPositionInfo& getInfo ();

private:
    mutable std::atomic<double> currentPosition {0};
    double samplesInMinute {0.0f};
    std::vector<double> ppqPositions;
    juce::AudioPlayHead::CurrentPositionInfo info;
};


#endif //TEMPOSYNCTEST_TRANSPORT_H
