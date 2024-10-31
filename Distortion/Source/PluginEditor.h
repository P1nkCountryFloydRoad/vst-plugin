/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class DistortionAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                        private juce::Slider::Listener,
                                        public juce::Button::Listener
{
public:
    DistortionAudioProcessorEditor (DistortionAudioProcessor&);
    ~DistortionAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    void sliderValueChanged (juce::Slider* slider) override; 
    void buttonClicked (juce::Button* button) override;
    DistortionAudioProcessor& audioProcessor;
    juce::Slider thresholdSlider;
    juce::Slider thresholdSlider1;
    juce::ToggleButton hardSoftToggle;
    // juce::Label thresholdLabel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionAudioProcessorEditor)
};