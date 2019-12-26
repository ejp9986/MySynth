/*
  ==============================================================================

    PluginVoice.h
    Created: 25 Dec 2019 7:48:02pm
    Author:  Esteban Polanco

  ==============================================================================
*/
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginSound.h"
#include "Maximilian.h"
#include "SimpleOscillator.h"
#pragma once
class PluginVoice : public SynthesiserVoice {

public:
    PluginVoice() {
        osc.setSampleRate(getSampleRate());
        setEnvParams(0.1, 0.1, 1.0, 0.1);
    }

    void setEnvParams(float attack, float decay, float sustain, float release) {
        const ADSR::Parameters params{
        attack,
        decay,
        sustain,
        release
        };
        env.setParameters(params);
    }

    bool canPlaySound(SynthesiserSound* sound) {
        return dynamic_cast <PluginSound*>(sound) != nullptr;
    }
    void startNote(int midiNoteNumber,
        float velocity,
        SynthesiserSound* sound,
        int currentPitchWheelPosition) {

        env.noteOn();
        freq = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        level = velocity;
        osc.resetOscillator();


    }
    void stopNote(float velocity, bool allowTailOff) {
        env.noteOff();

        allowTailOff = true;
        if (velocity == 0) {
            clearCurrentNote();
        }
    }
    void pitchWheelMoved(int newPitchWheelValue) {

    }
    void controllerMoved(int controllerNumber, int newControllerValue) {

    }
    virtual void renderNextBlock(AudioBuffer<float>& outputBuffer,
        int startSample,
        int numSamples) {
        env.setSampleRate(getSampleRate());
        

        for (int sample = 0; sample < numSamples; ++sample)
        {
            double val = osc.getSample(freq);

            val = val * env.getNextSample() * level;
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, val);

            }
            ++startSample;
        }
    }
    void changeWaveForm(int wv) {
        osc.changeWaveForm(wv);
    }
    void changeLevel(float gain) {
        level = pow(10, gain / 20);
    }

private:
    double freq, level, currSampleRate;
    ADSR env;
    SimpleOscillator osc;

};
