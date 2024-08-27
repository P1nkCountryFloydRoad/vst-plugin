/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ReverbAudioProcessorEditor::ReverbAudioProcessorEditor (ReverbAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Reverb Time Slider
    reverbTimeSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    reverbTimeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    reverbTimeSlider.setRange(0.1, 5.0, 0.1);
    reverbTimeSlider.setValue(0.5f);
    reverbTimeSlider.addListener(this);
    addAndMakeVisible(&reverbTimeSlider);

    // Wet/Dry Mix Slider
    wetDryMixSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    wetDryMixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    wetDryMixSlider.setRange(0.0, 1.0, 0.01);
    wetDryMixSlider.setValue(0.5f);
    wetDryMixSlider.addListener(this);
    addAndMakeVisible(&wetDryMixSlider);

    setSize (400, 300);
}

void ReverbAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &reverbTimeSlider)
    {
        float reverbTime = reverbTimeSlider.getValue();
        audioProcessor.updateReverbTime(reverbTime);
    }
    else if (slider == &wetDryMixSlider)
    {
       float wetDryMix = wetDryMixSlider.getValue();
       audioProcessor.updateWetDryMix(wetDryMix);
    }
}

ReverbAudioProcessorEditor::~ReverbAudioProcessorEditor()
{
}

//==============================================================================
void ReverbAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("Reverb", 10,10,getWidth(),10, juce::Justification::centred, 1);
}

void ReverbAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
