#pragma once
#include <JuceHeader.h>

class PresetPanel : public juce::Component, Button::Listener,ComboBox::Listener{
    public:
    PresetPanel() {
        configureButton(saveButton, "Save");
        configureButton(deleteButton, "Delete");
        configureButton(previousButton, "<");
        configureButton(nextButton, ">");

        presetList.setTextWhenNothingSelected("No Preset Selected");
        presetList.setMouseCursor(MouseCursor::PointingHandCursor);
        addAndMakeVisible(presetList);
        presetList.addListener(this);
    }
    ~PresetPanel() {
        saveButton.removeListener(this);
        deleteButton.removeListener(this);
        previousButton.removeListener(this);
        nextButton.removeListener(this);
        presetList.removeListener(this);
    }


private:
    TextButton saveButton,deleteButton,previousButton,nextButton;
    ComboBox presetList;

    void buttonClicked(Button*) override {

    }
    void resized() override {
        const Rectangle<int> container = getLocalBounds().reduced (4);
        auto bounds = container;
        saveButton.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.2f)).reduced(4));
    }
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override {

    }
    void configureButton(Button& button,const String& buttonText) {

        button.setButtonText(buttonText);
        button.setMouseCursor(MouseCursor::PointingHandCursor);
        addAndMakeVisible(button);
        button.addListener(this);
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresetPanel);
};

