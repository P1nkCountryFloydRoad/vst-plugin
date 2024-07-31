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
class IIRFilterAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    IIRFilterAudioProcessor();
    
    IIRFilterAudioProcessor(double b0, double b1, double b2, double a1, double a2)
      : b0(b0), b1(b1), b2(b2), a1(a1), a2(a2), x1(0), x2(0), y1(0), y2(0)
    #ifndef JucePlugin_PreferredChannelConfigurations
     , AudioProcessor (BusesProperties()
                      #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
    #endif
       {}

    double process(double x) {
        // 计算当前输出信号
        double y = b0 * x + b1 * x1 + b2 * x2 - a1 * y1 - a2 * y2;
        // 更新历史值
x        x2 = x1;
        x1 = x;
        y2 = y1;
        y1 = y;
        return y;
    }
    ~IIRFilterAudioProcessor() override;

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
    double b0, b1, b2, a1, a2; // 滤波器系数
    double x1, x2;             // 上两个输入信号
    double y1, y2;             // 上两个输出信号
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IIRFilterAudioProcessor)
};
