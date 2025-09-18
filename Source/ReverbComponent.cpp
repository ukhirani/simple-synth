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
    //initializing each reverb parameter sliders (making them visible and setting slider style)
    initReverbSlider(drySlider);
    initReverbSlider(wetSlider);

    initReverbSlider(RoomMsSlider);
    RoomMsSlider.setRange(0.1,1.0);

    initReverbSlider(LowCutoffFrequencySlider);
    initReverbSlider(HighCutoffFrequencySlider);
    initReverbSlider(RT20Slider);

    initReverbLabel("DRY",dryLabel);
    initReverbLabel("WET",wetLabel);
    initReverbLabel("ROOM",roomMsLabel);
    initReverbLabel("LOW",lowCutLabel);
    initReverbLabel("HIGH",highCutLabel);
    initReverbLabel("RT20",rt20Label);
    initReverbLabel("REVERB",ReverbLabel);




    wetSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "reverbWet", wetSlider);
    drySliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "reverbDry", drySlider);
    roomMsSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "roomMs", RoomMsSlider);
    lowCutoffFrequencySliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "lowCutoffFrequency", LowCutoffFrequencySlider);
    highCutoffFrequencySliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "highCutoffFrequency", HighCutoffFrequencySlider);
    RT20SliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "rt20", RT20Slider);

}

ReverbComponent::~ReverbComponent()
{
}

void ReverbComponent::initReverbLabel(juce::String label_text, Label &label) {
    addAndMakeVisible(label);

    label.setText(label_text, NotificationType::dontSendNotification);
    label.setJustificationType(Justification::centred);
    label.setColour(Label::textColourId, Colours::black);
    // label.setTooltip(label_text); TODO: add the tooltips later as they are not working as of now
    addAndMakeVisible(&label);
}



void ReverbComponent::paint (juce::Graphics& g)
{   int borderWidth = 2;
    // Draw a black border that spans from dry knob to RT20 knob
    auto border = juce::Rectangle<int>(
        drySlider.getX() ,  // Start from left of dry knob minus padding
        0,                    // Align with top of component
        (rt20Label.getRight() - drySlider.getX() ),  // Width from dry to RT20 plus padding
        ReverbLabel.getBottom()   // Height to bottom of REVERB label plus padding
    );
    g.setColour(Colours::black);

    
    g.drawRect(border, borderWidth);

    g.drawRect(drySlider.getBounds(), borderWidth);
    g.drawRect(wetSlider.getBounds(), borderWidth);
    g.drawRect(RoomMsSlider.getBounds(), borderWidth);
    g.drawRect(LowCutoffFrequencySlider.getBounds(), borderWidth);
    g.drawRect(HighCutoffFrequencySlider.getBounds(), borderWidth);
    g.drawRect(RT20Slider.getBounds(), borderWidth);



}

void ReverbComponent::initReverbSlider(juce::Slider &slider) {
    slider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    addAndMakeVisible(&slider);
    slider.setColour(Slider::textBoxTextColourId, juce::Colours::black);


}


void ReverbComponent::resized()
{
    constexpr int sliderWidth = 50;
    constexpr int sliderHeight = 200;
    constexpr int startX = 10;
    constexpr int startY = 38;
    constexpr int spacing = 10;

    constexpr int labelY = startY + sliderHeight + 5;
    constexpr int labelWidth = 50;
    constexpr int labelHeight = 20;

    // Set bounds for sliders

    Rectangle<int> area = getLocalBounds();

    ReverbLabel.setBorderSize(BorderSize<int>(1,1,1,1));


    drySlider.setBounds(startX, startY, sliderWidth, sliderHeight);
    wetSlider.setBounds(startX + sliderWidth + spacing, startY, sliderWidth, sliderHeight);
    RoomMsSlider.setBounds(startX + (sliderWidth + spacing) * 2, startY, sliderWidth, sliderHeight);
    LowCutoffFrequencySlider.setBounds(startX + (sliderWidth + spacing) * 3, startY, sliderWidth, sliderHeight);
    HighCutoffFrequencySlider.setBounds(startX + (sliderWidth + spacing) * 4, startY, sliderWidth, sliderHeight);
    RT20Slider.setBounds(startX + (sliderWidth + spacing) * 5, startY, sliderWidth, sliderHeight);

    // Set bounds for labels
    dryLabel.setBounds(startX, labelY, labelWidth, labelHeight);
    wetLabel.setBounds(startX + sliderWidth + spacing, labelY, labelWidth, labelHeight);
    roomMsLabel.setBounds(startX + (sliderWidth + spacing) * 2, labelY, labelWidth, labelHeight);
    lowCutLabel.setBounds(startX + (sliderWidth + spacing) * 3, labelY, labelWidth, labelHeight);
    highCutLabel.setBounds(startX + (sliderWidth + spacing) * 4, labelY, labelWidth, labelHeight);
    rt20Label.setBounds(startX + (sliderWidth + spacing) * 5, labelY, labelWidth, labelHeight);


    ReverbLabel.setBounds(rt20Label.getRight()/2 - 40,0,100,30);







}
