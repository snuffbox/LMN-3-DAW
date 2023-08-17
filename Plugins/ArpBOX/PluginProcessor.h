#pragma once
#include <juce_audio_processors/juce_audio_processors.h>

//==============================================================================
class AudioPluginAudioProcessor : public juce::AudioProcessor {
  public:
    const juce::String editorIsVisibleId = "editorIsVisible";
    const juce::String editorIsVisibleName = "Editor Is Visible";

    enum ChordShapes { MAJOR, MINOR /*, ... */ };
    enum ArpPatterns { UP, DOWN, PING_PONG, RANDOM };
    enum NoteDivision { QUARTER, EIGHTH, SIXTEENTH, THIRTY_SECOND };

    static const juce::StringArray chordShapeNames;
    static const juce::StringArray arpPatternNames;
    static const juce::StringArray noteDivisionNames;

    std::vector<int> generateChordNotes(int rootNote, ChordShapes chordShape, int octaves);
    std::vector<int> applyArpPattern(const std::vector<int>& chordNotes, ArpPatterns arpPattern);
    void scheduleMidiNotes(juce::MidiBuffer& processedMidi, const std::vector<int>& arpNotes,
                          double noteDuration, int originalSamplePosition, double sampleRate);
    //==============================================================================
    AudioPluginAudioProcessor();
    ~AudioPluginAudioProcessor() override;

    //==============================================================================
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported(const BusesLayout &layouts) const override;

    void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;

    //==============================================================================
    juce::AudioProcessorEditor *createEditor() override;
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
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String &newName) override;

    //==============================================================================
    void getStateInformation(juce::MemoryBlock &destData) override;
    void setStateInformation(const void *data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState state;

  private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessor)
};
