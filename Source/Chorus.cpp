#include "Chorus.h"
#include <JuceHeader.h>

ChorusComponent::ChorusComponent(SimpleSynthAudioProcessor& p)
    : processor(p)
{
    initChorusSlider(chorusMixSlider);
    initChorusSlider(chorusDepthSlider);
    initChorusSlider(chorusDetuneSlider);
    initChorusSlider(chorusStereoSlider);


    initChorusLabel("MIX", chorusMixLabel);
    initChorusLabel("DEPTH", chorusDepthLabel);
    initChorusLabel("DETUNE", chorusDetuneLabel);
    initChorusLabel("STEREO", chorusStereoLabel);

    initChorusLabel("CHORUS", ChorusLabel);

    ChorusLabel.setFont(FontOptions(15.0f,Font::bold));


    chorusMixSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "chorusMix", chorusMixSlider);
    chorusDepthSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "chorusDepth", chorusDepthSlider);
    chorusDetuneSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "chorusDetune", chorusDetuneSlider);
    chorusStereoSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "chorusStereo", chorusStereoSlider);
}

ChorusComponent::~ChorusComponent()
{
}

void ChorusComponent::initChorusSlider(Slider& slider)
{
    slider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    addAndMakeVisible(&slider);
    slider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
}

void ChorusComponent::initChorusLabel(const juce::String &labelText, Label& label)
{
    addAndMakeVisible(label);
    label.setText(labelText, NotificationType::dontSendNotification);
    label.setJustificationType(Justification::centred);
    label.setColour(Label::textColourId, Colours::black);
}

void ChorusComponent::paint(Graphics& g)
{
    int borderWidth = 2;
    auto border = juce::Rectangle<int>(
        chorusMixSlider.getX() ,
        0,
        (chorusStereoSlider.getRight() - chorusMixSlider.getX() ),
        ChorusLabel.getBottom()
    );
    g.setColour(Colours::black);


    g.drawRect(border, borderWidth);

    g.drawRect(chorusMixSlider.getBounds(), borderWidth);
    g.drawRect(chorusDepthSlider.getBounds(), borderWidth);
    g.drawRect(chorusDetuneSlider.getBounds(), borderWidth);
    g.drawRect(chorusStereoSlider.getBounds(), borderWidth);

}



void ChorusComponent::resized()
{
    constexpr int sliderWidth = 50;
    constexpr int sliderHeight = 200;
    constexpr int startX = 10;
    constexpr int startY = 38;
    constexpr int spacing = 10;

    constexpr int labelY = startY + sliderHeight + 5;
    constexpr int labelWidth = 50;
    constexpr int labelHeight = 20;

    chorusMixSlider.setBounds(startX,startY,sliderWidth,sliderHeight);
    chorusDepthSlider.setBounds(chorusMixSlider.getRight() + spacing,startY,sliderWidth,sliderHeight);
    chorusDetuneSlider.setBounds(chorusDepthSlider.getRight() + spacing,startY,sliderWidth,sliderHeight);
    chorusStereoSlider.setBounds(chorusDetuneSlider.getRight() + spacing,startY,sliderWidth,sliderHeight);
    
    chorusMixLabel.setBounds(startX,labelY,labelWidth,labelHeight);
    chorusDepthLabel.setBounds(chorusMixSlider.getRight() + spacing,labelY,labelWidth,labelHeight);
    chorusDetuneLabel.setBounds(chorusDepthSlider.getRight() + spacing,labelY,labelWidth,labelHeight);
    chorusStereoLabel.setBounds(chorusDetuneSlider.getRight() + spacing,labelY,labelWidth,labelHeight);

    ChorusLabel.setBounds(chorusStereoLabel.getRight()/2 - 40,0,100,30);

}
