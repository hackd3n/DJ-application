/*
  ==============================================================================

    WaveformDisplay.h
    Created: 16 Mar 2022 9:26:27am
    Author:  hacke

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformDisplay  : public juce::Component, public juce::ChangeListener
{
public:
    WaveformDisplay(juce::AudioFormatManager& formatManagerToUse, juce::AudioThumbnailCache& cacheToUse);
    ~WaveformDisplay() override;

    void paint (juce::Graphics&) override;
    void resized() override;

	void loadURL(juce::URL audioURL);
	void changeListenerCallback(juce::ChangeBroadcaster * source) override;

	/** set the relative position of the play head*/
	void setPositionRelative(double pos);

	//void mouseDown(const juce::mouseEvent &event) override;
	//void mouseUp(const juce::mouseEvent &event) override;

private:
	juce::AudioThumbnail audioThumbnail;

	bool fileLoaded = false;

	double position;

	double minPos;
	double maxPos;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
