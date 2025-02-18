/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AlgoReverbAudioProcessor::AlgoReverbAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

AlgoReverbAudioProcessor::~AlgoReverbAudioProcessor()
{
}

//==============================================================================
const String AlgoReverbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AlgoReverbAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AlgoReverbAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AlgoReverbAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AlgoReverbAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AlgoReverbAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AlgoReverbAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AlgoReverbAudioProcessor::setCurrentProgram (int index)
{
}

const String AlgoReverbAudioProcessor::getProgramName (int index)
{
    return {};
}

void AlgoReverbAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void AlgoReverbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    predelay.setFs(sampleRate);
    predelay.setDelaySamples(0.0f);
    Fs = sampleRate;
    //fdn.setFs(sampleRate);
    //apf1.setFs(sampleRate);
    //apf2.setFs(sampleRate);
    schroeder.setFs(sampleRate);
    
}

void AlgoReverbAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AlgoReverbAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void AlgoReverbAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

   
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    predelay.setDepth(0.0f);
    predelay.setSpeed(0.0f);
    
    float predelaySec = predelayMS * 0.001;
    float predelaySamples = predelaySec * Fs;
    predelay.setDelaySamples(predelaySamples);
    
//    fdn.setTime(timeValue);
//    fdn.setDepth(modValue);
//
//    apf1.setDepth(modValue);
//    apf2.setDepth(modValue);
//
//    apf1.setFeedbackGain(diffusionValue);
//    apf2.setFeedbackGain(diffusionValue);
    schroeder.setFeedbackGain(timeValue);
    schroeder.setDiffusionGain(diffusionValue);
    schroeder.setDepth(modValue);
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        for(int n = 0; n < buffer.getNumSamples(); ++n)
        {
            //Retrieves sample from buffer and assigns it to variable x, which represents our dry signal
            float x = buffer.getWritePointer (channel)[n];
            
            //verb represents Wet signal
            float verb = predelay.processSample(x, channel);
//            verb = fdn.processSample(verb, channel);
//            verb = apf1.processSample(verb, channel);
//            verb = apf2.processSample(verb, channel);
            verb = schroeder.processSample(verb, channel);
            
            
            //1.f-wet IS the wetdry parameter
            float y = ( (1.f - wet) * x ) + (wet * verb);
            
            buffer.getWritePointer(channel)[n] = y;
        }
    }
}

//==============================================================================
bool AlgoReverbAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* AlgoReverbAudioProcessor::createEditor()
{
    return new AlgoReverbAudioProcessorEditor (*this);
}

//==============================================================================
void AlgoReverbAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void AlgoReverbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AlgoReverbAudioProcessor();
}
