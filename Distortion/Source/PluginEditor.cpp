/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistortionAudioProcessorEditor::DistortionAudioProcessorEditor (DistortionAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (300, 300);

    // 设置 Slider 的属性
    thresholdSlider.setSliderStyle (juce::Slider::LinearBarVertical);
    thresholdSlider.setRange (0.0, 0.1, 0.001);
    thresholdSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    thresholdSlider.setPopupDisplayEnabled (true, false, this);
    thresholdSlider.setTextValueSuffix (" Threshold");
    thresholdSlider.setValue(0.5f);
    addAndMakeVisible(&thresholdSlider);
    thresholdSlider.addListener(this);

}

DistortionAudioProcessorEditor::~DistortionAudioProcessorEditor()
{
}

void DistortionAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
  audioProcessor.threshold = thresholdSlider.getValue();
}

//==============================================================================
void DistortionAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::white);
    g.setColour (juce::Colours::black);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("Distortion",0,0,getWidth(),30, juce::Justification::centred, 1);
}

void DistortionAudioProcessorEditor::resized()
{
    thresholdSlider.setBounds(10, 10, 20, getHeight() - 20);
}
