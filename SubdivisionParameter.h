//
// Created by edgallyot on 11/11/2021.
//

#ifndef TEMPOSYNCTEST_SUBDIVISIONPARAMETER_H
#define TEMPOSYNCTEST_SUBDIVISIONPARAMETER_H

#include "JuceHeader.h"

class SubdivisionParameter : public juce::AudioParameterChoice
{
public:
    SubdivisionParameter();
    juce::StringArray getChoices();
    double getDivisionPPQ();


private:
    

};


#endif //TEMPOSYNCTEST_SUBDIVISIONPARAMETER_H
