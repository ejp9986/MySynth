/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MySynthAudioProcessorEditor::MySynthAudioProcessorEditor (MySynthAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(0.0, 5.0);
    attackSlider.setValue(0.1);
    attackSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 30);;
    addAndMakeVisible(attackSlider);

    decaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    decaySlider.setRange(0.0, 5.0);
    decaySlider.setValue(0.1);
    decaySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 30);
    addAndMakeVisible(decaySlider);

    sustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    sustainSlider.setRange(1.0, 5.0);
    sustainSlider.setValue(1.0);
    sustainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 30);
    addAndMakeVisible(sustainSlider);

    releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange(0.0, 5.0);
    releaseSlider.setValue(0.1);
    releaseSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 30);
    addAndMakeVisible(releaseSlider);

    gainSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    gainSlider.setRange(-48.0f, 0.0f);
    gainSlider.setValue(-5.0);
    gainSlider.setTextBoxStyle(Slider::TextBoxRight, false, 60, 30);
    addAndMakeVisible(gainSlider);

    attLabel.setText("Attack", dontSendNotification);
    attLabel.attachToComponent(&attackSlider, false);
    addAndMakeVisible(attLabel);

    decLabel.setText("Decay", dontSendNotification);
    decLabel.attachToComponent(&decaySlider, false);
    addAndMakeVisible(decLabel);

    susLabel.setText("Sustain", dontSendNotification);
    susLabel.attachToComponent(&sustainSlider, false);
    addAndMakeVisible(susLabel);

    relLabel.setText("Release", dontSendNotification);
    relLabel.attachToComponent(&releaseSlider, false);
    addAndMakeVisible(relLabel);

    gainLabel.setText("Gain", dontSendNotification);
    gainLabel.attachToComponent(&gainSlider, true);
    addAndMakeVisible(gainLabel);

    

    treeAttSlider = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "attack", attackSlider);
    treeDecSlider = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "decay", decaySlider);
    treeSusSlider = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "sustain", sustainSlider);
    treeRelSlider = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "release", releaseSlider);
    treeGainSlider = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "gain", gainSlider);

    sin.addListener(this);
    sqr.addListener(this);
    saw.addListener(this);

    addAndMakeVisible(sin);
    sin.setButtonText("Sine");
    addAndMakeVisible(sqr);
    sqr.setButtonText("Square");
    addAndMakeVisible(saw);
    saw.setButtonText("Saw");
}

MySynthAudioProcessorEditor::~MySynthAudioProcessorEditor()
{
}

//==============================================================================
void MySynthAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
}

void MySynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    attackSlider.setBounds(10, 30, 60, 200);
    decaySlider.setBounds(80, 30, 60, 200);
    sustainSlider.setBounds(150, 30, 60, 200);
    releaseSlider.setBounds(220, 30, 60, 200);

    sin.setBounds(290, 30, 100, 50);
    sqr.setBounds(290, 100, 100, 50);
    saw.setBounds(290, 170, 100, 50);

    gainSlider.setBounds(30, 250, 350, 30);

}
void MySynthAudioProcessorEditor::buttonClicked(Button* btn) {
    if (btn == &sin) {
        processor.wave = 0;
    }
    else if (btn == &sqr) {
        processor.wave = 1;
    }
    else if (btn == &saw) {
        processor.wave = 2;
    }
}

