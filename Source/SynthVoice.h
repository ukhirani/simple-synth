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


    //2000 ms = 2 seconds
    // env1.setDecay(500);
    // env1.setSustain(0.8);
    // env1.setRelease(2000);

    for (int i = 0; i < numSamples; i++) {

      // const float theWave = osc1.saw(frequency);
      double theSound = env1.adsr(setOscType(),env1.trigger) * level ;



      double filteredSound = filter1.lores(theSound,20000,0.1);
      filteredSound = theSound;


      for (int channel = 0;channel < outputBuffer.getNumChannels();channel++) {
        outputBuffer.addSample(channel,startSample,theSound);
      }
      ++startSample;
    }
  }

  void getOscType(atomic<float> * selection) {
     theWave = *selection;
  }

  double setOscType() {
    if (theWave == 0) {
      return osc1.sinewave(frequency);
    }
    if (theWave == 1) {
      return osc1.saw(frequency);
    }
    if (theWave == 2) {
      return osc1.square(frequency);
    }
    return osc1.sinewave(frequency);
  }

private:
  double frequency = 440.0f;

  maxiOsc osc1;
  maxiEnv env1;
  maxiFilter filter1;
  int theWave;

  float level = 0.0;

};
