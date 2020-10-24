//
//  FBCF.cpp
//
//  Created by Eric Tarr on 2/6/20.
//  Copyright © 2020 Eric Tarr. All rights reserved.
//

#include "FBCF.hpp"


FBCF::FBCF()
{
 //   fractionalDelay1.setDelaySamples(1789.f);
 //   fractionalDelay2.setDelaySamples(2281.f);
}

 FBCF::FBCF(float delay, float speed)
{
    fractionalDelay.setDelaySamples(delay);
    fractionalDelay.setSpeed(speed);
}

// Destructor
FBCF::~FBCF(){
}


float FBCF::processSample(float x, int channel)
{
    float y;
    
    float inDL1 = x + (-feedbackGain) * fb1[channel];
    
    float outDL1 = fractionalDelay.processSample(inDL1, channel);
    
    y = outDL1;
    
    fb1[channel] = outDL1;
    
    return y;
}

void FBCF::setFs(float Fs){
    this->Fs = Fs;
    fractionalDelay.setFs(Fs);

}

void FBCF::setFeedbackGain(float feedbackGain)
{

    this->feedbackGain = feedbackGain;
}


void FBCF::setDepth(float depth){

    this->depth = depth;
    fractionalDelay.setDepth(depth);
}
