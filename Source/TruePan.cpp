/*
  ==============================================================================

    TruePan.cpp
    Created: 28 Feb 2016 7:39:11pm
    Author:  Mac

  ==============================================================================
*/

#include "TruePan.h"

#include <math.h>
#include "TruePan.h"

#include <iomanip>

TruePan::TruePan(){}
TruePan::~TruePan(){}


void TruePan::ComputeDelay(float pos, float SR, float lowRange, float highRange)
{
    // Convert to radians.
    //pos = (((pos/(highRange-lowRange))*180)-180)/180*M_PI;
    pos = ((pos-90) / 180) * M_PI;
    
    //TODO:These values must be defined prior to this. Only for test defined here
    float radious = 1.0;//TODO: Abstract if necessary
    
    float xs = cos(pos) * radious;//TODO: Abstract if necessary
    float ys = -sin(pos) * radious;
    
    // 1 = LEFT
    // 2 = RIGHT
    //TODO: This following position must be defined and set prior and in relation to a 'distance between speakers'
    float x1 = -0.5;//TODO: Abstract if necessary
    float x2 = 0.5;
    float y1 = 0.0;
    float y2 = y1;
    
    // Distances from imaginary sound source to imaginary speakers, all imaginary!
    float d1 = sqrt(pow(xs-x1,2)+pow(ys-y1,2));//TODO: Abstract
    float d2 = sqrt(pow(xs-x2,2)+pow(ys-y2,2));
    
    // Number of samples to delay 
    nSamples[0] = (int)(SR * (d1/343));  // LEFT
    nSamples[1] = (int)(SR * (d2/343));  // RIGHT
    
    // Only use as much delay as there is inbetween channels. 
    if(nSamples[0] >= nSamples[1])
    {
        nSamples[0] -= nSamples[1];
        nSamples[1] = 0;
    }
    if(nSamples[1] >= nSamples[0])
    {
        nSamples[1] -= nSamples[0];
        nSamples[0] = 0;
    }
    
}