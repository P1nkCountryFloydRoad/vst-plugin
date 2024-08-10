/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FuzzAudioProcessorEditor::FuzzAudioProcessorEditor (FuzzAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    gainSlider.setSliderStyle(juce::Slider::LinearVertical);
    gainSlider.setRange(0.0, 3.0, 0.02);
    gainSlider.setValue(0.5);
    gainSlider.addListener(this);
    addAndMakeVisible(&gainSlider);
}

FuzzAudioProcessorEditor::~FuzzAudioProcessorEditor()
{
}

void FuzzAudioProcessorEditor::sliderValueChanged(juce::Slider* slider) 
{
  float gain = gainSlider.getValue();
  audioProcessor.updateGain(gain);
}

//==============================================================================
void FuzzAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("FUZZ!", getLocalBounds(), juce::Justification::centred, 1);
}

void FuzzAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    gainSlider.setBounds(getWidth() / 2 - 50, getHeight() / 2 - 75, 100, 150);
}
