#pragma once
#include <JuceHeader.h>

enum class WaveType {
    SINE,
    SAW,
    SQUARE,
    TRIANGLE
};

class CustomOscillator {
public:
    CustomOscillator() = default;
    
    void prepare(double sampleRate) {
        currentSampleRate = sampleRate;
        updatePhaseIncrement();
    }
    
    void setFrequency(double newFrequencyHz) {
        if (frequencyHz != newFrequencyHz) {
            frequencyHz = newFrequencyHz;
            updatePhaseIncrement();
        }
    }
    
    void setWaveType(WaveType newType) {
        waveType = newType;
    }
    
    float getNextSample() noexcept {
        float value = 0.0f;
        
        switch (waveType) {
            case WaveType::SINE:
                value = std::sin(phase * juce::MathConstants<float>::twoPi);
                break;
                
            case WaveType::SAW: {
                value = 2.0f * (phase - std::floor(phase + 0.5f));
                break;
            }
                
            case WaveType::SQUARE:
                value = (phase < 0.5f) ? 1.0f : -1.0f;
                break;
                
            case WaveType::TRIANGLE:
                value = 1.0f - (4.0f * std::abs(phase - 0.5f) - 1.0f);
                break;
        }
        
        // Update phase for next sample
        phase += phaseDelta;
        if (phase >= 1.0f)
            phase -= 1.0f;
            
        return value * level;
    }
    
    void setLevel(float newLevel) {
        level = juce::jlimit(0.0f, 1.0f, newLevel);
    }
    
    void reset() {
        phase = 0.0f;
    }
    
private:
    void updatePhaseIncrement() {
        if (currentSampleRate > 0.0)
            phaseDelta = static_cast<float>(frequencyHz / currentSampleRate);
    }
    
    WaveType waveType = WaveType::SINE;
    double frequencyHz = 440.0;
    double currentSampleRate = 44100.0;
    float phase = 0.0f;
    float phaseDelta = 0.0f;
    float level = 0.8f;
};
