/*
  ==============================================================================

    SimpleOscillator.cpp
    Created: 25 Dec 2019 11:19:07pm
    Author:  Esteban Polanco

  ==============================================================================
*/

#include "SimpleOscillator.h"

void SimpleOscillator::recalculateWaveTable() {
    switch (wave) {
    case(Sine):
        recalculateWaveTableSin();
        break;
    case(Square):
        recalculateWaveTableSq();
        break;
    case(Saw):
        recalculateWaveTableSaw();
        break;
    default:
        recalculateWaveTableSin();
    }
}

void SimpleOscillator::recalculateWaveTableSin() {
    double tau = 2 * double_Pi;
    for (int i = 0; i < wavetableSize; ++i) {
        float val = sinf(tau * i / wavetableSize);
        wavetable.insert(i, val);
    }
}
void SimpleOscillator::recalculateWaveTableSq() {
    double tau = 2 * double_Pi;
    for (int i = 0; i < wavetableSize; ++i) {
        float val = sinf(tau * i / wavetableSize);
        if (val < 0) {
            val = -1;
        }
        else
            val = 1;
        wavetable.insert(i, val);
    }
}
void SimpleOscillator::recalculateWaveTableSaw() {
    for (int i = 0; i < wavetableSize; ++i)
    {
        wavetable.insert(i - 1, ((i / (float)wavetableSize) * 2) - 1);
    }
}
float SimpleOscillator::getSample(float freq) {
    increment = freq * wavetableSize / sampleRate;
    float val = wavetable[(int)phase];
    phase = fmod(phase + increment, wavetableSize);
    return val;
}
void SimpleOscillator::resetOscillator() {
    phase = 0;
}
void SimpleOscillator::changeWaveForm(int wv) {
    Wave newWave = (Wave)wv;
    if (newWave != wave) {
        wave = newWave;
        recalculateWaveTable();
    }
}