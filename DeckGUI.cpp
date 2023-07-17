/*
  ==============================================================================

    DeckGUI.cpp
    Created: 13 Mar 2022 1:51:34pm
    Author:  hacke

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer * _player, juce::AudioFormatManager& formatManagerToUse,	juce::AudioThumbnailCache& cacheToUse) : djAudioPlayer(_player), // assign _player to our player data member
	waveformDisplay(formatManagerToUse, cacheToUse) // call the constructoron waveformDisplay
{
	addAndMakeVisible(playButton);
	addAndMakeVisible(pauseButton);
	addAndMakeVisible(stopButton);
	addAndMakeVisible(loadButton);
	addAndMakeVisible(volumeSlider);
	addAndMakeVisible(positionSlider);
	addAndMakeVisible(setLoopPosition);
	addAndMakeVisible(speedSlider);
	addAndMakeVisible(waveformDisplay);

	volumeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
	volumeSlider.setTextValueSuffix(" Vol");
	volumeSlider.setRange(0.0f, 1.0f, 0.5f);
	volumeSlider.setValue(0.5f);

	positionSlider.setRange(0.0, 1.0, 0.1);
	positionSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
	positionSlider.setTextValueSuffix(" Pos");

	setLoopPosition.setRange(0.0, 1.0, 0.1);
	setLoopPosition.setSliderStyle(juce::Slider::SliderStyle::TwoValueHorizontal);
	setLoopPosition.setMinAndMaxValues(0.0, 1.0);

	speedSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
	speedSlider.setRange(0, 5, 0.1);
	speedSlider.setTextValueSuffix("x Speed");

	playButton.addListener(this);
	pauseButton.addListener(this);
	stopButton.addListener(this);
	volumeSlider.addListener(this);
	positionSlider.addListener(this);
	setLoopPosition.addListener(this);

	speedSlider.addListener(this);
	loadButton.addListener(this);

	startTimer(200); //time call back 200ms

	isPlaying = false; //for pause toggle
}

DeckGUI::~DeckGUI()
{
	stopTimer();
}

void DeckGUI::paint(juce::Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour
	(juce::ResizableWindow::backgroundColourId)); // clear the background
}


void DeckGUI::resized()
{
	float rowH = getHeight() / 6;
	playButton.setBounds(0, 0, getWidth() * 1 / 3, rowH);
	pauseButton.setBounds(getWidth() * 1/3, 0, getWidth() * 1 / 3, rowH);
	stopButton.setBounds(getWidth() * 2 / 3, 0, getWidth() * 1 / 3, rowH);
	volumeSlider.setBounds(0, rowH, getWidth()/2, rowH);
	speedSlider.setBounds(getWidth()/2, rowH, getWidth()/2, rowH);
	positionSlider.setBounds(0, rowH * 2, getWidth(), rowH/2);
	setLoopPosition.setBounds(0, rowH * 2.5, getWidth(), rowH/2);
	waveformDisplay.setBounds(0, rowH * 3.0, getWidth(), rowH * 1.5);
	loadButton.setBounds(0, rowH * 4.5, getWidth(), rowH * 0.5);
}


void DeckGUI::buttonClicked(juce::Button* button)
{
	if (&playButton == button)
	{
			isPlaying = true;
			djAudioPlayer->play();
			DBG("PLAY BUTTON PRESSED");
			playButton.setButtonText("PLAYING");

		
	}

	if (&pauseButton == button) {
		djAudioPlayer->pause();
	}
	if (&stopButton == button)
	{
		djAudioPlayer->stop();
		djAudioPlayer->setPosition(0);
	}
	if (&loadButton == button)
	{
		juce::FileChooser chooser("Select an audio file to play...");
		if (chooser.browseForFileToOpen())
		{
			auto audioURL = juce::URL{ chooser.getResult() };
			djAudioPlayer->loadURL(audioURL);
			waveformDisplay.loadURL(audioURL);
		}
	}
}
void DeckGUI::sliderValueChanged(juce::Slider * slider)
{
	if (&volumeSlider == slider)
	{
		djAudioPlayer->setGain(slider->getValue());
	}
	if (&positionSlider == slider)
	{
		djAudioPlayer->setPositionRelative(slider->getValue());
	}
	if (&speedSlider == slider)
	{
		djAudioPlayer->setSpeed(slider->getValue());
	}

	if (&setLoopPosition == slider) {
		
		djAudioPlayer->setMinLoop(slider->getMinValue());
		DBG(slider->getMinValue());
		djAudioPlayer->setMaxLoop(slider->getMaxValue());
	}

}

bool DeckGUI::isInterestedInFileDrag(const juce::StringArray& files)
{
	std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
	return true;
}
void DeckGUI::filesDropped(const juce::StringArray& files, int x, int y)
{

	for (const auto& filename : files)
	{
		std::cout << "DeckGUI::filesDropped " << filename << std::endl;
		juce::URL fileURL = juce::URL{ juce::File{filename} };
		djAudioPlayer->loadURL(fileURL);
		
		return;

	}

}

void DeckGUI::timerCallback()
{
	std::cout << "DeckGUI::timerCallback" << std::endl;
	waveformDisplay.setPositionRelative(djAudioPlayer->getPositionRelative());
}


