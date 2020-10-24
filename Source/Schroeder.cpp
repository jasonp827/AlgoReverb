//
//  Schroeder.cpp
//
//  Created by Eric Tarr on 2/6/20.
//  Copyright © 2020 Eric Tarr. All rights reserved.
//

#include "Schroeder.hpp"


Schroeder::Schroeder()
{
 //   fractionalDelay1.setDelaySamples(1789.f);
 //   fractionalDelay2.setDelaySamples(2281.f);
}

// Destructor
Schroeder::~Schroeder(){
}


float Schroeder::processSample(float x, int channel)
{
    float y;
    
    float outFBCF1 = fbcf1.processSample(x, channel);
    float outFBCF2 = fbcf2.processSample(x, channel);
    float outFBCF3 = fbcf3.processSample(x, channel);
    float outFBCF4 = fbcf4.processSample(x, channel);
    
    float inAPF1 = outFBCF1 + outFBCF2 + outFBCF3 + outFBCF4;
    
    float outAPF1 = apf1.processSample(inAPF1, channel);

    y = apf2.processSample(outAPF1, channel);
    
    return y;
}

void Schroeder::setFs(float Fs){
    this->Fs = Fs;
    fbcf1.setFs(Fs);
    fbcf2.setFs(Fs);
    fbcf3.setFs(Fs);
    fbcf4.setFs(Fs);
    
    apf1.setFs(Fs);
    apf2.setFs(Fs);

}

void Schroeder::setFeedbackGain(float feedbackGain)
{

    this->feedbackGain = feedbackGain;
    fbcf1.setFeedbackGain(feedbackGain);
    fbcf2.setFeedbackGain(feedbackGain);
    fbcf3.setFeedbackGain(feedbackGain);
    fbcf4.setFeedbackGain(feedbackGain);
    
    apf1.setFeedbackGain(feedbackGain);
    apf2.setFeedbackGain(feedbackGain);
    
}

void Schroeder::setDiffusionGain(float diffusionGain)
{

    this->diffusionGain = diffusionGain;
    
    apf1.setFeedbackGain(diffusionGain);
    apf2.setFeedbackGain(diffusionGain);
    
}


void Schroeder::setDepth(float depth){

    this->depth = depth;
    fbcf1.setDepth(depth);
    fbcf2.setDepth(depth);
    fbcf3.setDepth(depth);
    fbcf4.setDepth(depth);
    
    apf1.setDepth(depth);
    apf2.setDepth(depth);
    
    
}
