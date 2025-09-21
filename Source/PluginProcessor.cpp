/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SimpleSynthAudioProcessor::SimpleSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : juce::AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
#endif
           .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
#endif
       ), tree(*this, nullptr, "PARAMETERS", {

                //Noise Oscillator's processor tree state values
                   std::make_unique<juce::AudioParameterFloat>("noiseAmp", "Noise Amplitude", 0.0f, 1.0f, 0.0f),

                   std::make_unique<juce::AudioParameterFloat>("attack", "Attack", 0.1f, 5000.0f, 100.0f),
                   std::make_unique<juce::AudioParameterFloat>("decay", "Decay", 0.1f, 5000.0f, 100.0f),
                   std::make_unique<juce::AudioParameterFloat>("sustain", "Sustain", 0.1f, 5000.0f, 100.0f),
                   std::make_unique<juce::AudioParameterFloat>("release", "Release", 0.1f, 5000.0f, 100.0f),
                   // Limit cutoff to a safe range well below Nyquist to avoid filter singularities
                   std::make_unique<juce::AudioParameterFloat>("frequency","Cutoff Frequency",20.0f,10000.0f,1000.0f),
                   std::make_unique<juce::AudioParameterFloat>("resonance","Filter Resonance",0.1f,10.0f,1.0f),

                   // Reverb Component's processor tree state values
                   std::make_unique<juce::AudioParameterFloat>("reverbWet","Reverb Wet",0.0f,1.0f,0.3f),
                   std::make_unique<juce::AudioParameterFloat>("reverbDry","Reverb Dry",0.0f,1.0f,1.0f),
                   std::make_unique<juce::AudioParameterFloat>("roomMs","Room Ms",0.1f,10000.0f,500.0f),
                   std::make_unique<juce::AudioParameterFloat>("lowCutoffFrequency","Low Cutoff Frequency",20.0f,10000.0f,200.0f),
                   std::make_unique<juce::AudioParameterFloat>("highCutoffFrequency","High Cutoff Frequency",20.0f,10000.0f,2000.0f),
                   std::make_unique<juce::AudioParameterFloat>("rt20","RT20",0.0f,10000.0f,0.0f),

                   //Distortion Component's processor tree state values
                   std::make_unique<juce::AudioParameterFloat>("fuzz","Fuzz",0.0f,1.0f,0.5f),
                   std::make_unique<juce::AudioParameterFloat>("drive", "Drive", stfx::units::dbToGain(-12), stfx::units::dbToGain(40), 4),
                   std::make_unique<juce::AudioParameterFloat>("tonehz", "Tone Hz", 100, 20000, 4000),
                   std::make_unique<juce::AudioParameterFloat>("cuthz", "Cut Hz", 20, 500, 100),
                   std::make_unique<juce::AudioParameterFloat>("outgain", "Out Gain", stfx::units::dbToGain(-12), stfx::units::dbToGain(24), 1),

                   //Chorus's Component's process tree state values
                   std::make_unique<juce::AudioParameterFloat>("chorusMix","Chorus Mix",0.0f,1.0f,0.5f),
                   std::make_unique<juce::AudioParameterFloat>("chorusDepth","Chorus Depth",2.0f,20.0f,15.0f),
                   std::make_unique<juce::AudioParameterFloat>("chorusDetune","Chorus Detune",1.0f,50.0f,8.0f),
                   std::make_unique<juce::AudioParameterFloat>("chorusStereo","Chorus Stereo",0.0f,1.5f,0.5f),

                   std::make_unique<AudioParameterChoice>("wavetype","WaveType",StringArray { "saw", "square", "saw" },0)

               })
#endif
{
    mySynth.clearVoices();
    int numChannels = 5;
    for (int i = 0; i < numChannels; ++i) {
        mySynth.addVoice(new SynthVoice());
    }
    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());
}

SimpleSynthAudioProcessor::~SimpleSynthAudioProcessor()
{
}

//==============================================================================
const juce::String SimpleSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SimpleSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SimpleSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SimpleSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SimpleSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SimpleSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SimpleSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SimpleSynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SimpleSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void SimpleSynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

