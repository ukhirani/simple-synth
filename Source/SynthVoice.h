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
  SynthVoice() {
    // Initialize the envelope with default values
    env1.setAttack(100.0);
    env1.setDecay(500.0);
    env1.setSustain(0.8);
    env1.setRelease(2000.0);
    env1.trigger = 0;
    
    // Initialize waveType to match the default parameter value (1 = Sine)
    waveType = 1;
  }
  bool canPlaySound(SynthesiserSound *sound) override {
    // it will return true only if the cast is successful otherwise false.
    return dynamic_cast<SynthSound *>(sound) != nullptr;
  }
  void setAttack(float attack) {
    env1.setAttack(static_cast<double>(attack));

  }

  void setDecay(float decay) {
    env1.setDecay(static_cast<double>(decay));
  }

  void setSustain(float sustain) {
    env1.setSustain(static_cast<double>(sustain));
  }

  void setRelease(float release) {
    env1.setRelease(static_cast<double>(release));
  }


  void startNote(int midiNoteNumber, float velocity, SynthesiserSound *sound,int currentPitchWheelPosition) override {

    env1.trigger = 1;

    //velocity will be ranging from 0.0 to 1.0 so that is the float value that we are multiplying with the sound source's amplitude
    level = velocity;


    //find the equivalent frequency for the note that is being played
    frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);


  }
  void stopNote(float velocity, bool allowTailOff) override {

    env1.trigger = 0;
    allowTailOff = true;
    if (velocity == 0) {
      clearCurrentNote();
    }



  }
  void pitchWheelMoved(int newPitchWheelValue) override {}
  void controllerMoved(int controllerNumber, int newControllerValue) override {}
  void renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, const int numSamples) override {

    for (int i = 0; i < numSamples; i++) {
      // Select oscillator waveform based on waveType
      double theWave;
      switch (waveType) {
        case 1: // Sine
          theWave = osc1.sinewave(frequency);
          break;
        case 2: // Square
          theWave = osc1.square(frequency);
          break;
        case 3: // Saw
          theWave = osc1.saw(frequency);
          break;
        default:
          theWave = osc1.sinewave(frequency);
          break;
      }
      
      double theSound = env1.adsr(theWave, env1.trigger) * level;

      for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++) {
        outputBuffer.addSample(channel, startSample, theSound);
      }
      ++startSample;
    }
  }

private:
  double frequency = 440.0f;

  maxiOsc osc1;
  maxiEnv env1;
  maxiFilter filter1;

  float level = 0.0;
  int waveType = 1; // 1=sine, 2=square, 3=saw (default to sine)

public:
  void setWaveType(int type) {
    waveType = type;
  }
};
