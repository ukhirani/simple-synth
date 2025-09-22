#include "Crunch.h"
#include <JuceHeader.h>

CrunchComponent::CrunchComponent(SimpleSynthAudioProcessor& p)
    : processor(p)
{
    initCrunchSlider(fuzzSlider);
    initCrunchSlider(driveSlider);
    initCrunchSlider(tonehzSlider);
    initCrunchSlider(cuthzSlider);
    initCrunchSlider(outgainSlider);

    initCrunchLabel("FUZZ", fuzzLabel);
    initCrunchLabel("DRIVE", driveLabel);
    initCrunchLabel("TONE", tonehzLabel);
    initCrunchLabel("CUT", cuthzLabel);
    initCrunchLabel("GAIN", outgainLabel);
    initCrunchLabel("CRUNCH", CrunchLabel);

    CrunchLabel.setFont(FontOptions(15.0f,Font::bold));


    fuzzSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "fuzz", fuzzSlider);
    driveSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "drive", driveSlider);
    tonehzSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "tonehz", tonehzSlider);
    cuthzSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "cuthz", cuthzSlider);
    outgainSliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "outgain", outgainSlider);
}

CrunchComponent::~CrunchComponent()
{
}

void CrunchComponent::initCrunchSlider(Slider& slider)
{
    slider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    addAndMakeVisible(&slider);
    slider.setColour(Slider::textBoxTextColourId, juce::Colours::black);
}

void CrunchComponent::initCrunchLabel(const juce::String &labelText, Label& label)
{
    addAndMakeVisible(label);
    label.setText(labelText, NotificationType::dontSendNotification);
    label.setJustificationType(Justification::centred);
    label.setColour(Label::textColourId, Colours::black);
}

void CrunchComponent::paint(Graphics& g)
{
    int borderWidth = 2;
    auto border = juce::Rectangle<int>(
        fuzzSlider.getX() ,
        0,
        (outgainSlider.getRight() - fuzzSlider.getX() ),
        CrunchLabel.getBottom()
    );
    g.setColour(Colours::black);


    g.drawRect(border, borderWidth);

    g.drawRect(fuzzSlider.getBounds(), borderWidth);
    g.drawRect(driveSlider.getBounds(), borderWidth);
    g.drawRect(tonehzSlider.getBounds(), borderWidth);
    g.drawRect(cuthzSlider.getBounds(), borderWidth);
    g.drawRect(outgainSlider.getBounds(), borderWidth);

}



void CrunchComponent::resized()
{
    constexpr int sliderWidth = 50;
    constexpr int sliderHeight = 200;
    constexpr int startX = 10;
    constexpr int startY = 38;
    constexpr int spacing = 10;

    constexpr int labelY = startY + sliderHeight + 5;
    constexpr int labelWidth = 50;
    constexpr int labelHeight = 20;



    fuzzSlider.setBounds(startX,startY,sliderWidth,sliderHeight);
    driveSlider.setBounds(fuzzSlider.getRight() + spacing,startY,sliderWidth,sliderHeight);
    tonehzSlider.setBounds(driveSlider.getRight() + spacing,startY,sliderWidth,sliderHeight);
    cuthzSlider.setBounds(tonehzSlider.getRight() + spacing,startY,sliderWidth,sliderHeight);
    outgainSlider.setBounds(cuthzSlider.getRight() + spacing,startY,sliderWidth,sliderHeight);
    
    
    
    fuzzLabel.setBounds(startX,labelY,labelWidth,labelHeight);
    driveLabel.setBounds(fuzzSlider.getRight() + spacing,labelY,labelWidth,labelHeight);
    tonehzLabel.setBounds(driveSlider.getRight() + spacing,labelY,labelWidth,labelHeight);
    cuthzLabel.setBounds(tonehzSlider.getRight() + spacing,labelY,labelWidth,labelHeight);
    outgainLabel.setBounds(cuthzSlider.getRight() + spacing,labelY,labelWidth,labelHeight);

    CrunchLabel.setBounds(outgainLabel.getRight()/2 - 40,0,100,30);




    int labelX = startX;


}
