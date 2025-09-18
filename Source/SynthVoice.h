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
#include "../basics/include/signalsmith-basics/reverb.h"
// #include "../basics/include/signalsmith-basics/chorus.h"


class SynthVoice : public SynthesiserVoice {
public:
  SynthVoice() {
    // Initialize the envelope with default values
    env1.setAttack(100.0);
    env1.setDecay(500.0);
    env1.setSustain(0.8);
    env1.setRelease(2000.0);
    env1.trigger = 0;

    //now initialzing the signalsmith's reverb

    // reverb1.highCutHz = 8000.f;
    reverb1.configure(currSampleRate,512);
    reverb1.wet = 0.2;




  }
  bool canPlaySound(SynthesiserSound *sound) override {
    // it will return true only if the cast is successful otherwise false.
    return dynamic_cast<SynthSound *>(sound) != nullptr;
  }
  void setAttack(double attack) {
    env1.setAttack(attack);

  }

  void setDecay(double decay) {
    env1.setDecay(decay);
  }

  void setSustain(double sustain) {
    env1.setSustain(sustain);
  }

  void setRelease(double release) {
    env1.setRelease(release);
  }

  void setCutoffFrequency(double CutoffFreq) {
    cutoffFrequency = CutoffFreq;
  }

  void setCurrSampleRate(double rate) {
    currSampleRate = rate;
    // this cout was for debugging purpose
    // cout<<currSampleRate<<endl;
    // confirmed that this function is reacting to the sample rate change
  }






  void startNote(int midiNoteNumber, float velocity, SynthesiserSound *sound,int currentPitchWheelPosition) override {

    env1.trigger = 1;

    //velocity will be ranging from 0.0 to 1.0 so that is the float value that we are multiplying with the sound source's amplitude
    level = velocity*(0.5);


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
    // Get write pointers for the entire buffer

    // First, generate all the samples
    for (int i = 0; i < numSamples; i++) {
      double theSound = env1.adsr(setOscType(), env1.trigger) * level;
      double filteredSound = filter1.lores(theSound, cutoffFrequency, filterResonance);

      // Write to all channels
      for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++) {
        outputBuffer.addSample(channel, startSample + i, theSound);
      }
    }

    // Apply reverb to the entire block after all samples are generated
    if (outputBuffer.getNumChannels() >= 2) {
      float* channels[2] = {
        outputBuffer.getWritePointer(0, startSample),
        outputBuffer.getWritePointer(1, startSample)
    };
      reverb1.process(channels, numSamples);
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

  //================================================here goes all the signalsmith's stuff ===========================================================

  signalsmith::basics::ReverbFloat reverb1;




  int theWave = 0; // default to sine
  double cutoffFrequency = 1000.0f;
  double filterResonance = 5.0f;
  double currSampleRate = 44100.0;




  float level = 0.0;

};
