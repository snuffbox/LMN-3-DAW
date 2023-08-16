#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessor::AudioPluginAudioProcessor()
    : AudioProcessor(
          BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
              .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
              .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
              ),
      state(*this, nullptr, "PARAMETERS",
            {std::make_unique<juce::AudioParameterBool>(
                 editorIsVisibleId, editorIsVisibleName, false),
             std::make_unique<juce::AudioParameterChoice>(
                 "chordShape", "Chord Shape", chordShapeNames, 0),
             std::make_unique<juce::AudioParameterChoice>(
                 "arpPattern", "Arp Pattern", chordShapeNames, 0),
             std::make_unique<juce::AudioParameterChoice>(
                 "noteDivision", "Note Division", noteDivisionNames, 0),
             std::make_unique<juce::AudioParameterInt>(
                 "octaves", "Octaves", 1, 3, 1)

            }) {
}

AudioPluginAudioProcessor::~AudioPluginAudioProcessor() {}

//==============================================================================
const juce::String AudioPluginAudioProcessor::getName() const {
    return JucePlugin_Name;
}

bool AudioPluginAudioProcessor::acceptsMidi() const {
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool AudioPluginAudioProcessor::producesMidi() const {
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool AudioPluginAudioProcessor::isMidiEffect() const {
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double AudioPluginAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int AudioPluginAudioProcessor::getNumPrograms() {
    return 1; // NB: some hosts don't cope very well if you tell them there are
              // 0 programs, so this should be at least 1, even if you're not
              // really implementing programs.
}

int AudioPluginAudioProcessor::getCurrentProgram() { return 0; }

void AudioPluginAudioProcessor::setCurrentProgram(int index) {
    juce::ignoreUnused(index);
}

const juce::String AudioPluginAudioProcessor::getProgramName(int index) {
    juce::ignoreUnused(index);
    return {};
}

void AudioPluginAudioProcessor::changeProgramName(int index,
                                                  const juce::String &newName) {
    juce::ignoreUnused(index, newName);
}

//==============================================================================
void AudioPluginAudioProcessor::prepareToPlay(double sampleRate,
                                              int samplesPerBlock) {
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::ignoreUnused(sampleRate, samplesPerBlock);
}

void AudioPluginAudioProcessor::releaseResources() {
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool AudioPluginAudioProcessor::isBusesLayoutSupported(
    const BusesLayout &layouts) const {
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() &&
        layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

        // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}

void AudioPluginAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer,
                                             juce::MidiBuffer &midiMessages) {
    bool editorIsVisible =
        *(state.getRawParameterValue(editorIsVisibleId)) > .5f;
    // Get tempo from playhead
    double tempo = getPlayHead()->getCurrentPosition().bpm;

    // Calculate note duration
    double beatDuration = 60.0 / tempo;
    double noteDuration;
    switch (noteDivision) {
        case QUARTER:
            noteDuration = beatDuration;
            break;
        case EIGHTH:
            noteDuration = beatDuration / 2;
            break;
        case SIXTEENTH:
            noteDuration = beatDuration / 4;
            break;
        case THIRTY_SECOND:
            noteDuration = beatDuration / 8;
            break;
    }

    juce::MidiBuffer processedMidi;
    for (const auto metadata : midiMessages) {
        auto message = metadata.getMessage();
        if (message.isNoteOn()) {
            auto chordNotes = generateChordNotes(message.getNoteNumber(), chordShape, octaves);
            auto arpNotes = applyArpPattern(chordNotes, arpPattern);
            scheduleMidiNotes(processedMidi, arpNotes, noteDuration, metadata.samplePosition, getSampleRate());
        }
    }

    if (editorIsVisible) {
        int increaseValueFlag = 1;
        int decreaseValueFlag = 127;
        for (auto messageData : midiMessages) {
            if (messageData.getMessage().isController()) {
                if (messageData.getMessage().getControllerNumber() == 3) {
                    float currentValue =
                        state.getParameter(parameter1Id)->getValue();
                    if (messageData.getMessage().getControllerValue() ==
                        increaseValueFlag) {
                        state.getParameter(parameter1Id)
                            ->setValueNotifyingHost(currentValue + .01f);
                    }

                    if (messageData.getMessage().getControllerValue() ==
                        decreaseValueFlag) {
                        state.getParameter(parameter1Id)
                            ->setValueNotifyingHost(currentValue - .01f);
                    }
                }

                if (messageData.getMessage().getControllerNumber() == 9) {
                    float currentValue =
                        state.getParameter(parameter2Id)->getValue();
                    if (messageData.getMessage().getControllerValue() ==
                        increaseValueFlag) {
                        state.getParameter(parameter2Id)
                            ->setValueNotifyingHost(currentValue + .01f);
                    }

                    if (messageData.getMessage().getControllerValue() ==
                        decreaseValueFlag) {
                        state.getParameter(parameter2Id)
                            ->setValueNotifyingHost(currentValue - .01f);
                    }
                }

                if (messageData.getMessage().getControllerNumber() == 14) {
                    float currentValue =
                        state.getParameter(parameter3Id)->getValue();
                    if (messageData.getMessage().getControllerValue() ==
                        increaseValueFlag) {
                        state.getParameter(parameter3Id)
                            ->setValueNotifyingHost(currentValue + .01f);
                    }

                    if (messageData.getMessage().getControllerValue() ==
                        decreaseValueFlag) {
                        state.getParameter(parameter3Id)
                            ->setValueNotifyingHost(currentValue - .01f);
                    }
                }

                if (messageData.getMessage().getControllerNumber() == 15) {
                    float currentValue =
                        state.getParameter(parameter4Id)->getValue();
                    if (messageData.getMessage().getControllerValue() ==
                        increaseValueFlag) {
                        state.getParameter(parameter4Id)
                            ->setValueNotifyingHost(currentValue + .01f);
                    }

                    if (messageData.getMessage().getControllerValue() ==
                        decreaseValueFlag) {
                        state.getParameter(parameter4Id)
                            ->setValueNotifyingHost(currentValue - .01f);
                    }
                }
            }
        }
    }

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel) {
        auto *channelData = buffer.getWritePointer(channel);
        juce::ignoreUnused(channelData);
        // ..do something to the data...
    }
    midiMessages.swapWith(processedMidi);
}
//==============================================================================
    std::vector<int> generateChordNotes(int rootNote, ChordShapes chordShape, int octaves) {
        // Define the intervals for the selected chord shape
        std::vector<int> intervals;
        switch (chordShape) {
            case MAJOR:
                intervals = {0, 4, 7};
                break;
            case MINOR:
                intervals = {0, 3, 7};
                break;
            // Add other chord shapes as needed
        }

        // Generate the chord notes for the selected number of octaves
        std::vector<int> chordNotes;
        for (int octave = 0; octave < octaves; ++octave) {
            for (int interval : intervals) {
                int note = rootNote + interval + (12 * octave); // Add 12 for each additional octave
                chordNotes.push_back(note);
            }
        }

        return chordNotes;
    }
//==============================================================================
    std::vector<int> applyArpPattern(const std::vector<int>& chordNotes, ArpPatterns arpPattern) {
        std::vector<int> arpNotes;

        switch (arpPattern) {
            case UP:
                arpNotes = chordNotes; // Play notes in ascending order
                break;

            case DOWN:
                arpNotes = chordNotes; // Play notes in descending order
                std::reverse(arpNotes.begin(), arpNotes.end());
                break;

            case PING_PONG:
                arpNotes = chordNotes; // Play notes in ascending and then descending order
                arpNotes.insert(arpNotes.end(), chordNotes.rbegin() + 1, chordNotes.rend() - 1);
                break;

            case RANDOM:
                arpNotes = chordNotes; // Play notes in random order starting with root note
                std::random_shuffle(arpNotes.begin() + 1, arpNotes.end());
                break;
        }

        return arpNotes;
    }
//==============================================================================
    void scheduleMidiNotes(juce::MidiBuffer& processedMidi, const std::vector<int>& arpNotes,
                        double noteDuration, int originalSamplePosition, double sampleRate) {
        // Convert note duration from seconds to samples
        int sampleDuration = static_cast<int>(noteDuration * sampleRate);

        // Schedule MIDI notes
        for (int i = 0; i < arpNotes.size(); ++i) {
            int note = arpNotes[i];
            int samplePosition = originalSamplePosition + i * sampleDuration;

            // Schedule note-on message
            processedMidi.addEvent(juce::MidiMessage::noteOn(1, note, (juce::uint8)127), samplePosition);

            // Schedule corresponding note-off message
            processedMidi.addEvent(juce::MidiMessage::noteOff(1, note), samplePosition + sampleDuration);
        }
    }
//==============================================================================

//==============================================================================
bool AudioPluginAudioProcessor::hasEditor() const {
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor *AudioPluginAudioProcessor::createEditor() {
    return new AudioPluginAudioProcessorEditor(*this);
}

//==============================================================================
void AudioPluginAudioProcessor::getStateInformation(
    juce::MemoryBlock &destData) {
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::ignoreUnused(destData);
}

void AudioPluginAudioProcessor::setStateInformation(const void *data,
                                                    int sizeInBytes) {
    // You should use this method to restore your parameters from this memory
    // block, whose contents will have been created by the getStateInformation()
    // call.
    juce::ignoreUnused(data, sizeInBytes);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
    return new AudioPluginAudioProcessor();
}
