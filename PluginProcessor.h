/*
==============================================================================

This file was auto-generated!

It contains the basic framework code for a JUCE plugin processor.

==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <cmath>
#include <math.h>
#define _USE_MATH_DEFINES

//==============================================================================
/**
*/
class AutoWahProjectAudioProcessor : public AudioProcessor
{
public:
	//==============================================================================
	AutoWahProjectAudioProcessor();
	~AutoWahProjectAudioProcessor();

	//==============================================================================
	void prepareToPlay(double sampleRate, int samplesPerBlock) override;
	void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
	bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

	void processBlock(AudioSampleBuffer&, MidiBuffer&) override;

	//==============================================================================
	AudioProcessorEditor* createEditor() override;
	bool hasEditor() const override;

	//==============================================================================
	const String getName() const override;

	bool acceptsMidi() const override;
	bool producesMidi() const override;
	bool isMidiEffect() const override;
	double getTailLengthSeconds() const override;

	//==============================================================================
	int getNumPrograms() override;
	int getCurrentProgram() override;
	void setCurrentProgram(int index) override;
	const String getProgramName(int index) override;
	void changeProgramName(int index, const String& newName) override;

	//==============================================================================
	void getStateInformation(MemoryBlock& destData) override;
	void setStateInformation(const void* data, int sizeInBytes) override;



	
	bool up;							// Up/Down button 
	float release, Gain, sensitivity;  // Sliders 
	OwnedArray<IIRFilter> filters;	  
	Array<float> envelopes;
	

private:
	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AutoWahProjectAudioProcessor)

	double minfb, maxfb, minf, maxf, attack, Q, a_A, a_R, fc, fb;
	//float attack, minf, maxf;
	const double PI = std::atan(1.0) * 4;

};

