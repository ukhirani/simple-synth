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
#include "CustomOscillator.h"

// Simple ADSR envelope implementation
class CustomADSR {
public:
    CustomADSR() = default;
    
    void setSampleRate(double sampleRate) {
        sampleRate_ = sampleRate;
        updateRates();
    }
    
    void setAttack(double attackMs) {
        attackMs_ = attackMs;
        updateRates();
    }
    
    void setDecay(double decayMs) {
        decayMs_ = decayMs;
        updateRates();
    }
    
    void setSustain(double sustainLevel) {
        sustainLevel_ = jlimit(0.0, 1.0, sustainLevel);
    }
    
    void setRelease(double releaseMs) {
        releaseMs_ = releaseMs;
        updateRates();
    }
    
    void noteOn() {
        state_ = State::Attack;
        currentLevel_ = (state_ == State::Attack) ? 0.0 : 1.0;
    }
    
    void noteOff() {
        if (state_ != State::Idle) {
            state_ = State::Release;
        }
    }
    
    float getNextSample() {
        switch (state_) {
            case State::Attack:
                currentLevel_ += attackRate_;
                if (currentLevel_ >= 1.0) {
                    currentLevel_ = 1.0;
                    state_ = State::Decay;
                }
                break;
                
            case State::Decay:
                currentLevel_ -= decayRate_;
                if (currentLevel_ <= sustainLevel_) {
                    currentLevel_ = sustainLevel_;
                    state_ = State::Sustain;
                }
                break;
                
            case State::Sustain:
                // Level stays at sustain level until note off
                break;
                
            case State::Release:
                currentLevel_ -= releaseRate_;
                if (currentLevel_ <= 0.0) {
                    currentLevel_ = 0.0;
                    state_ = State::Idle;
                }
                break;
                
            case State::Idle:
                currentLevel_ = 0.0;
                break;
        }
        
        return static_cast<float>(currentLevel_);
    }
    
    bool isActive() const { return state_ != State::Idle; }
    
private:
    enum class State { Idle, Attack, Decay, Sustain, Release };
    
    void updateRates() {
        attackRate_ = 1.0 / (0.001 * attackMs_ * sampleRate_);
        decayRate_ = (1.0 - sustainLevel_) / (0.001 * decayMs_ * sampleRate_);
        releaseRate_ = sustainLevel_ / (0.001 * releaseMs_ * sampleRate_);
    }
    
    double sampleRate_ = 44100.0;
    double attackMs_ = 100.0;
    double decayMs_ = 100.0;
    double releaseMs_ = 100.0;
    double sustainLevel_ = 0.8;
    
    double attackRate_ = 0.0;
    double decayRate_ = 0.0;
    double releaseRate_ = 0.0;
    
    double currentLevel_ = 0.0;
    State state_ = State::Idle;
};

class SynthVoice : public SynthesiserVoice {
public:
  SynthVoice() {
    // Initialize the envelope with default values
    envelope.setAttack(100.0);
    envelope.setDecay(500.0);
    envelope.setSustain(0.8);
    envelope.setRelease(2000.0);
    envelope.setSampleRate(44100.0); // Will be updated in prepareToPlay
    
    // Set default oscillator settings
    oscillator.setWaveType(WaveType::SINE);
  }
  
  void prepareToPlay(double sampleRate, int /*samplesPerBlock*/, int /*outputChannels*/) {
    envelope.setSampleRate(sampleRate);
    oscillator.prepare(sampleRate);
  }
  bool canPlaySound(SynthesiserSound *sound) override {
    // it will return true only if the cast is successful otherwise false.
    return dynamic_cast<SynthSound *>(sound) != nullptr;
  }
  void setAttack(double attack) {
    envelope.setAttack(attack);
  }

  void setDecay(double decay) {
    envelope.setDecay(decay);
  }

  void setSustain(double sustain) {
    envelope.setSustain(sustain);
  }

  void setRelease(double release) {
    envelope.setRelease(release);
  }

  void setCutoffFrequency(double CutoffFreq) {
    cutoffFrequency = CutoffFreq;
  }




  void startNote(int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition) override {
    envelope.noteOn();
    level = velocity;
    frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    oscillator.setFrequency(frequency);
    oscillator.reset();
  }
  void stopNote(float /*velocity*/, bool allowTailOff) override {
    if (allowTailOff) {
      envelope.noteOff();
    } else {
      envelope.noteOff();
      clearCurrentNote();
    }
  }
  void pitchWheelMoved(int newPitchWheelValue) override {}
  void controllerMoved(int controllerNumber, int newControllerValue) override {}
  void renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, const int numSamples) override {
    if (!isVoiceActive())
      return;

    for (int i = 0; i < numSamples; ++i) {
      float oscOutput = oscillator.getNextSample();
      float envValue = envelope.getNextSample();
      float sample = oscOutput * envValue * level;
      
      // Simple low-pass filter (can be replaced with a better implementation)
      static float lastOutput = 0.0f;
      float filteredSample = lastOutput + 0.5f * (sample - lastOutput);
      lastOutput = filteredSample;
      
      // Apply to all channels
      for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel) {
        outputBuffer.addSample(channel, startSample, filteredSample);
      }
      
      ++startSample;
      
      // Check if we should clear the note
      if (!envelope.isActive()) {
        clearCurrentNote();
        break;
      }
    }
  }

  void getOscType(std::atomic<float>* selection) {
    int waveType = static_cast<int>(*selection);
    switch (waveType) {
      case 0: oscillator.setWaveType(WaveType::SINE); break;
      case 1: oscillator.setWaveType(WaveType::SAW); break;
      case 2: oscillator.setWaveType(WaveType::SQUARE); break;
      case 3: oscillator.setWaveType(WaveType::TRIANGLE); break;
      default: oscillator.setWaveType(WaveType::SINE);
    }
  }

private:
  double frequency = 440.0f;
  float level = 0.0f;
  
  CustomOscillator oscillator;
  CustomADSR envelope;
  
  // Filter parameters (simple implementation - can be enhanced)
  float cutoffFrequency = 1000.0f;
  float filterResonance = 0.1f;

};
