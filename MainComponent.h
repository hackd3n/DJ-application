#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

#include "DeckGUI.h"
#include "PlaylistComponent.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent, public juce::Button::Listener, public juce::Slider::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

	//==============================================================================
	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
	void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
	void releaseResources() override;
	void buttonClicked(juce::Button* button) override;
	void sliderValueChanged(juce::Slider* slider) override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...

	juce::MixerAudioSource mixerSource;

	juce::Slider crossfade;

	juce::AudioFormatManager formatManager;
	// note we need to tell it how large the cache is. 20 files are ok for now.
	juce::AudioThumbnailCache thumbCache{ 20 };

	DJAudioPlayer player1{ formatManager };
	DeckGUI deckGUI1{ &player1, formatManager, thumbCache };
	DJAudioPlayer player2{ formatManager };
	DeckGUI deckGUI2{ &player2, formatManager, thumbCache };

	PlaylistComponent playlistComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
