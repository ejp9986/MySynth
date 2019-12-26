/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MySynthAudioProcessor::MySynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
tree (*this, nullptr)
#endif
{
    NormalisableRange<float> slideRange(0.1f, 5.0f);
    NormalisableRange<float> plusOneRange(1.0f, 5.0f);
    NormalisableRange<float> gainRange(-48.0, 0.0f);
    tree.createAndAddParameter("attack", "Attack", "Attack", slideRange, 0.1f, nullptr, nullptr);
    tree.createAndAddParameter("decay", "Decay", "Decay", slideRange, 0.1f, nullptr, nullptr);
    tree.createAndAddParameter("sustain", "Sustain", "Sustain", plusOneRange, 1.0f, nullptr, nullptr);
    tree.createAndAddParameter("release", "Release", "Release", slideRange, 0.1f, nullptr, nullptr);
    tree.createAndAddParameter("gain", "Gain", "Gain", gainRange, -5.0f, nullptr, nullptr);
    tree.state = ValueTree("Foo");
    synth.clearVoices();
    for (size_t i = 0; i < 5; i++)
    {
        synth.addVoice(new PluginVoice());

    }
    synth.clearSounds();
    synth.addSound(new PluginSound());
    wave = 0;
}

MySynthAudioProcessor::~MySynthAudioProcessor()
{
}

//==============================================================================
const String MySynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MySynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MySynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MySynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MySynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MySynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MySynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MySynthAudioProcessor::setCurrentProgram (int index)
{
}

const String MySynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void MySynthAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MySynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    ignoreUnused(samplesPerBlock);
    currSampleRate = sampleRate;
    synth.setCurrentPlaybackSampleRate(currSampleRate);
}

void MySynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MySynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MySynthAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    for (size_t i = 0; i < synth.getNumVoices(); i++)
    {
        if (plugVoice = dynamic_cast<PluginVoice*>(synth.getVoice(i))) {}
        plugVoice->setEnvParams(*tree.getRawParameterValue("attack"),
                                *tree.getRawParameterValue("decay"),
                                *tree.getRawParameterValue("sustain"),
                                *tree.getRawParameterValue("release"));
        plugVoice->changeWaveForm(wave);
        plugVoice->changeLevel(*tree.getRawParameterValue("gain"));
    }

    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    //for (int channel = 0; channel < totalNumInputChannels; ++channel)
    //{
    //    auto* channelData = buffer.getWritePointer (channel);

    //    // ..do something to the data...
    //}

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool MySynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MySynthAudioProcessor::createEditor()
{
    return new MySynthAudioProcessorEditor (*this);
}

//==============================================================================
void MySynthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MySynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MySynthAudioProcessor();
}
