#include "Limiter.h"
#include <JuceHeader.h>

LimiterComponent::LimiterComponent(SimpleSynthAudioProcessor& p)
    : processor(p)
{
    initLimiterSlider(inputGainSlider);
    initLimiterSlider(outputLimitSlider);
    initLimiterSlider(attackMsSlider);
    initLimiterSlider(holdMsSlider);
    initLimiterSlider(releaseMsSlider);

    initLimiterLabel("PRE", inputGainLabel);
    initLimiterLabel("LIMIT", outputLimitLabel);
    initLimiterLabel("ATK", attackMsLabel);
    initLimiterLabel("HOLD", holdMsLabel);
    initLimiterLabel("REL", releaseMsLabel);

    initLimiterLabel("LIMITER", LimiterLabel);
    LimiterLabel.setFont(FontOptions(15.0f,Font::bold));


    inputGainSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "inputGain", inputGainSlider);
    outputLimitSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "outputLimit", outputLimitSlider);
    attackMsSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "attackMs", attackMsSlider);
    holdMsSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "holdMs", holdMsSlider);
    releaseMsSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "releaseMs", releaseMsSlider);
}

LimiterComponent::~LimiterComponent()
{
}

void LimiterComponent::initLimiterSlider(Slider& slider)
{
    slider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    addAndMakeVisible(&slider);
    slider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
}

void LimiterComponent::initLimiterLabel(const juce::String &labelText, Label& label)
{
    addAndMakeVisible(label);
    label.setText(labelText, NotificationType::dontSendNotification);
    label.setJustificationType(Justification::centred);
    label.setColour(Label::textColourId, Colours::black);
}

void LimiterComponent::paint(Graphics& g)
{
    int borderWidth = 2;
    auto border = juce::Rectangle<int>(
        inputGainSlider.getX() ,
        0,
        (releaseMsSlider.getRight() - inputGainSlider.getX() ),
        LimiterLabel.getBottom()
    );
    g.setColour(Colours::black);


    g.drawRect(border, borderWidth);

    g.drawRect(inputGainSlider.getBounds(), borderWidth);
    g.drawRect(outputLimitSlider.getBounds(), borderWidth);
    g.drawRect(attackMsSlider.getBounds(), borderWidth);
    g.drawRect(holdMsSlider.getBounds(), borderWidth);
    g.drawRect(releaseMsSlider.getBounds(), borderWidth);

}



void LimiterComponent::resized()
{
    constexpr int sliderWidth = 50;
    constexpr int sliderHeight = 200;
    constexpr int startX = 10;
    constexpr int startY = 38;
    constexpr int spacing = 10;

    constexpr int labelY = startY + sliderHeight + 5;
    constexpr int labelWidth = 50;
    constexpr int labelHeight = 20;



    inputGainSlider.setBounds(startX,startY,sliderWidth,sliderHeight);
    outputLimitSlider.setBounds(inputGainSlider.getRight() + spacing,startY,sliderWidth,sliderHeight);
    attackMsSlider.setBounds(outputLimitSlider.getRight() + spacing,startY,sliderWidth,sliderHeight);
    holdMsSlider.setBounds(attackMsSlider.getRight() + spacing,startY,sliderWidth,sliderHeight);
    releaseMsSlider.setBounds(holdMsSlider.getRight() + spacing,startY,sliderWidth,sliderHeight);
    
    
    
    inputGainLabel.setBounds(startX,labelY,labelWidth,labelHeight);
    outputLimitLabel.setBounds(inputGainSlider.getRight() + spacing,labelY,labelWidth,labelHeight);
    attackMsLabel.setBounds(outputLimitSlider.getRight() + spacing,labelY,labelWidth,labelHeight);
    holdMsLabel.setBounds(attackMsSlider.getRight() + spacing,labelY,labelWidth,labelHeight);
    releaseMsLabel.setBounds(holdMsSlider.getRight() + spacing,labelY,labelWidth,labelHeight);

    LimiterLabel.setBounds(releaseMsLabel.getRight()/2 - 40,0,100,30);




    int labelX = startX;


}
