/*
  ==============================================================================

    TruePan.h
    Created: 28 Feb 2016 7:39:11pm
    Author:  Mac

  ==============================================================================
*/

#ifndef TRUEPAN_H_INCLUDED
#define TRUEPAN_H_INCLUDED


class TruePan
{
public:
    TruePan();
    ~TruePan();
    
    // Function to compute delay in each channel depending on angle of knob
    void ComputeDelay(float pos, float SR, float lowRange, float highRange);
    
    // Placeholder for the delays in number of samples for each channel
    int nSamples[2] = {0};

private:
    float m_delay;
};



#endif  // TRUEPAN_H_INCLUDED
