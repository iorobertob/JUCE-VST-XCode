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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...

//[/MiscUserDefs]

//==============================================================================
TruePan2AudioProcessorEditor::TruePan2AudioProcessorEditor (TruePan2AudioProcessor& ownerFilter)
    : AudioProcessorEditor(ownerFilter)
{
    //[Constructor_pre] You can add your own custom stuff here..
    startTimer(200);                    // Starts the time with interval of 200ms
    setLookAndFeel(&altLookAndFeel);    // Change the look and feel to our custom drawn shape
    //[/Constructor_pre]

    addAndMakeVisible (panSlider = new Slider ("Pan Slider"));
    panSlider->setRange (0, 256, 0.1);
    panSlider->setSliderStyle (Slider::Rotary);
    panSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    panSlider->setColour (Slider::trackColourId, Colour (0xaad00000));
    panSlider->setColour (Slider::rotarySliderFillColourId, Colour (0x7f00008b));
    panSlider->setColour (Slider::rotarySliderOutlineColourId, Colour (0x66850808));

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("0.0")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (Label::textColourId, Colours::white);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    // Attach the "angle" parameter to the main slider
    sliderAttachment =  new SliderAttachment (getProcessor()->parameters, "angle", *panSlider);
    //[/UserPreSize]

    setSize (250, 260);


    //[Constructor] You can add your own custom stuff here..
    addMouseListener(this, true);
    //[/Constructor]
}

TruePan2AudioProcessorEditor::~TruePan2AudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    panSlider = nullptr;
    label = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TruePan2AudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff200430));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TruePan2AudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    panSlider->setBounds (0, 0, 250, 260);
    label->setBounds (104, 240, 40, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void TruePan2AudioProcessorEditor::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
    startY = e.y;
    startPosition = draggedPosition;
    //panSlider->setValue(draggedPosition);
    //[/UserCode_mouseDown]
}

void TruePan2AudioProcessorEditor::mouseDrag (const MouseEvent& e)
{
    //[UserCode_mouseDrag] -- Add your code here...
    // Divided by 2 to slow down the movement
    draggedPosition = startPosition+((startY-e.y)/2);
    if (draggedPosition > 90){
        draggedPosition = 90;
    }
    if (draggedPosition < -90){
        draggedPosition = -90;
    }
    panSlider->setValue(draggedPosition);
    handlePositionChange(panSlider, draggedPosition);
    //[/UserCode_mouseDrag]
}

void TruePan2AudioProcessorEditor::mouseUp (const MouseEvent& e)
{
    //[UserCode_mouseUp] -- Add your code here...
    //[/UserCode_mouseUp]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void TruePan2AudioProcessorEditor::handlePositionChange(Slider* sliderThatWasMoved, float knobPosition){

    if(sliderThatWasMoved->getName() == "Pan Slider"){

        // Only update the label indicating the current angle
        int angle = int(knobPosition);
        label ->setText(std::to_string(angle), sendNotification);
    }
}

void TruePan2AudioProcessorEditor::timerCallback()
{
    //exchange any data you want between UI elements and the Plugin "our Processor"

    // Update the reference position of the slider
    draggedPosition = panSlider->getValue();

    // Check if something changed in the Processor, in this case the angle
    if (previousAngle != *getProcessor()->parameters.getRawParameterValue("angle")){
        //This works to update the value in the GUI
        previousAngle = *getProcessor()->parameters.getRawParameterValue("angle");
        handlePositionChange(panSlider, previousAngle);

    }


}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TruePan2AudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer"
                 constructorParams="TruePan2AudioProcessor&amp; ownerFilter" variableInitialisers="AudioProcessorEditor(ownerFilter)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="250" initialHeight="260">
  <METHODS>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
    <METHOD name="mouseDrag (const MouseEvent&amp; e)"/>
    <METHOD name="mouseUp (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ff200430"/>
  <SLIDER name="Pan Slider" id="8718d971245a3757" memberName="panSlider"
          virtualName="" explicitFocusOrder="0" pos="0 0 250 260" trackcol="aad00000"
          rotarysliderfill="7f00008b" rotaryslideroutline="66850808" min="0"
          max="256" int="0.10000000000000000555" style="Rotary" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="0"/>
  <LABEL name="new label" id="972994439b8f37cd" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="104 240 40 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="0.0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
