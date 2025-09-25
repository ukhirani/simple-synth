#pragma once
#include "PresetManager.h"
#include <JuceHeader.h>
#include "PluginProcessor.h"


	class PresetPanel : public Component, Button::Listener, ComboBox::Listener
	{
	public:
		PresetPanel(SimpleSynthAudioProcessor& p,Service::PresetManager& pm) : presetManager(pm)
		{
			configureButton(saveButton, "Save");
			configureButton(deleteButton, "Delete");
			configureButton(previousPresetButton, "<");
			configureButton(nextPresetButton, ">");

			presetList.setTextWhenNothingSelected("No Preset Selected");
			presetList.setMouseCursor(MouseCursor::PointingHandCursor);
			addAndMakeVisible(presetList);
			presetList.addListener(this);

			loadPresetList();


			presetList.setColour(ComboBox::ColourIds::backgroundColourId, Colours::white);
			presetList.setColour(ComboBox::ColourIds::textColourId		, Colours::black);
			presetList.setColour(ComboBox::ColourIds::outlineColourId	, Colours::black);
			presetList.setColour(ComboBox::ColourIds::buttonColourId	, Colours::black);
			presetList.setColour(ComboBox::ColourIds::arrowColourId		, Colours::black);
			presetList.setColour(ComboBox::ColourIds::focusedOutlineColourId , Colours::black);

			changeButtonUI(&saveButton);
			changeButtonUI(&deleteButton);
			changeButtonUI(&previousPresetButton);
			changeButtonUI(&nextPresetButton);













		}

		~PresetPanel()
		{
			saveButton.removeListener(this);
			deleteButton.removeListener(this);
			previousPresetButton.removeListener(this);
			nextPresetButton.removeListener(this);
			presetList.removeListener(this);
		}

		static void changeButtonUI(TextButton* button) {
			button->setColour(TextButton::ColourIds::buttonColourId, Colours::white);
			button->setColour(TextButton::ColourIds::textColourOffId, Colours::black);
		}



		void resized() override
		{
			const auto container = getLocalBounds().reduced(4);
			auto bounds = container;

			constexpr int padding = 3;

			saveButton.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.2f)).reduced(padding));
			previousPresetButton.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.05f)).reduced(padding));
			presetList.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.5f)).reduced(padding));
			nextPresetButton.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.05f)).reduced(padding));
			deleteButton.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.2f)).reduced(padding));
		}
	private:
		void buttonClicked(Button* button) override
		{
			if (button == &saveButton)
			{
				fileChooser = std::make_unique<FileChooser>("Save Preset",
					Service::PresetManager::defaultDirectory,
					"*." + Service::PresetManager::extension,
					true,  // warn about overwriting
					false  // don't select multiple files
				);

				fileChooser->launchAsync(FileBrowserComponent::saveMode, 
				[this](const FileChooser& chooser)
				{
					const auto result = chooser.getResult();
					if (result.getFullPathName().isNotEmpty())
					{
						presetManager.savePreset(result.getFileNameWithoutExtension());
						loadPresetList();
					}
					fileChooser.reset();
				});
			}
			if (button == &previousPresetButton)
			{
				const auto index = presetManager.loadPreviousPreset();
				presetList.setSelectedItemIndex(index, dontSendNotification);
			}
			if (button == &nextPresetButton)
			{
				const auto index = presetManager.loadNextPreset();
				presetList.setSelectedItemIndex(index, dontSendNotification);
			}
			if (button == &deleteButton)
			{
				presetManager.deletePreset(presetManager.getCurrentPreset());
				loadPresetList();
			}
		}
		void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override
		{
			if (comboBoxThatHasChanged == &presetList)
			{
				presetManager.loadPreset(presetList.getItemText(presetList.getSelectedItemIndex()));
			}
		}

		void configureButton(Button& button, const String& buttonText)
		{
			button.setButtonText(buttonText);
			button.setMouseCursor(MouseCursor::PointingHandCursor);
			addAndMakeVisible(button);
			button.addListener(this);
		}

		void loadPresetList()
		{
			presetList.clear(dontSendNotification);
			const auto allPresets = presetManager.getAllPresets();
			const auto currentPreset = presetManager.getCurrentPreset();
			presetList.addItemList(allPresets, 1);
			presetList.setSelectedItemIndex(allPresets.indexOf(currentPreset), dontSendNotification);
		}

		Service::PresetManager& presetManager;
		TextButton saveButton, deleteButton, previousPresetButton, nextPresetButton;
		ComboBox presetList;
		std::unique_ptr<FileChooser> fileChooser;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresetPanel)
	};
