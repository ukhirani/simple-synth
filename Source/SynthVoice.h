/*
  ==============================================================================

    SynthVoice.h
    Created: 31 Aug 2025 10:48:03am
    Author:  ukhirani

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "SynthSound.h"
#include "../MaximilianDSP/maximilian.h"

class SynthVoice : public SynthesiserVoice {
public:
  bool canPlaySound(SynthesiserSound *sound) override {
    // it will return true only if the cast is successful otherwise false.
    return dynamic_cast<SynthSound *>(sound) != nullptr;
  }
  void startNote(int midiNoteNumber, float velocity, SynthesiserSound *sound,int currentPitchWheelPosition) override {
    //find the equivalent frequency for the note that is being played
    level = velocity;
    frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    // std::cout << midiNoteNumber << std::endl;
    // std::cout<<velocity << std::endl;
  }
  void stopNote(float velocity, bool allowTailOff) override {
    level = 0;
    clearCurrentNote();


  }
  void pitchWheelMoved(int newPitchWheelValue) override {}
  void controllerMoved(int controllerNumber, int newControllerValue) override {}
  void renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample,
                       int numSamples) override {

    for (int i = 0; i < numSamples; i++) {
      const float theWave = osc1.saw(frequency) * level;
      for (int channel = 0;channel < outputBuffer.getNumChannels();channel++) {
        outputBuffer.addSample(channel,startSample,theWave);
      }
      ++startSample;
    }
  }

private:
  double frequency = 440.0f;
  maxiOsc osc1;
  float level = 0.0;

};
