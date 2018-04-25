/*
==============================================================================

This file was auto-generated!

It contains the basic framework code for a JUCE plugin processor.

==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
AutoWahProjectAudioProcessor::AutoWahProjectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", AudioChannelSet::stereo(), true)
#endif
	)
#endif
{



	// Initialize variables
	Q = 10.0;		 // Q-factor
	fb = 200.0;		 // Bandwidth
	fc = 1000.0;	 // Center frequency
	//Gain = 20;     // (Handled with a slider)
	attack = 0.001;
	//release = 0.4; // (Handled with a slider)
	minf = 400.0;    // Envelope sweeps from min freq to max freq
	maxf = 2000.0;
	minfb = 80.0;
	maxfb = 700.0;

}

AutoWahProjectAudioProcessor::~AutoWahProjectAudioProcessor()
{
}

//==============================================================================
const String AutoWahProjectAudioProcessor::getName() const
{
	return JucePlugin_Name;
}

bool AutoWahProjectAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool AutoWahProjectAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool AutoWahProjectAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}

double AutoWahProjectAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int AutoWahProjectAudioProcessor::getNumPrograms()
{
	return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
				// so this should be at least 1, even if you're not really implementing programs.
}

int AutoWahProjectAudioProcessor::getCurrentProgram()
{
	return 0;
}

void AutoWahProjectAudioProcessor::setCurrentProgram(int index)
{
}

const String AutoWahProjectAudioProcessor::getProgramName(int index)
{
	return {};
}

void AutoWahProjectAudioProcessor::changeProgramName(int index, const String& newName)
{
}

//==============================================================================
void AutoWahProjectAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	// Use this method as the place to do any pre-playback
	// initialisation that you need..
	
	up = true;

	// Initialize peak filters
	filters.clear();
	for (int i = 0; i < getTotalNumInputChannels(); ++i) {
		IIRFilter* filter;
		filters.add(filter = new IIRFilter());
	}

	// Initialize envelopes
	for (int i = 0; i < getTotalNumInputChannels(); ++i)
		envelopes.add(0.0f);

}

void AutoWahProjectAudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AutoWahProjectAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
	ignoreUnused(layouts);
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

void AutoWahProjectAudioProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	ScopedNoDenormals noDenormals;
	const int totalNumInputChannels = getTotalNumInputChannels();
	const int totalNumOutputChannels = getTotalNumOutputChannels();


	for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());



	// Main audio processing loop
	for (int channel = 0; channel < totalNumInputChannels; ++channel) {
		float *channelData = buffer.getWritePointer(channel);

		for (int n = 0; n < buffer.getNumSamples(); ++n) {

			const float x = channelData[n];


			// Envelope
			float envelope;
			a_A = exp(-1.0f / (attack*getSampleRate()));
			a_R = exp(-1.0f / (release*getSampleRate()));

			// Level detector
			if (fabs(x) > envelopes[channel]) {
				envelope = a_A * envelopes[channel] + (1.0f - a_A)*fabs(x); // Attack
			}
			else {
				envelope = a_R * envelopes[channel] + (1.0f - a_R)*fabs(x); // Release
			}

			envelopes.set(channel, envelope);
						
			// Update filter parameters depending on level
			if (up == true) {										// Up
				fc = minf + (maxf - minf)*envelopes[channel];  
				// TODO Gain
			} else {												// Down
				fc = maxf + (minf - maxf)*envelopes[channel]; 	
			}
			
			fb = minfb + (maxfb - minfb)*envelopes[channel];
			Q = fc / fb; 

			
			// Peak filter
			for (int i = 0; i < filters.size(); ++i) {
				filters[i]->setCoefficients(IIRCoefficients::makePeakFilter(getSampleRate(), fc, Q, Gain));
			}

			// Filtering
			float filtered = filters[channel]->processSingleSampleRaw(x);
			channelData[n] = sensitivity*filtered; // Output

	
		}
	}

	for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());


}



//==============================================================================
bool AutoWahProjectAudioProcessor::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* AutoWahProjectAudioProcessor::createEditor()
{
	return new AutoWahProjectAudioProcessorEditor(*this);
}

//==============================================================================
void AutoWahProjectAudioProcessor::getStateInformation(MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.
}

void AutoWahProjectAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new AutoWahProjectAudioProcessor();
}

