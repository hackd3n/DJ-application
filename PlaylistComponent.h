/*
  ==============================================================================

    PlaylistComponent.h
    Created: 4 Apr 2022 2:27:48pm
    Author:  hacke

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "DJAudioPlayer.h"

//==============================================================================
/*
*/
class PlaylistComponent  : public juce::Component,
	public juce::TableListBoxModel,
	public juce::Button::Listener
{
public:
    //PlaylistComponent(DJAudioPlayer * _djAudioPlayer);
    PlaylistComponent();
    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
	int getNumRows() override;
	void paintRowBackground(juce::Graphics &, int rowNumber, int width, int height, bool rowIsSelected) override;
	void paintCell(juce::Graphics &, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
	juce::Component * refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate) override;
	
	void cellClicked(int rowNumber, int columnId, const juce::MouseEvent&) override;
	void buttonClicked(juce::Button* button) override;

	//void queueList(juce::URL _fileToQueue);

	enum {
		ID_PLAY = 1,
		ID_TRACK_TITLE = 2,
		ARTIST_ID = 3,
		DURATION_ID = 4
	};

	struct TrackInfo {
		juce::String title;
		std::string artist;
		std::string seconds;
		std::string filePath;
	};

	std::vector<TrackInfo> trackInfos;
private:

	juce::TextButton newPlaylist{ "New Track..." };
	juce::TableListBox tableComponent;
	std::vector<std::string> trackTitles;
	std::ifstream myFile;

	DJAudioPlayer * djAudioPlayer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
