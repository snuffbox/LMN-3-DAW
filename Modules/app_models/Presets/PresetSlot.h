namespace app_models {

    class PresetSlot {

    public:
        PresetSlot(const juce::ValueTree &v);

        // state must be public since traction object list accesses it directly
        juce::ValueTree state;
        Preset preset;

        int getNumber();

    private:

        juce::CachedValue<int> number;

    };

}
