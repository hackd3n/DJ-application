/*
  ==============================================================================

    DeckGUI.h
    Created: 13 Mar 2022 1:51:34pm
    Author:  hacke

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"



//==============================================================================
/*
*/
class DeckGUI  : public juce::Component,
				public juce::Button::Listener,
				public juce::Slider::Listener,
				public juce::FileDragAndDropTarget,
				public juce::Timer
{
public:
	DeckGUI(DJAudioPlayer * _djAudioPlayer, juce::AudioFormatManager& formatManagerTool, juce::AudioThumbnailCache& cacheToUse);
    ~DeckGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

	void buttonClicked(juce::Button * button) override;
	void sliderValueChanged(juce::Slider * slider) override;

	bool isInterestedInFileDrag(const juce::StringArray& files) override;
	void filesDropped(const juce::StringArray& files, int x, int y) override;
	void timerCallback() override;



private:
	juce::TextButton playButton{ "PLAY" };
	juce::TextButton pauseButton{ "PAUSE" };
	juce::TextButton stopButton{ "STOP" };
	juce::TextButton loadButton{ "LOAD FILE" };
	juce::Slider volumeSlider;
	juce::Slider positionSlider;
	juce::Slider speedSlider;
	juce::Slider setLoopPosition;


	DJAudioPlayer * djAudioPlayer;
	WaveformDisplay waveformDisplay;

	bool isPlaying;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
