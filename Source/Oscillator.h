/*
  ==============================================================================

    Oscillator.h
    Created: 7 Sep 2025 9:34:46am
    Author:  ukhirani

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Oscillator  : public juce::Component,
                    public juce::ComboBox::Listener
{
public:
    Oscillator();
    ~Oscillator() override;

    void comboBoxChanged(juce::ComboBox* comboBox) override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void FillComboBox();
    
    // Getter for the combo box to create attachment
    ComboBox& getOscMenu() { return oscMenu; }

private:
    ComboBox oscMenu;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
