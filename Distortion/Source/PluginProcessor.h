/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class DistortionAudioProcessor  : public juce::AudioProcessor
{
public:
    float threshold = 0.5;
    bool hardSoft = true;
    //==============================================================================
    DistortionAudioProcessor();
    ~DistortionAudioProcessor() override;
    //==============================================================================
    // 硬剪切失真
    float hardClip(float input, float threshold){
        if (input > threshold){
            return threshold;
        }
        else if (input < -threshold){
            return -threshold;
        }
        else{
            return input;
        }
    }
    // 软剪切失真
    float softClip(float input, float threshold){ // tanh(x)
        if (input > threshold){
            return 1 - exp(-input);
        }
        else if (input < -threshold){
            return -1 + exp(input);
        }
        else{
            return input;
        }
    }

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionAudioProcessor)
};