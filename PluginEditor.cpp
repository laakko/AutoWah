/*
==============================================================================

This file was auto-generated!

It contains the basic framework code for a JUCE plugin editor.

==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
AutoWahProjectAudioProcessorEditor::AutoWahProjectAudioProcessorEditor(AutoWahProjectAudioProcessor& p)
	: AudioProcessorEditor(&p), processor(p)
{
	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(400, 300);

	// UP/DOWN button
	addAndMakeVisible(&updown);
	if (processor.up == true) {
		updown.setButtonText("Up");
	}
	else {
		updown.setButtonText("Down");
	}
	updown.addListener(this);


	// these define the parameters of our slider object
	sensS.setSliderStyle(Slider::LinearBar);
	sensS.setRange(1, 4, 0.5);
	sensS.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	sensS.setPopupDisplayEnabled(true, false, this);
	sensS.setTextValueSuffix(" sensitivity");
	sensS.setValue(1);
	// sensS.setSliderStyle(Slider::Rotary);
	sensL.setText("Sensitivity", dontSendNotification);
	sensL.setColour(Label::textColourId, Colours::darkgreen);
	sensL.attachToComponent(&sensS, true);

	// this function adds the slider to the editor
	addAndMakeVisible(&sensS);
	addAndMakeVisible(&sensL);
	releaseS.addListener(this);

	// these define the parameters of our slider object
	releaseS.setSliderStyle(Slider::LinearBar);
	releaseS.setRange(0.001, 0.01, 0.001);
	releaseS.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	releaseS.setPopupDisplayEnabled(true, false, this);
	releaseS.setTextValueSuffix(" release");
	releaseS.setValue(0.01);
	releaseL.setText("Release", dontSendNotification);
	releaseL.setColour(Label::textColourId, Colours::darkgreen);
	releaseL.attachToComponent(&releaseS, true);

	// this function adds the slider to the editor
	addAndMakeVisible(&releaseS);
	addAndMakeVisible(&releaseL);
	releaseS.addListener(this);

	// these define the parameters of our slider object
	gainS.setSliderStyle(Slider::LinearBar);
	gainS.setRange(1, 30, 1);
	gainS.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	gainS.setPopupDisplayEnabled(true, false, this);
	gainS.setTextValueSuffix(" gain");
	gainS.setValue(10);
	gainL.setText("Gain", dontSendNotification);
	gainL.setColour(Label::textColourId, Colours::darkgreen);
	gainL.attachToComponent(&gainS, true);

	// this function adds the slider to the editor
	addAndMakeVisible(&gainS);
	addAndMakeVisible(&gainL);
	gainS.addListener(this);

}
void AutoWahProjectAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
	processor.release = releaseS.getValue();
	processor.Gain = gainS.getValue();
	processor.sensitivity = sensS.getValue();
}
AutoWahProjectAudioProcessorEditor::~AutoWahProjectAudioProcessorEditor()
{
}

void AutoWahProjectAudioProcessorEditor::buttonClicked(Button* button) {

	if (button == &updown) {
		
		if (processor.up == true) {
			processor.up = false;
			updown.setButtonText("Down");

		}
		else {
			processor.up = true;
			updown.setButtonText("Up");
		}
		
	}

}

//==============================================================================
void AutoWahProjectAudioProcessorEditor::paint(Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	//g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
	g.fillAll(Colours::darkseagreen);
	g.setColour(Colours::darkgreen);
	g.setFont(25.0f);
	g.drawFittedText("Auto-Wah  \n (envelope follower)", getLocalBounds(), Justification::centredTop, 1);
	g.setFont(20.0f);
	g.drawText("mode", 325, 100, 100,25 , true);
	g.setFont(12.0f);
	g.drawText("ELEC-E5620 Audio Signal Processing 2018, Jukka&Rafael", 10, 280, 350, 25, true);
}

void AutoWahProjectAudioProcessorEditor::resized()
{
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor..
	releaseS.setBounds(80, 200, 200, 25);
	gainS.setBounds(80, 150, 200, 25);
	sensS.setBounds(80, 100, 200, 25);
	updown.setBounds(325, 125, 50, 50);
}
