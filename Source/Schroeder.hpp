//
//  Schroeder.hpp
//
//  Created by Eric Tarr on 2/6/20.
//  Copyright © 2020 Eric Tarr. All rights reserved.
//

#ifndef Schroeder_hpp
#define Schroeder_hpp

#include "FBCF.hpp"
#include "APF.hpp"

using namespace std;

class Schroeder {
    
public:
    
    // Constructor function (special function - no return type, name = Class name)
    Schroeder();
    
    // Destructor
    ~Schroeder();
    
    float processSample(float x, int channel);

    void setFs(float Fs);
    
    void setDiffusionGain(float diffusionGain);
    void setFeedbackGain(float feedbackGain);
    
    void setDepth(float depth);

    
private:
    
    float Fs = 48000.f;
    
    FBCF fbcf1 {1426.f, 0.724f};
    FBCF fbcf2 {1781.f, 1.257f};
    FBCF fbcf3 {1973.f, 0.893f};
    FBCF fbcf4 {2098.f, 1.111f};
    
    APF apf1 {240.f, 0.8321f};
    APF apf2 {82.f, 0.965f};
    
    float feedbackGain = 0.5f;
    float diffusionGain = 0.5f;
    
    float depth = 10.0f; // percentage of intensity, control amp of LFO
    
};



#endif /* Schroeder_hpp */
