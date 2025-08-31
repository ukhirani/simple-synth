/*
  ==============================================================================

    SynthVoice.h
    Created: 31 Aug 2025 10:48:03am
    Author:  ukhirani

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include  "SynthSound.h"

class SynthVoice : SynthesiserVoice {
  public:
    bool canPlaySound(SynthesiserSound* sound) {
      return true;
    }
  void startNote(int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition) override {
    }
  void stopNote(float velocity, bool allowTailOff) override{

    }
  void pitchWheelMoved(int newPitchWheelValue) override{

  }
  void controllerMoved(int controllerNumber, int newControllerValue) override{

    }
  void renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override {

  }
private:
  int hello = 5;







};
