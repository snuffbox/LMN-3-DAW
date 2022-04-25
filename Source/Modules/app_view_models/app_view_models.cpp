#include "app_view_models.h"

// Utilities
#include "Utilities/EngineHelpers.cpp"
#include "Utilities/FlaggedAsyncUpdater.cpp"

// EditItemList
#include "Edit/ItemList/EditItemListViewModel.cpp"
#include "Edit/ItemList/ItemListState.cpp"
#include "Edit/ItemList/ListAdapters/MixerTracksListAdapter.cpp"
#include "Edit/ItemList/ListAdapters/ModifierPluginDestinationsListAdapter.cpp"
#include "Edit/ItemList/ListAdapters/ModifiersListAdapter.cpp"
#include "Edit/ItemList/ListAdapters/PluginsListAdapter.cpp"
#include "Edit/ItemList/ListAdapters/TracksListAdapter.cpp"

// Tracks
#include "Edit/Tracks/TrackViewModel.cpp"
#include "Edit/Tracks/TracksListViewModel.cpp"

// Plugins
#include "Edit/Plugins/AvailablePluginsViewModel.cpp"
#include "Edit/Plugins/ChorusPluginViewModel.cpp"
#include "Edit/Plugins/CompressorPluginViewModel.cpp"
#include "Edit/Plugins/DelayPluginViewModel.cpp"
#include "Edit/Plugins/EqualiserPluginViewModel.cpp"
#include "Edit/Plugins/FourOsc/ADSRViewModel.cpp"
#include "Edit/Plugins/FourOsc/FilterViewModel.cpp"
#include "Edit/Plugins/FourOsc/OscillatorViewModel.cpp"
#include "Edit/Plugins/FourOscPluginViewModel.cpp"
#include "Edit/Plugins/InternalPluginViewModel.cpp"
#include "Edit/Plugins/LowPassPluginViewModel.cpp"
#include "Edit/Plugins/PhaserPluginViewModel.cpp"
#include "Edit/Plugins/PluginTree/PluginTreeBase.cpp"
#include "Edit/Plugins/PluginTree/PluginTreeGroup.cpp"
#include "Edit/Plugins/PluginTree/PluginTreeItem.cpp"
#include "Edit/Plugins/ReverbPluginViewModel.cpp"
#include "Edit/Plugins/Sampler/DrumSamplerViewModel.cpp"
#include "Edit/Plugins/Sampler/SamplerViewModel.cpp"
#include "Edit/Plugins/Sampler/SynthSamplerViewModel.cpp"
#include "Edit/Plugins/TrackPluginsListViewModel.cpp"

// Modifiers
#include "Edit/Modifiers/AvailableModifiersListViewModel.cpp"
#include "Edit/Modifiers/AvailablePluginParametersListViewModel.cpp"
#include "Edit/Modifiers/LFOModifierViewModel.cpp"
#include "Edit/Modifiers/ModifierList.cpp"
#include "Edit/Modifiers/ModifierPluginDestinationsViewModel.cpp"
#include "Edit/Modifiers/ModifierViewModel.cpp"
#include "Edit/Modifiers/TrackModifiersListViewModel.cpp"

// Tempo
#include "Edit/Tempo/TempoSettingsViewModel.cpp"

// Sequencers
#include "Edit/Sequencers/AvailableSequencersListViewModel.cpp"
#include "Edit/Sequencers/StepSequencerViewModel.cpp"

// Mixer
#include "Edit/Mixer/MixerTrackViewModel.cpp"
#include "Edit/Mixer/MixerViewModel.cpp"

// Settings
#include "Edit/Settings/AudioBufferSizeListViewModel.cpp"
#include "Edit/Settings/DeviceTypeListViewModel.cpp"
#include "Edit/Settings/OutputListViewModel.cpp"
#include "Edit/Settings/SampleRateListViewModel.cpp"
#include "Edit/Settings/SettingsListViewModel.cpp"