AudioProcessorValueTreeState::ParameterLayout SimpleSynthAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<RangedAudioParameter>> params;

    params.push_back(std::make_unique<AudioParameterFloat>("frequency","Cutoff Frequency",20.0f,10000.0f,1000.0f));
    params.push_back(std::make_unique<AudioParameterFloat>("resonance","Filter Resonance",0.1f,10.0f,1.0f));
    params.push_back(std::make_unique<AudioParameterFloat>("noiseAmp", "Noise Amplitude", 0.0f, 1.0f, 0.0f));

    params.push_back(std::make_unique<AudioParameterFloat>("attack", "Attack", 0.1f, 5000.0f, 100.0f));
    params.push_back(std::make_unique<AudioParameterFloat>("release", "Release", 0.1f, 5000.0f, 100.0f));
    params.push_back(std::make_unique<AudioParameterFloat>("decay", "Decay", 0.1f, 5000.0f, 100.0f));
    params.push_back(std::make_unique<AudioParameterFloat>("sustain", "Sustain", 0.1f, 5000.0f, 100.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("reverbWet","Reverb Wet",0.0f,1.0f,0.3f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("reverbDry","Reverb Dry",0.0f,1.0f,1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("roomMs","Room Ms",0.1f,10000.0f,500.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("lowCutoffFrequency","Low Cutoff Frequency",20.0f,10000.0f,200.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("highCutoffFrequency","High Cutoff Frequency",20.0f,10000.0f,2000.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("rt20","RT20",0.1f,10000.0f,0.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("fuzz","Fuzz",0.0f,1.0f,0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("drive", "Drive", stfx::units::dbToGain(-12), stfx::units::dbToGain(40), 4));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("tonehz", "Tone Hz", 100, 20000, 4000));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("cuthz", "Cut Hz", 20, 500, 100));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("outgain", "Out Gain", stfx::units::dbToGain(-12), stfx::units::dbToGain(24), 1));

    return { params.begin(), params.end() };
}

//==============================================================================
void SimpleSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    ignoreUnused(sampleRate);
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);

    for (int i = 0; i < mySynth.getNumVoices(); i++) {
        if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i)))) {
           myVoice->reverb1.configure(lastSampleRate,samplesPerBlock);
           myVoice->crunch1.configure(lastSampleRate,samplesPerBlock);
           myVoice->chorus1.configure(lastSampleRate,samplesPerBlock);
           myVoice->limiter1.configure(lastSampleRate,samplesPerBlock);
        }
    }

    maxiSettings::sampleRate = lastSampleRate;
}

void SimpleSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SimpleSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void SimpleSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (int i = 0; i < mySynth.getNumVoices(); i++) {
        if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i)))) {

            myVoice->setNoiseAmp(tree.getRawParameterValue("noiseAmp")->load());

            myVoice->setAttack(tree.getRawParameterValue("attack")->load());
            myVoice->setDecay(tree.getRawParameterValue("decay")->load());
            myVoice->setSustain(tree.getRawParameterValue("sustain")->load());
            myVoice->setRelease(tree.getRawParameterValue("release")->load());
            myVoice->getOscType(tree.getRawParameterValue("wavetype"));

            myVoice->setCutoffFrequency(tree.getRawParameterValue("frequency")->load());
            myVoice->setResonance(tree.getRawParameterValue("resonance")->load());
            
            myVoice->setReverbWet(tree.getRawParameterValue("reverbWet")->load());
            myVoice->setReverbDry(tree.getRawParameterValue("reverbDry")->load());
            myVoice->setRoomMs(tree.getRawParameterValue("roomMs")->load());
            myVoice->setLowCutoffFrequency(tree.getRawParameterValue("lowCutoffFrequency")->load());
            myVoice->setHighCutoffFrequency(tree.getRawParameterValue("highCutoffFrequency")->load());
            myVoice->setRT20(tree.getRawParameterValue("rt20")->load());

            myVoice->setBlockSize(getBlockSize());
            myVoice->setCurrSampleRate(getSampleRate());

            myVoice->setFuzz(tree.getRawParameterValue("fuzz")->load());
            myVoice->setDrive(tree.getRawParameterValue("drive")->load());
            myVoice->setToneHz(tree.getRawParameterValue("tonehz")->load());
            myVoice->setCutHz(tree.getRawParameterValue("cuthz")->load());
            myVoice->setOutGain(tree.getRawParameterValue("outgain")->load());
            
            myVoice->setChorusMix(tree.getRawParameterValue("chorusMix")->load());
            myVoice->setChorusDepth(tree.getRawParameterValue("chorusDepth")->load());
            myVoice->setChorusDetune(tree.getRawParameterValue("chorusDetune")->load());
            myVoice->setChorusStereo(tree.getRawParameterValue("chorusStereo")->load());

            
        }
    }

    // Clear the buffer and process audio
    buffer.clear();
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    // Send audio data to the visualizer if the editor is open
    if (auto* editor = dynamic_cast<SimpleSynthAudioProcessorEditor*>(getActiveEditor()))
    {
        // Only send every 4th sample to reduce CPU usage
        const int downsampleFactor = 4;
        for (int sample = 0; sample < buffer.getNumSamples(); sample += downsampleFactor)
        {
            // Send the left channel or mono sum if multiple channels
            float sampleValue = buffer.getSample(0, sample);
            if (totalNumOutputChannels > 1) {
                sampleValue = (sampleValue + buffer.getSample(1, sample)) * 0.5f;
            }
            editor->pushNextSample(sampleValue);
        }
    }
}

//==============================================================================
bool SimpleSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SimpleSynthAudioProcessor::createEditor()
{
    return new SimpleSynthAudioProcessorEditor (*this);
}

//==============================================================================
void SimpleSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SimpleSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleSynthAudioProcessor();
}
