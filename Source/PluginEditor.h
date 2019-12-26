/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class MySynthAudioProcessorEditor  : public AudioProcessorEditor, 
                                     public Button::Listener
{
public:
    MySynthAudioProcessorEditor (MySynthAudioProcessor&);
    ~MySynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    void buttonClicked(Button* btn) override;


private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MySynthAudioProcessor& processor;

    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> treeAttSlider, treeDecSlider, treeSusSlider, treeRelSlider, treeGainSlider;

    Slider attackSlider, decaySlider, sustainSlider, releaseSlider, gainSlider;

    Label attLabel, decLabel, susLabel, relLabel, gainLabel;

    TextButton sin;
    TextButton sqr;
    TextButton saw;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MySynthAudioProcessorEditor)
};
