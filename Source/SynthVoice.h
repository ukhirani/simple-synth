/*
  ==============================================================================

    SynthVoice.h
    Created: 31 Aug 2025 10:48:03am
    Author:  ukhirani

  ==============================================================================
*/

#pragma once


#include <ranges>

#include "JuceHeader.h"
#include "SynthSound.h"
#include "../MaximilianDSP/maximilian.h"
#include "../basics/include/signalsmith-basics/reverb.h"
#include "../basics/include/signalsmith-basics/crunch.h"
#include "../basics/include/signalsmith-basics/chorus.h"
#include "../basics/include/signalsmith-basics/limiter.h"




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
    // reverb1.configure(currSampleRate,currBlockSize);
    reverb1.wet = 0.2;

    //now initializing the signalsmith's crunch (distortion)
    // crunch1.configure(currSampleRate,currBlockSize);
    crunch1.fuzz = 0.1;
    crunch1.drive = 4;
    crunch1.fuzz = 0.5;

    //init maxiFilter
    filter1.setResonance(0);

    //init Limiter










  }
  double getNoise(bool NoiseFlag) {
    return noise_amplitude * noise1.noise();
  }

  double getSum(vector<double> &summation) {
    double sum = 0.0;
    for (size_t i = 0; i < summation.size(); i++) {
      sum+=summation[i];
    }
    return sum;
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

  void setSustain(const double sustain) {
    env1.setSustain(sustain);
  }

  void setRelease(const double release) {
    env1.setRelease(release);
  }

  void setCutoffFrequency(const double CutoffFreq) {
    cutoffFrequency = CutoffFreq;
  }

  void setCurrSampleRate(double rate) {
    currSampleRate = rate;
    // this cout was for debugging purpose
    // cout<<currSampleRate<<endl;
    // confirmed that this function is reacting to the sample rate change
  }

  void setNoiseAmp(double noiseAmp1) {
    noise_amplitude = noiseAmp1;
  }

  void setReverbWet(double wet1) {
    reverb1.wet = wet1;

  }

  void setReverbDry(double dry1) {
    reverb1.dry = dry1;
  }

  void setRoomMs(double roomMs1) {
    reverb1.roomMs = roomMs1;
  }

  void setLowCutoffFrequency(double lowCutoffFrequency1) {
    reverb1.lowCutHz = lowCutoffFrequency1;
  }

  void setHighCutoffFrequency(double highCutoffFrequency1) {
    reverb1.highCutHz = highCutoffFrequency1;
  }

  void setRT20(double rt201) {
    reverb1.rt20 = rt201;
  }

  void setChorusMix(double chorusMix1) {
    chorus1.mix = chorusMix1;
  }

  void setChorusDepth(double chorusDepth1) {
    chorus1.depthMs = chorusDepth1;
  }

  void setChorusDetune(double chorusDetune1) {
    chorus1.detune = chorusDetune1;
  }

  void setChorusStereo(double chorusStereo1) {
    chorus1.stereo = chorusStereo1;
  }

  void setOscAmp(double oscAmp1) {
    oscAmp = oscAmp1;
  }

  void setOctave (int octave) {
    oscOct = octave;
  }

  void setSemitone (int semitone) {
    oscSemi = semitone;
  }


  void startNote(int midiNoteNumber, float velocity, SynthesiserSound *sound,int currentPitchWheelPosition) override {

    env1.trigger = 1;

    //velocity will be ranging from 0.0 to 1.0 so that is the float value that we are multiplying with the sound source's amplitude
    level = velocity;


    //find the equivalent frequency for the note that is being played
    int finalMidi = midiNoteNumber + 12*oscOct + oscSemi;

    //TODO: Integrate the pitch wheel bend here
    frequency = MidiMessage::getMidiNoteInHertz(finalMidi);


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

    // First, generate all the samples
    for (int i = 0; i < numSamples; i++) {
      double theSound = env1.adsr(setOscType(), env1.trigger) * level * oscAmp;
      double theNoise = env1.adsr(getNoise(NoiseFlag), env1.trigger);

      vector<double> summation = vector<double>();

      summation.push_back(theSound);
      summation.push_back(theNoise);

      double theSum = env1.adsr(getSum(summation), env1.trigger);
      float filteredSound = filter1.lores(theSum, cutoffFrequency, filterResonance);

      // Write to all channels
      for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++) {
        outputBuffer.addSample(channel, startSample + i, filteredSound);
      }
    }

      float* channels[2] = {
        outputBuffer.getWritePointer(0, startSample),
        outputBuffer.getWritePointer(1, startSample)
    };

      crunch1.process(channels, numSamples);
      chorus1.process(channels,numSamples);
      reverb1.process(channels, numSamples);
      limiter1.process(channels, numSamples);


  }

  void getOscType(atomic<float> * selection) {
     theWave = *selection;
  }

  void setBlockSize(int blocksize) {
    currBlockSize = blocksize;
  }

  void setFuzz(double fuzz1) {
    crunch1.fuzz = fuzz1;
  }

  void setDrive(double drive1) {
    crunch1.drive = drive1;
  }

  void setToneHz(double toneHz1) {
    crunch1.toneHz = toneHz1;
  }

  void setCutHz(double cutHz1) {
    crunch1.cutHz = cutHz1;
  }

  void setOutGain(double outGain1) {
    crunch1.outGain = outGain1;
  }

  void setResonance(double resonance1) {
    filterResonance = resonance1;
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

  double frequency = 440.0f;

  maxiOsc osc1;
  int theWave = 0; // default to sine

  //init oscAmp's stuff
  double oscAmp = 0.5;
  int oscOct = 0;
  int oscSemi = 0;


  //noise and related stuff
  maxiOsc noise1;
  double noise_amplitude = 0.1;
  bool NoiseFlag = true;

  maxiEnv env1;

  maxiFilter filter1;
  double cutoffFrequency = 1000.0f;
  double filterResonance = 5.0f;
  double currSampleRate = 44100.0;
  int currBlockSize;

  double level = 0.0;

  //================================== here goes all the signalsmith's stuff =========================================
  signalsmith::basics::ReverbFloat reverb1;
  signalsmith::basics::CrunchFloat crunch1;
  signalsmith::basics::ChorusFloat chorus1;
  signalsmith::basics::LimiterFloat limiter1;


};
