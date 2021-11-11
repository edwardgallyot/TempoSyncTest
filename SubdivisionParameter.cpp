//
// Created by edgallyot on 11/11/2021.
//

#include "SubdivisionParameter.h"

SubdivisionParameter::SubdivisionParameter () :
        juce::AudioParameterChoice ("Subdivision", "Subdivision", getChoices(), 2)
{

}


juce::StringArray SubdivisionParameter::getChoices ()
{
    return {"1/1", "1/2", "1/4", "1/8", "1/16"};
}

double SubdivisionParameter::getDivisionPPQ ()
{
    switch (getIndex ())
    {
        case 0:
            return 4.0f;
        case 1:
            return 2.0f;
        case 2:
            return 1.0f;
        case 3:
            return 0.5f;
        case 4:
            return 0.25f;
    }
    return 1.0;
}
