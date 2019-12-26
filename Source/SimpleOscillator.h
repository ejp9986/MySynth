/*
  ==============================================================================

    SimpleOscillator.h
    Created: 25 Dec 2019 11:13:48pm
    Author:  Esteban Polanco

  ==============================================================================
*/
#include "../JuceLibraryCode/JuceHeader.h"
class SimpleOscillator {
public:
    enum Wave
    {
        Sine,
        Square,
        Saw
    };
    SimpleOscillator() {
        wave = Sine;
        wavetableSize = 1024;
        recalculateWaveTable();
        phase = 0;
        
    }
    void setSampleRate(double currSampleRate) {
        sampleRate = currSampleRate;
    }
    float getSample(float frequency);
    void resetOscillator();
    void changeWaveForm(int wv);

private:
    double sampleRate;
    Array<float> wavetable;
    int wavetableSize;
    Wave wave;
    float increment;
    float phase = 0;


    void recalculateWaveTable();
    void recalculateWaveTableSin();
    void recalculateWaveTableSq();
    void recalculateWaveTableSaw();

};

#pragma once
