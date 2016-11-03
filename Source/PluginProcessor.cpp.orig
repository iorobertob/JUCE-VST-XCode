/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
// Base initializer for the constructor with parameters
TruePan2AudioProcessor::TruePan2AudioProcessor(): parameters(*this, nullptr)
{
    
    parameters.createAndAddParameter ("angle",          // paremeterID
                                      "Angle",          // parameter name
                                      String(),         // parameter label (suffix)
                                      NormalisableRange<float>(-90.0f, 90.0f), // range
                                      0.0f,             // default value
                                      nullptr,          // conversion function
                                      nullptr);         // conversion function
    
    parameters.createAndAddParameter ("gain",           // paremeterID
                                      "Gain",           // parameter name
                                      String(),         // parameter label (suffix)
                                      NormalisableRange<float>(0.0f, 2.0f), // range
                                      1.0f,             // default value
                                      nullptr,          // conversion function
                                      nullptr);         // conversion function
                                      
    parameters.createAndAddParameter ("invertPhase", "Invert Phase", String(),
                                      NormalisableRange<float> (0.0f, 1.0f, 1.0f), 0.0f,
                                      [](float value)
                                      {
                                            // Lambda function - value to text function
                                            return value < 0.5 ? "Normal" : "Inverted";
                                      },
                                      [](const String& text)
                                      {
                                            // Lambda function - text to value function
                                            if (text == "Normal")    return 0.0f;
                                            if (text == "Inverted")  return 1.0f;
                                            return 0.0f;
                                      });
    
    parameters.createAndAddParameter ("swapChannel", "Swap Channels", String(),
                                      NormalisableRange<float> (0.0f, 1.0f, 1.0f), 0.0f,
                                      [](float value)
                                      {
                                          // Lambda function - value to text function
                                          return value < 0.5 ? "Normal" : "Inverted";
                                      },
                                      [](const String& text)
                                      {
                                          // Lambda function - text to value function
                                          if (text == "Normal")    return 0.0f;
                                          if (text == "Inverted")  return 1.0f;
                                          return 0.0f;
                                      });

                                    
          
    parameters.addParameterListener("angle",this);
    parameters.addParameterListener("gain", this);
    parameters.addParameterListener("invertPhase",this);
    
    // Initialising the ValueTree object    
    parameters.state = ValueTree(Identifier ("APVTSTruePan"));
       
}

TruePan2AudioProcessor::~TruePan2AudioProcessor()
{
}

//==============================================================================


//=====================================   I   /    O====================================
//   ADD CODE HERE 
void TruePan2AudioProcessor::parameterChanged(const String& id, float newValue){
    
        if (id == "angle"){
            // Process the angle value and compute delay for each channel
            truePanInProcessor.ComputeDelay(newValue,       // Current value of the slider
                                            mSampleRate,    // SR
                                            -90.0f,         // Low value of the slider
                                             90.0f);        // High value of the slider
            
            // Assign delay from the previous function to the values used in the ProcessBlock
            delaySamplesKnobPosPtr[0] = truePanInProcessor.nSamples[0];//LEFT  channel
            delaySamplesKnobPosPtr[1] = truePanInProcessor.nSamples[1];//RIGHT channel
        }
        if (id == "gain"){
            // Do something
        }
        if (id == "invertPhase"){
            // Do something
        }
    
}
//=====================================   I   /    O====================================

const String TruePan2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TruePan2AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TruePan2AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double TruePan2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TruePan2AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TruePan2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void TruePan2AudioProcessor::setCurrentProgram (int index)
{
}

const String TruePan2AudioProcessor::getProgramName (int index)
{
    return String();
}

void TruePan2AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void TruePan2AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    mSampleRate = getSampleRate();
    
    // Based on Audio Effects - Reiss
    delayBuffer_.setSize(2, 1024);
    delayBuffer_.clear ();
    
    tempSwapBuffer.setSize(1,1024);
    tempSwapBuffer.clear();
    
    // Initialise gain and phase parameters
    const float phase   = *parameters.getRawParameterValue("invertPhase") < 0.5f ? 1.0f : -1.0f;
    previousGain        = *parameters.getRawParameterValue("gain") * phase;
}

void TruePan2AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TruePan2AudioProcessor::setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet)
{
    // Reject any bus arrangements that are not compatible with your plugin

    const int numChannels = preferredSet.size();

   #if JucePlugin_IsMidiEffect
    if (numChannels != 0)
        return false;
   #elif JucePlugin_IsSynth
    if (isInput || (numChannels != 1 && numChannels != 2))
        return false;
   #else
    if (numChannels != 1 && numChannels != 2)
        return false;

    if (! AudioProcessor::setPreferredBusArrangement (! isInput, bus, preferredSet))
        return false;
   #endif

    return AudioProcessor::setPreferredBusArrangement (isInput, bus, preferredSet);
}
#endif

