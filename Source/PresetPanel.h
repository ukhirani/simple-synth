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
		}

		~PresetPanel()
		{
			saveButton.removeListener(this);
			deleteButton.removeListener(this);
			previousPresetButton.removeListener(this);
			nextPresetButton.removeListener(this);
			presetList.removeListener(this);
		}

		void resized() override
		{
			const auto container = getLocalBounds().reduced(4);
			auto bounds = container;

			saveButton.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.2f)).reduced(4));
			previousPresetButton.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.1f)).reduced(4));
			presetList.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.4f)).reduced(4));
			nextPresetButton.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.1f)).reduced(4));
			deleteButton.setBounds(bounds.reduced(4));
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
