/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 4 Apr 2022 2:27:48pm
    Author:  hacke

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

using namespace std;
//==============================================================================
PlaylistComponent::PlaylistComponent()
{
	//data
	trackTitles.push_back("Track 1");
	trackTitles.push_back("Track 2");
	trackTitles.push_back("Track 3");
	trackTitles.push_back("Track 4");
	trackTitles.push_back("Track 5");
	trackTitles.push_back("Track 6");
	trackTitles.push_back("Track 7");
	//	trackTitles.push_back("Track 8");
	//trackTitles.push_back("Track 9");
	//trackTitles.push_back("Track 10");

	
	
	//trackInfos.push_back(TrackInfo());
	//trackInfos[0].title = "Hello World";
	//trackInfos[0].artist = "Adele";
	
	tableComponent.getHeader().addColumn("", ID_PLAY, 50);
	tableComponent.getHeader().addColumn("Track Title",ID_TRACK_TITLE, 200);
	tableComponent.getHeader().addColumn("Artist", ARTIST_ID, 200);
	tableComponent.getHeader().addColumn("Duration", DURATION_ID, 100);
	tableComponent.setModel(this);
	addAndMakeVisible(tableComponent);
	addAndMakeVisible(newPlaylist);

	newPlaylist.addListener(this);

	//load CSV file
	myFile.open("C:\\Users\\hacke\\Documents\\JUCE PROJECTS\\reFactor\\Source\\myPlaylist.csv");
	
	//if playlist file loaded
	if (myFile.good()) {
		DBG("Playlist Loaded");
	}

	string line = "*"; 
	//push back data into vector
	while (getline(myFile, line)) {
		string firstCol;
		string secondCol;
		string thirdCol;
		string forthCol;
		getline(myFile, firstCol, ',');
		getline(myFile, secondCol, ',');
		getline(myFile, thirdCol, ',');
		getline(myFile, forthCol, ',');

		trackInfos.push_back(TrackInfo());
		trackInfos.back().title = firstCol;
		trackInfos.back().artist = secondCol;
		trackInfos.back().seconds = thirdCol;
		trackInfos.back().filePath = forthCol;

		line = "*";
	}

	myFile.close();
}

PlaylistComponent::~PlaylistComponent() 
{
}

void PlaylistComponent::paint (juce::Graphics& g)
{
 
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("PlaylistComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{
	newPlaylist.setBounds(0,0,getWidth(), 30);
	tableComponent.setBounds(0, 30, getWidth(), getHeight());

}

int PlaylistComponent::getNumRows() {
	return trackInfos.size();
}

void PlaylistComponent::paintRowBackground(juce::Graphics & g, int rowNumber, int width, int height, bool rowIsSelected) {
	if (rowIsSelected) {
		g.fillAll(juce::Colours::orange);
	}
	else {
		g.fillAll(juce::Colours::darkslategrey);
	}
}

void PlaylistComponent::paintCell(juce::Graphics & g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) {
	
	if (columnId == 2) {
		g.drawText(trackInfos[rowNumber].title,
			2,
			0,
			width - 4,
			height,
			juce::Justification::centredLeft,
			true);
	}
	else if (columnId == 3) {
		g.drawText(trackInfos[rowNumber].artist,
			2,
			0,
			width - 4,
			height,
			juce::Justification::centredLeft,
			true);
	}
	else if (columnId == 4) {
		//std::string _dur = std::to_string(trackInfos[rowNumber].seconds);
		string _dur = trackInfos[rowNumber].seconds;
		g.drawText(_dur,
			2,
			0,
			width - 4,
			height,
			juce::Justification::centredLeft,
			true);
	}
	else {
		g.drawText(" - ",
			2,
			0,
			width - 4,
			height,
			juce::Justification::centredLeft,
			true);
	}

}

juce::Component * PlaylistComponent::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, juce::Component *existingComponentToUpdate) {
	
	if (columnId == ID_PLAY) {
		//IF NOT YET CREATED
		if (existingComponentToUpdate == nullptr) {
			juce::TextButton* btn = new juce::TextButton{ "PLAY" };
			juce::String id{ std::to_string(rowNumber) };
			btn->setComponentID(id);

			btn->addListener(this);

			existingComponentToUpdate = btn; //text button is a child class
		}
	}
	return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked(juce::Button* button) {
	//convert back from string to int
	int id = std::stoi(button->getComponentID().toStdString());
	
	DBG("play pressed : " << id);
	juce::String filePath_ = trackInfos[id].filePath;
	//queueList(juce::URL("C://Users//hacke//Music//166434__ultradust__concert-applause-1.wav"));

	if (&newPlaylist == button) {
		DBG("THIS WORKS");
		juce::FileChooser chooser("Select an audio file to play...");
		if (chooser.browseForFileToOpen())
		{
			auto audioURL = juce::URL{chooser.getResult()};
			trackInfos.push_back(TrackInfo());
			//trackInfos.back().title = audioURL.getFileName();
			trackInfos.back().seconds = 0.0;
		}

	}
}


void PlaylistComponent::cellClicked(int rowNumber, int columnId, const juce::MouseEvent&) {
	//PRINT OUT CELL PRESSED DBG()
}

//void readFile(const juce::File& fileToRead) {
//	if (!fileToRead.existsAsFile())
//		return;  // file doesn't exist
//
//	juce::FileInputStream inputStream(fileToRead); // [2]
//
//	if (!inputStream.openedOk())
//		return;  // failed to open
//		textContent->clear();
//
//		auto normalFont = textContent->getFont();
//		auto titleFont = normalFont.withHeight(normalFont.getHeight() * 1.5f).boldened();
//		juce::String asterix("*");
//		while (!inputStream.isExhausted()) // [3]
//		{
//			auto line = inputStream.readNextLine();
//
//			if (line.startsWith(asterix))
//			{
//				line = line.removeCharacters(asterix);
//				textContent->setFont(titleFont);
//			}
//			else
//			{
//				textContent->setFont(normalFont);
//			}
//
//			// append the text to the textContent
//			textContent->insertTextAtCaret(line + juce::newLine);
//		}
//	}
//}

//void PlaylistComponent::queueList(juce::URL _fileToQueue) {
//	
//
//	int nextTrack = trackInfos.size();
//
//	//trackInfos.
//
//	//djAudioPlayer->loadURL(_fileToQueue);
//}