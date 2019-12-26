/*
  ==============================================================================

    PluginSound.h
    Created: 25 Dec 2019 7:47:44pm
    Author:  Esteban Polanco

  ==============================================================================
*/
#include "../JuceLibraryCode/JuceHeader.h"
#pragma once
class PluginSound : public SynthesiserSound {
public:
    bool appliesToNote(int midiNoteNumber) {
        return true;
    }
    virtual bool appliesToChannel(int midiChannel) {
        return true;
    }

 };