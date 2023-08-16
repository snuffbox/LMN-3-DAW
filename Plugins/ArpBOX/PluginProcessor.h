#pragma once
#include <juce_audio_processors/juce_audio_processors.h>

//==============================================================================
class AudioPluginAudioProcessor : public juce::AudioProcessor {
  public:
    const juce::String editorIsVisibleId = "editorIsVisible";
    const juce::String editorIsVisibleName = "Editor Is Visible";
/*     const juce::String parameter1Id = "parameter1";
    const juce::String parameter1Name = "Parameter 1";
    const juce::String parameter2Id = "parameter2";
    const juce::String parameter2Name = "Parameter 2";
    const juce::String parameter3Id = "parameter3";
    const juce::String parameter3Name = "Parameter 3";
    const juce::String parameter4Id = "parameter4";
    const juce::String parameter4Name = "Parameter 4"; */
    //==============================================================================
    enum ChordShapes { MAJOR, MINOR /*, ... */ };
    enum ArpPatterns { UP, DOWN, PING_PONG, RANDOM };
    enum NoteDivision { QUARTER, EIGHTH, SIXTEENTH, THIRTY_SECOND };

    const juce::StringArray chordShapeNames = {"Major", "Minor" /*, ... */};
    const juce::StringArray arpPatternNames = {"Up", "Down", "Ping Pong", "Random"};
    const juce::StringArray noteDivisionNames = {"1/4", "1/8", "1/16", "1/32"};

    static const juce::StringArray chordShapeNames;
    static const juce::StringArray arpPatternNames;
    static const juce::StringArray noteDivisionNames;

    juce::AudioProcessorValueTreeState state;

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
