/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "TruePan.h"

#include <array>


//==============================================================================
/**
*/
class TruePan2AudioProcessor  : public AudioProcessor,
                                public AudioProcessorValueTreeState::Listener
{
public:

    ///////// I / O Patterns ///////////////////////////////////////////////////////
     
    // Positions and new delay to address a buffer
    int positionInCurrentBuffer[2]  = {0}; 
    int currentDelayInSamples       =  0; 
    int pastDelayInSamples[2]       = {0};   
    
    // To Store values and create interpolations 
    // TODO: see if can be merged into one single buffer
    float prevInput[2]              = {0};
    float prevInputs[2][5]          = {0};
    
    // To smooth the gain changes with a ramp
    float previousGain;                    
     
    // Used to compute delay in samples from the know position using TruePan class
    // TODO: make without pointer?
    int  delaySamplesKnobPos[2]     = {0};
    int* delaySamplesKnobPosPtr     = delaySamplesKnobPos;
    
    // This is where the input samples are put
    float* samples;
    
    // In case of channel swap
    float* tempSamples1;
    float* tempSamples2;
    
    // The circular buffer for the delayed data
    float* delayedData;
    
    // Placeholder for Sample Rate 
    float mSampleRate;
    
    AudioProcessorValueTreeState parameters;// Store values through sessions 
    
    ///////// I / O Patterns ///////////////////////////////////////////////////////
    
    //==============================================================================
    TruePan2AudioProcessor();
    ~TruePan2AudioProcessor();
    
    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet) override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //=====================================   I   /    O====================================
    void parameterChanged(const String& id, float newValue)override;
    //=====================================   I   /    O====================================
    

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TruePan2AudioProcessor)
    
    // I/O //////////////////////////////// I/O //////////////////////////////
    
    AudioSampleBuffer delayBuffer_;         // Handle the Audio delayed data. Dedicated buffer
    AudioSampleBuffer tempSwapBuffer;       // To swap channels
    TruePan truePanInProcessor;             // Instance of the delay computation class
    
    // I/O //////////////////////////////// I/O //////////////////////////////
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
