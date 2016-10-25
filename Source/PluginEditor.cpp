/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.2.4

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
TruePan_0_01AudioProcessorEditor::TruePan_0_01AudioProcessorEditor (TruePan_0_01AudioProcessor& ownerFilter)
    : AudioProcessorEditor(ownerFilter)
{
    //[Constructor_pre] You can add your own custom stuff here..
    startTimer(200);//Starts the time with interval of 200ms
    setLookAndFeel(&altLookAndFeel);
    //[/Constructor_pre]

    addAndMakeVisible (slider = new Slider ("Pan Slider"));
    slider->setRange (0, 256, 0.1);
    slider->setSliderStyle (Slider::Rotary);
    slider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    slider->setColour (Slider::backgroundColourId, Colours::grey);
    slider->setColour (Slider::trackColourId, Colour (0xffdd2929));
    slider->setColour (Slider::rotarySliderFillColourId, Colour (0xff000051));
    slider->setColour (Slider::rotarySliderOutlineColourId, Colour (0xff832c2c));
    slider->setColour (Slider::textBoxTextColourId, Colours::white);
    slider->setColour (Slider::textBoxBackgroundColourId, Colour (0x002c8cff));
    slider->setColour (Slider::textBoxHighlightColourId, Colour (0xff1111ee));
    slider->setColour (Slider::textBoxOutlineColourId, Colour (0x00a83838));
    slider->addListener (this);

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Ldelay\n")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (Label::textColourId, Colours::white);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("\n"
                                           "Rdelay")));
    label2->setFont (Font (15.00f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (Label::textColourId, Colours::white);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]

    //[/UserPreSize]

    setSize (250, 260);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

TruePan_0_01AudioProcessorEditor::~TruePan_0_01AudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    slider = nullptr;
    label = nullptr;
    label2 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void TruePan_0_01AudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff302222));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void TruePan_0_01AudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    slider->setBounds (0, 0, 250, 260);
    label->setBounds (0, 216, 72, 32);
    label2->setBounds (184, 216, 64, 32);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void TruePan_0_01AudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]

    mTruePan.ComputeDelay(sliderThatWasMoved->getValue(), getProcessor()->mSampleRate);


    if(sliderThatWasMoved->getName() == "Pan Slider"){

        getProcessor()->delaySamplesKnobPosPtr[0] = mTruePan.nSamples[0];//LEFT
        getProcessor()->delaySamplesKnobPosPtr[1] = mTruePan.nSamples[1];//RIGHT

        label ->setText(std::to_string(getProcessor()-> delaySamplesKnobPosPtr[0]), sendNotification);
        label2->setText(std::to_string(getProcessor()-> delaySamplesKnobPosPtr[1]), sendNotification);
    }

    //[/UsersliderValueChanged_Pre]



    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void TruePan_0_01AudioProcessorEditor::timerCallback()
{
        //TruePan_0_01AudioProcessor* ourProcessor = getProcessor();
        //exchange any data you want between UI elements and the Plugin "our Processor"
}



//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="TruePan_0_01AudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer"
                 constructorParams="TruePan_0_01AudioProcessor&amp; ownerFilter"
                 variableInitialisers="AudioProcessorEditor(ownerFilter)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="0"
                 initialWidth="250" initialHeight="260">
  <BACKGROUND backgroundColour="ff302222"/>
  <SLIDER name="Pan Slider" id="4ccd8bf579090d8f" memberName="slider" virtualName=""
          explicitFocusOrder="0" pos="0 0 250 260" bkgcol="ff808080" trackcol="ffdd2929"
          rotarysliderfill="ff000051" rotaryslideroutline="ff832c2c" textboxtext="ffffffff"
          textboxbkgd="2c8cff" textboxhighlight="ff1111ee" textboxoutline="a83838"
          min="0" max="256" int="0.10000000000000000555" style="Rotary"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <LABEL name="new label" id="645c2efb17df879a" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="0 216 72 32" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="Ldelay&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="c37238f6a08fb7ae" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="184 216 64 32" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="&#10;Rdelay" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
