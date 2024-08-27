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
class PhaserAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    PhaserAudioProcessor();
    ~PhaserAudioProcessor() override;

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
    LFO lfo;  // 低频振荡器，用于调制相位
    AllPassFilter allPassFilters[4];  // 全通滤波器，用于实现相位移动效果
    SimplePhaser phaser;  // 简单的相位器
    float depth;  // 深度参数
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PhaserAudioProcessor)
};

class AllPassFilter
{
public:
    AllPassFilter() : alpha(0.0f), z1(0.0f) {}

    // 设置全通滤波器的系数，通常由LFO调制
    void setAlpha(float newAlpha)
    {
        alpha = newAlpha;
    }

    // 处理单个样本
    float processSample(float inputSample)
    {
        // 全通滤波器公式实现
        float outputSample = (alpha * inputSample + z1 - alpha * z1) / (1.0f + alpha);
        z1 = inputSample - alpha * outputSample;
        return outputSample;
    }

private:
    float alpha;  // 滤波器系数
    float z1;     // 记录上一个样本的状态（延迟元素）
};

class SimplePhaser
{
public:
    SimplePhaser()
        : sampleRate(44100.0), lfo(), depth(1.0f)
    {
        lfo.setFrequency(0.5f); // 设置LFO频率为0.5Hz
        for (auto& filter : allPassFilters)
        {
            filter.setAlpha(0.0f);
        }
    }

    void setSampleRate(double newSampleRate)
    {
        sampleRate = newSampleRate;
        lfo.setSampleRate(sampleRate);
    }

    void setDepth(float newDepth)
    {
        depth = newDepth;
    }
private:
    double sampleRate;
    LFO lfo;  // 低频振荡器，用于调制相位
    float depth;
    static const int numFilters = 4;  // 使用4个全通滤波器实现Phaser
    AllPassFilter allPassFilters[numFilters];  // 全通滤波器的数组
};

class LFO
{
public:
    LFO() : sampleRate(44100.0), frequency(1.0), phase(0.0), phaseIncrement(0.0)
    {
        setFrequency(frequency);
    }

    void setFrequency(float newFrequency)
    {
        frequency = newFrequency;
        phaseIncrement = (float)(2.0 * juce::MathConstants<double>::pi * frequency / sampleRate);
    }

    void setSampleRate(double newSampleRate)
    {
        sampleRate = newSampleRate;
        setFrequency(frequency); // Update phase increment
    }

    float getNextSample()
    {
        // Generate a sine wave for simplicity, but this can be changed to any waveform
        float currentSample = std::sin(phase);

        phase += phaseIncrement;
        if (phase >= 2.0 * juce::MathConstants<double>::pi)
            phase -= 2.0 * juce::MathConstants<double>::pi;

        return currentSample;
    }

private:
    double sampleRate;
    float frequency;
    float phase;
    float phaseIncrement;
};