void TruePan2AudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    
    const int numberOfChannels =  getTotalNumInputChannels();
    
    // Get values from the State Tree parameters 
    const float phase       = *parameters.getRawParameterValue ("invertPhase") < 0.5f ? 1.0f : -1.0f;
    const float swapChannel = *parameters.getRawParameterValue ("swapChannel") < 0.5f ? 0.0f : 1.0f;
    const float currentGain = *parameters.getRawParameterValue ("gain") * phase;
    
    if (numberOfChannels == 2)
    {
        
        for (int channel = 0; channel < numberOfChannels; ++channel)
        {
            
            samples = buffer.getWritePointer(channel);
            
            // delayData is the circular buffer for implementing the delay
            delayedData = delayBuffer_.getWritePointer(
                                jmin( channel, 
                                delayBuffer_.getNumChannels() - 1));
            
                                
            for (int i = 0; i < buffer.getNumSamples(); ++i)
            {
                // position in the delay buffer, where to store: current position in buffer + current delay in samples
                currentDelayInSamples = positionInCurrentBuffer[channel] + pastDelayInSamples[channel];
                
                if (currentDelayInSamples >  1023)
                {   // reset off limits
                    currentDelayInSamples -= 1024;
                }
                
                // DELAY IS INCREASING - Interpolation ==========================================================================
                
                // Only every 100 samples, not to have all artifacts concentrated
                if ((delaySamplesKnobPos[channel] > pastDelayInSamples[channel]) && (i%100 == 0)){
                    
                    prevInput[channel] = (samples[i]+prevInputs[channel][4])/2;
                    // INPUT
                    // one position more since the delay is getting longer, one sample at the time
                    if ((currentDelayInSamples + 1) > 1023){
                        
                        delayedData[0] = samples [i]; // y4
                        
                    }
                    else{
                        delayedData[currentDelayInSamples + 1]= samples [i]; // y4
                    }
                    
                    // Lagrange Interpolation 
                    // y3 = -0.25y0 - y1 + 1.5y2 + 0.25y4
                    delayedData[currentDelayInSamples]        = (0.25*prevInputs[channel][2]) - (prevInputs[channel][3])
                                                + (1.5*prevInputs[channel][4]) + (0.25*samples[i]);
                    
                    // Move towards delay goal. Make a line to smooth the transition
                    pastDelayInSamples[channel]++;  
                    
                    // Saving current input for next average. saving the previous 3 inputs 
                    prevInputs[channel][0] = prevInputs[channel][1];
                    prevInputs[channel][1] = prevInputs[channel][2]; 
                    prevInputs[channel][2] = prevInputs[channel][3]; 
                    prevInputs[channel][3] = delayedData[currentDelayInSamples]; 
                    prevInputs[channel][4] = samples[i]; 
                    
                    
                }//==============================================================================================================
                
                // DELAY IS DECREASING - Average  ===============================================================================
                else if ((delaySamplesKnobPos[channel] < pastDelayInSamples[channel])&& (i%100 == 0)){
                    
                    // INPUT
                    // we update one position shorter, since delay is getting shorter.
                    delayedData[currentDelayInSamples-1]    = samples[i];
                    
                     // INPUT
                    // The previous sample is modified to fit an interpolated curve
                    delayedData[currentDelayInSamples-2]    = (0.25*prevInputs[channel][0]) - (prevInputs[channel][1])
                                                + (1.5*prevInputs[channel][2]) + (0.25*samples[i]);
                                                
                    // Move towards delay goal. 
                    pastDelayInSamples[channel]--; 
                    
                    // Saving current input for next average.
                    prevInputs[channel][3] = delayedData[currentDelayInSamples-2] ;  
                    prevInputs[channel][4] = samples[i];
                    
                }//==============================================================================================================
                
                // DELAY IS THE SAME ============================================================================================
                else{
                    // INPUT
                    // put current sample in the 'delay' position in the buffer
                    delayedData[currentDelayInSamples]       = samples[i];
                    
                    // Save previous inputs for future interpolations
                    prevInputs[channel][0] = prevInputs[channel][1];// 
                    prevInputs[channel][1] = prevInputs[channel][2];// 
                    prevInputs[channel][2] = prevInputs[channel][3];// 
                    prevInputs[channel][3] = prevInputs[channel][4];// 
                    prevInputs[channel][4] = samples[i];
                }//==============================================================================================================
                
                // OUTPUT =======================================================================================================
                // Put the output in the stream buffer "samples", which is the delayed data by the num of samples computed earlier
                samples[i]  = delayedData[positionInCurrentBuffer[channel]];
                //===============================================================================================================
                
                
                
                // Increase position in delay buffer for output, this only go around the buffer
                positionInCurrentBuffer[channel]++;
                if(positionInCurrentBuffer[channel] > 1023)
                {   // reset off limits
                    positionInCurrentBuffer[channel]= 0;
                }
            
            }
             
        }
        // APPLY GAIN AND INVERSION =====================================================================================
        if (currentGain == previousGain)
        {
            buffer.applyGain (currentGain);
        }
        else
        {
            buffer.applyGainRamp (0, buffer.getNumSamples(), previousGain, currentGain);
            previousGain = currentGain;
        }
        // ==============================================================================================================
        
        // SWAP  CHANNELS  ==============================================================================================
        if (swapChannel == 1)
        {
            // Invert channels
            tempSwapBuffer.copyFrom(0,0,buffer,1,0,buffer.getNumSamples());
            buffer.copyFrom(1, 0, buffer, 0, 0, buffer.getNumSamples());
            buffer.copyFrom(0, 0, tempSwapBuffer,0,0, buffer.getNumSamples());
            
        }// =============================================================================================================
    }
}

//==============================================================================
bool TruePan2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TruePan2AudioProcessor::createEditor()
{
    return new TruePan2AudioProcessorEditor (*this);
}

//==============================================================================
void TruePan2AudioProcessor::getStateInformation (MemoryBlock& destData)  
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    ScopedPointer<XmlElement> xml (parameters.state.createXml());
    copyXmlToBinary (*xml, destData);
    
}

void TruePan2AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    
    if (xmlState != nullptr)
        if (xmlState->hasTagName (parameters.state.getType()))
            parameters.state = ValueTree::fromXml (*xmlState);
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TruePan2AudioProcessor();
}


