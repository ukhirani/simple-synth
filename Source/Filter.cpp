#include <JuceHeader.h>
#include "Filter.h"

//==============================================================================
Filter::Filter(SimpleSynthAudioProcessor& p):processor(p)
{

  FrequencySlider.setSliderStyle(Slider::LinearBarVertical);
  // FrequencySlider.setRange(20.0f,10000.0f);
  FrequencySlider.setTextBoxStyle(Slider::TextBoxBelow,false,20.0,20.0);

  ResonanceSlider.setSliderStyle(Slider::LinearBarVertical);
  ResonanceSlider.setRange(0.0f,5.0f);
  ResonanceSlider.setTextBoxStyle(Slider::TextBoxBelow,false,20.0,20.0);

  FrequencyLabel.setText("FREQ", NotificationType::dontSendNotification);
  FrequencyLabel.setJustificationType(Justification::centred);
  FrequencyLabel.setColour(Label::textColourId, Colours::black);

  ResonanceLabel.setText("RES", NotificationType::dontSendNotification);
  ResonanceLabel.setJustificationType(Justification::centred);
  ResonanceLabel.setColour(Label::textColourId, Colours::black);

  FilterLabel.setText("FILTER", NotificationType::dontSendNotification);
  FilterLabel.setJustificationType(Justification::centred);
  FilterLabel.setColour(Label::textColourId, Colours::black);

  FilterLabel.setFont(FontOptions(15.0f,Font::bold));


  addAndMakeVisible(&FrequencySlider);
  addAndMakeVisible(&ResonanceSlider);
  addAndMakeVisible(&FrequencyLabel);
  addAndMakeVisible(&ResonanceLabel);
  addAndMakeVisible(&FilterLabel);




  FrequencyAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(
    processor.tree, "frequency", FrequencySlider);
  ResonanceAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(
  processor.tree, "resonance", ResonanceSlider);



}

Filter::~Filter()
{
}

void Filter::paint (juce::Graphics& g)
{

  int borderWidth = 2;

  FrequencySlider.setColour (Slider::textBoxTextColourId, juce::Colours::black);
  FrequencyLabel.setColour (Slider::textBoxTextColourId, juce::Colours::black);

  ResonanceSlider.setColour (Slider::textBoxTextColourId, juce::Colours::black);
  ResonanceLabel.setColour (Slider::textBoxTextColourId, juce::Colours::black);

  auto border = juce::Rectangle<int>(
      FrequencySlider.getX() ,
      10,
      (ResonanceSlider.getRight() - FrequencySlider.getX() ),
      30
  );
  g.setColour(Colours::black);
  g.drawRect(border, borderWidth);

  g.drawRect(FrequencySlider.getBounds(), borderWidth);
  g.drawRect(ResonanceSlider.getBounds(), borderWidth);

}

void Filter::resized()
{

  const int sliderWidth = 50;
  const int sliderHeight = 200;
  const int startX = 0;
  const int startY = 50;
  const int spacing = 10;

  FrequencySlider.setBounds(startX, startY, sliderWidth, sliderHeight);
  ResonanceSlider.setBounds(startX + spacing + sliderWidth, startY,sliderWidth , sliderHeight);


  const int labelY = startY + sliderHeight + 5;
  const int labelWidth = 50;
  const int labelHeight = 20;

  FrequencyLabel.setBounds(FrequencySlider.getX() + (sliderWidth - labelWidth)/2, labelY, labelWidth, labelHeight);
  ResonanceLabel.setBounds(ResonanceSlider.getX() + (sliderWidth - labelWidth)/2, labelY, labelWidth, labelHeight);

  FilterLabel.setBounds(  0,15,ResonanceSlider.getRight()- FrequencySlider.getX(),20);







}

