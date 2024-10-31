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

    // 阈值滑块
    thresholdSlider.setSliderStyle (juce::Slider::LinearBarVertical);
    thresholdSlider.setRange (0.0, 0.1, 0.001);
    thresholdSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    thresholdSlider.setPopupDisplayEnabled (true, false, this);
    thresholdSlider.setTextValueSuffix (" Threshold");
    thresholdSlider.setValue(0.05f);
    addAndMakeVisible(&thresholdSlider);
    // 硬/软剪切切换按钮
    hardSoftToggle.setButtonText("Hard/Soft");
    hardSoftToggle.setClickingTogglesState(true);
    hardSoftToggle.addListener(this);
    hardSoftToggle.setColour(juce::ToggleButton::textColourId, juce::Colours::black);
    hardSoftToggle.setColour(juce::ToggleButton::tickColourId, juce::Colours::black);
    hardSoftToggle.setColour(juce::ToggleButton::tickDisabledColourId, juce::Colours::black);
    addAndMakeVisible(&hardSoftToggle);

}

DistortionAudioProcessorEditor::~DistortionAudioProcessorEditor()
{
}

void DistortionAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
  audioProcessor.threshold = thresholdSlider.getValue();
}

void DistortionAudioProcessorEditor::buttonClicked (juce::Button* button)
{
  audioProcessor.hardSoft = !audioProcessor.hardSoft;
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
    hardSoftToggle.setBounds(100, 10, 100, getHeight() - 20);
}