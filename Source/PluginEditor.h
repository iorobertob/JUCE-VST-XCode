/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.3.0

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_C6909893470D428__
#define __JUCE_HEADER_C6909893470D428__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

/////  I/O  / ///
#include "TruePan.h"
#include "AltLookAndFeel.h"
////////////////

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class TruePan2AudioProcessorEditor  : public AudioProcessorEditor,
<<<<<<< HEAD
                                      public Timer
=======
                                      public Timer,
                                      public SliderListener
>>>>>>> master
{
public:
    //==============================================================================
    TruePan2AudioProcessorEditor (TruePan2AudioProcessor& ownerFilter);
    ~TruePan2AudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void timerCallback() override;
    TruePan2AudioProcessor* getProcessor() const
        {return static_cast <TruePan2AudioProcessor*>(getAudioProcessor());}
<<<<<<< HEAD

    // Define types to use and attach GUI components to parameters in the Value Tree
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

    void sliderDragStarted (Slider* slider) ;//override;
    void sliderDragEnded   (Slider* slider) ;//override;

    void handlePositionChange(Slider* sliderThatWasMoved, float knobPosition);
=======
>>>>>>> master
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void mouseDown (const MouseEvent& e) override;
    void mouseDrag (const MouseEvent& e) override;
    void mouseUp (const MouseEvent& e) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

    AltLookAndFeel altLookAndFeel;                      // Instance of a new GUI interface look and feel clas

    ScopedPointer<SliderAttachment> gainAttachment;
    ScopedPointer<SliderAttachment> sliderAttachment;
    ScopedPointer<ButtonAttachment> invertAttachment;

    float startY;
    float draggedPosition;
    float startPosition;
    float previousAngle;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Slider> panSlider;
    ScopedPointer<Label> label;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TruePan2AudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_C6909893470D428__
