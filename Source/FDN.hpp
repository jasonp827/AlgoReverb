//
//  FDN.hpp
//
//  Created by Eric Tarr on 2/6/20.
//  Copyright © 2020 Eric Tarr. All rights reserved.
//

#ifndef FDN_hpp
#define FDN_hpp
#include "FractionalDelay.hpp"

using namespace std;

class FDN {
    
public:
    
    // Constructor function (special function - no return type, name = Class name)
    FDN();
    
    // Destructor
    ~FDN();
    
    float processSample(float x, int channel);

    void setFs(float Fs);
    
    void setTime(float timeValue);
    
    void setDepth(float depth);

    
private:
    
    float Fs = 48000.f;
    
    FractionalDelay fractionalDelay1 {1571.f, 0.7f};
    FractionalDelay fractionalDelay2 {2053.f, 0.9f};
    FractionalDelay fractionalDelay3 {2719.f, 1.1f};
    FractionalDelay fractionalDelay4 {3463.f, 1.3f};
    
    float feedbackGain = 0.5f;
    
    float fb1[2] = {0.f};
    float fb2[2] = {0.f};
    float fb3[2] = {0.f};
    float fb4[2] = {0.f};
    
    float depth = 10.0f; // percentage of intensity, control amp of LFO
    
};



#endif /* FDN_hpp */
