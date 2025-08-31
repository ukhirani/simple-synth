/*
  ==============================================================================

    SynthSound.h
    Created: 31 Aug 2025 10:47:50am
    Author:  ukhirani

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthSound : public SynthesiserSound {
  public:
    //returns true if this sound should be played when a given midi note is pressed
    bool appliesToNote (int midiNoteNumber){
      return true;
    }

    //returns true if the sound should be triggered by midi events on a given channel
    bool appliesToChannel (int midiChannel){
      return true;
    }
};
