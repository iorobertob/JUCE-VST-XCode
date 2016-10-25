/*
  ==============================================================================

    TruePan.h
    Created: 28 Feb 2016 7:39:11pm
    Author:  Mac

  ==============================================================================
*/

#ifndef TRUEPAN_H_INCLUDED
#define TRUEPAN_H_INCLUDED


/*Volume-Normalized Stereo Width Control, contributed by Michael Gruhn to the 
MusicDSP Source Code Archive: http://musicdsp.org/showArchiveComment.php?ArchiveID=256
'width' is the stretch factor of the stereo field:
width < 1: decrease in stereo width
width = 1: no change
width > 1: increase in stereo width
width = 0: mono*/
class TruePan
{
public:
    TruePan();
    ~TruePan();

    //Parameters
    void SetWidth(float width); 
    //float* ComputeDelay(float pos, float SR);
    void ComputeDelay(float pos, float SR);
    int nSamples[2] = {0};
    
    //int samplesL = 0;
    //int samplesR = 0;
    
    float Getwidth(void){return m_width;};
    float GetDelay(void){return m_delay;};

    //Use
    void ClockProcess(float* LeftSample, float* RightSample); 

private:
    float m_width, sumGain, diffGain, m_delay, m_distance;
};



#endif  // TRUEPAN_H_INCLUDED
