/*
  ==============================================================================

    altLookAndFeel.h
    Created: 24 Oct 2016 10:09:27pm
    Author:  Mac

  ==============================================================================
*/

#ifndef ALTLOOKANDFEEL_H_INCLUDED
#define ALTLOOKANDFEEL_H_INCLUDED

class AltLookAndFeel : public LookAndFeel_V3
{
public:
    AltLookAndFeel()
    {
        setColour (Slider::rotarySliderFillColourId, Colours::red);
        
    }
    
    // Create a custom Knob, imported from an SVG file created in Adobe Illustrator usint the SVG Path Helper
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                           const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
    {
        g.setColour (Colours::darkblue);
        
        static const unsigned char pathData[] = { 110,109,117,19,123,67,203,161,84,67,98,117,19,123,67,18,131,129,67,238,92,67,67,182,179,166,67,117,19,39,67,230,80,148,67,98,193,202,6,67,188,169,126,67,234,38,166,66,19,131,129,67,234,38,166,66,204,161,84,67,98,234,38,166,66,114,61,38,67,47,29,6,67,
26,36,43,67,117,19,39,67,204,161,0,67,98,6,129,67,67,164,240,183,66,117,19,123,67,113,61,38,67,117,19,123,67,203,161,84,67,99,109,45,114,228,66,193,170,80,67,98,131,64,228,66,220,249,81,67,108,39,228,66,74,76,83,67,108,39,228,66,203,161,84,67,98,108,
39,228,66,43,231,113,67,86,206,9,67,230,208,132,67,182,19,39,67,230,208,132,67,98,22,89,68,67,230,208,132,67,182,19,92,67,44,231,113,67,182,19,92,67,204,161,84,67,98,182,19,92,67,108,92,55,67,22,89,68,67,204,161,31,67,182,19,39,67,204,161,31,67,98,150,
35,11,67,203,161,31,67,0,128,232,66,125,63,53,67,45,114,228,66,193,170,80,67,109,109,39,228,66,76,55,80,67,108,105,145,167,66,230,176,77,67,109,199,11,229,66,121,137,91,67,108,105,145,167,66,117,147,95,67,101,0,0 };

        Path path;
        path.loadPathFromData (pathData, sizeof (pathData));

        
        path.applyTransform (AffineTransform::translation (-50, -70));      // Move to Center of VST GUI
        path.applyTransform (AffineTransform::translation (-117, -143));    // Move to 0,0
        path.applyTransform (AffineTransform::rotation (sliderPos*3.1415)); // Rotate
        path.applyTransform (AffineTransform::translation (117, 143));      // Back to its position
    
        g.fillPath(path);

    }
    
};

//==============================================================================




#endif  // ALTLOOKANDFEEL_H_INCLUDED
