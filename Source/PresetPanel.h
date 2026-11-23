#pragma once

#include <JuceHeader.h>
#include "PresetManager.h"
#include "PluginProcessor.h"
#include "UI/Theme.h"

// Preset bar: [<] [ preset list ] [>]  [SAVE] [DEL]
class PresetPanel : public juce::Component, juce::Button::Listener, juce::ComboBox::Listener
{
public:
    PresetPanel (SimpleSynthAudioProcessor&, Service::PresetManager& pm) : presetManager (pm)
    {
        configureButton (saveButton, "Save", "Save the current sound as a preset");
        configureButton (deleteButton, "Del", "Delete the selected preset");
        configureButton (previousPresetButton, "<", "Previous preset");
        configureButton (nextPresetButton, ">", "Next preset");

        presetList.setTextWhenNothingSelected ("INIT");
        presetList.setTextWhenNoChoicesAvailable ("NO PRESETS");
        presetList.setMouseCursor (juce::MouseCursor::PointingHandCursor);
        addAndMakeVisible (presetList);
        presetList.addListener (this);

        loadPresetList();
    }

    ~PresetPanel() override
    {
        for (auto* b : { &saveButton, &deleteButton, &previousPresetButton, &nextPresetButton })
            b->removeListener (this);
        presetList.removeListener (this);
    }

    void resized() override
    {
        auto r = getLocalBounds();
        const int h  = r.getHeight();
        const int gap = ui::space::s2;

        deleteButton.setBounds (r.removeFromRight (52));
        r.removeFromRight (gap / 2);
        saveButton.setBounds (r.removeFromRight (60));
        r.removeFromRight (gap);

        previousPresetButton.setBounds (r.removeFromLeft (h));
        nextPresetButton.setBounds (r.removeFromRight (h));
        // Share borders with the arrow buttons.
        presetList.setBounds (r.expanded (1, 0));
    }

private:
    void buttonClicked (juce::Button* button) override
    {
        if (button == &saveButton)
        {
            fileChooser = std::make_unique<juce::FileChooser> ("Save Preset",
                                                               Service::PresetManager::defaultDirectory,
                                                               "*." + Service::PresetManager::extension);

            fileChooser->launchAsync (juce::FileBrowserComponent::saveMode
                                          | juce::FileBrowserComponent::warnAboutOverwriting,
                                      [this] (const juce::FileChooser& chooser)
                                      {
                                          const auto result = chooser.getResult();
                                          if (result.getFullPathName().isNotEmpty())
                                          {
                                              presetManager.savePreset (result.getFileNameWithoutExtension());
                                              loadPresetList();
                                          }
                                      });
        }
        else if (button == &previousPresetButton)
        {
            presetList.setSelectedItemIndex (presetManager.loadPreviousPreset(), juce::dontSendNotification);
        }
        else if (button == &nextPresetButton)
        {
            presetList.setSelectedItemIndex (presetManager.loadNextPreset(), juce::dontSendNotification);
        }
        else if (button == &deleteButton)
        {
            presetManager.deletePreset (presetManager.getCurrentPreset());
            loadPresetList();
        }
    }

    void comboBoxChanged (juce::ComboBox* box) override
    {
        if (box == &presetList)
            presetManager.loadPreset (presetList.getItemText (presetList.getSelectedItemIndex()));
    }

    void configureButton (juce::Button& button, const juce::String& text, const juce::String& tip)
    {
        button.setButtonText (text);
        button.setTooltip (tip);
        button.setMouseCursor (juce::MouseCursor::PointingHandCursor);
        addAndMakeVisible (button);
        button.addListener (this);
    }

    void loadPresetList()
    {
        presetList.clear (juce::dontSendNotification);
        const auto allPresets = presetManager.getAllPresets();
        const auto currentPreset = presetManager.getCurrentPreset();
        presetList.addItemList (allPresets, 1);
        presetList.setSelectedItemIndex (allPresets.indexOf (currentPreset), juce::dontSendNotification);
    }

    Service::PresetManager& presetManager;
    juce::TextButton saveButton, deleteButton, previousPresetButton, nextPresetButton;
    juce::ComboBox presetList;
    std::unique_ptr<juce::FileChooser> fileChooser;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetPanel)
};
