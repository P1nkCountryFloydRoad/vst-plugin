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
class FuzzAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                  private juce::Slider::Listener
{
public:
    FuzzAudioProcessorEditor (FuzzAudioProcessor&);
    ~FuzzAudioProcessorEditor() override;
    

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    void sliderValueChanged (juce::Slider* slider) override;
    FuzzAudioProcessor& audioProcessor;
    juce::Slider gainSlider;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FuzzAudioProcessorEditor)
};
