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
class AutoWahProjectAudioProcessorEditor : public AudioProcessorEditor, private Slider::Listener,
	private Button::Listener
										
{
public:
	AutoWahProjectAudioProcessorEditor(AutoWahProjectAudioProcessor&);
	~AutoWahProjectAudioProcessorEditor();

	//==============================================================================
	void paint(Graphics&) override;
	void resized() override;
	

private:

	void sliderValueChanged(Slider* slider) override;
	void buttonClicked(Button* togglebutton) override;
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	AutoWahProjectAudioProcessor& processor;


	Slider releaseS;
	Label releaseL;
	Slider gainS;
	Label gainL;
	Slider sensS;
	Label sensL;
	TextButton updown;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AutoWahProjectAudioProcessorEditor)
};
