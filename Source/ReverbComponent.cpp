/*
  ==============================================================================

    ReverbComponent.cpp
    Created: 18 Sep 2025 1:08:30pm
    Author:  ukhirani

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ReverbComponent.h"

//==============================================================================
ReverbComponent::ReverbComponent(SimpleSynthAudioProcessor& p) : processor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    wetSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    wetSlider.setRange(0.1f,5000.0f);
    wetSlider.setTextBoxStyle(Slider::TextBoxBelow,false,20.0,20.0);
    wetSlider.setHelpText("Hello");
    wetSlider.setValue(100.0f);
    addAndMakeVisible(&wetSlider);





    wetSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "reverbWet", wetSlider);

}

ReverbComponent::~ReverbComponent()
{
}

void ReverbComponent::paint (juce::Graphics& g)
{

    wetSlider.setColour (Slider::textBoxTextColourId, juce::Colours::black);


}

void ReverbComponent::resized()
{
    constexpr int sliderWidth = 50;
    constexpr int sliderHeight = 200;
    constexpr int startX = 10;
    constexpr int startY = 0;
    constexpr int spacing = 10;

    // Set bounds for sliders
    wetSlider.setBounds(startX, startY, sliderWidth, sliderHeight);


}
