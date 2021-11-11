//
// Created by edgallyot on 11/11/2021.
//

#ifndef TEMPOSYNCTEST_WHITENOISEOSC_H
#define TEMPOSYNCTEST_WHITENOISEOSC_H

#include "JuceHeader.h"


class WhiteNoiseOsc
{
public:
    void prepare (double sampleRate, int samplesPerBlock);
    void process (juce::AudioBuffer<float>& buffer);
    float getNextSample();
private:
    juce::Random random1;
    double d_sampleRate;
    int d_samplesPerBlock;
};


#endif //TEMPOSYNCTEST_WHITENOISEOSC_H
