#include "BypassComponent.h"
#include <JuceHeader.h>

BypassComponent::BypassComponent(SimpleSynthAudioProcessor& p):processor(p)
{
    changeButtonUI(&toggleChorus);
    changeButtonUI(&toggleCrunch);
    changeButtonUI(&toggleReverb);
    changeButtonUI(&toggleLimiter);
}

BypassComponent::~BypassComponent()
{

}




void BypassComponent::paint (juce::Graphics& g)
{
    constexpr int borderWidth = 2;

}

void BypassComponent::resized()
{
    int sliderWidth = 100;
    constexpr int sliderHeight = 170;
    constexpr int startX = 0;
    constexpr int startY = 0;
    constexpr int spacing = 5;

    constexpr int labelWidth = 50;
    constexpr int labelHeight = 20;

    toggleCrunch.setBounds(startX,startY,labelWidth,labelHeight);
    toggleChorus.setBounds(startX + spacing + labelWidth,startY,labelWidth ,labelHeight);
    toggleReverb.setBounds();
    toggleLimiter.setBounds(startX + spacing + labelWidth,startY + labelHeight + spacing,labelWidth,labelHeight);


}
