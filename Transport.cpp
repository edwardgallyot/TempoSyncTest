//
// Created by edgallyot on 11/11/2021.
//

#include "Transport.h"

void Transport::prepare (double sampleRate, int maxBlockSize)
{
    samplesInMinute = sampleRate * 60.0;
    ppqPositions.resize (maxBlockSize);

}
void Transport::process (juce::AudioPlayHead* playHead, int numSamples)
{
    if (playHead != nullptr)
        playHead->getCurrentPosition (info);

    auto ppqPerSample = getPPQPerSample ();
    double offset = 0.0;
    for (auto sample = 0; sample < numSamples; ++sample)
    {

        ppqPositions[sample] = info.ppqPosition + offset;
        offset += ppqPerSample;
    }
    currentPosition.store (info.ppqPosition + offset);



}
double Transport::getPPQPerSample () const
{
    auto samplesPerBeat = samplesInMinute / info.bpm;
    return 1.0 / samplesPerBeat;
}
std::atomic<double>& Transport::getCurrentPosition ()
{
    return currentPosition;
}
std::vector<double>& Transport::getPpqPositions ()
{
    return ppqPositions;
}
juce::AudioPlayHead::CurrentPositionInfo& Transport::getInfo ()
{
    return info;
}
