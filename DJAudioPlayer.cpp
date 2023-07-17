/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 16 Feb 2022 9:16:24am
    Author:  hacke

  ==============================================================================
*/

#include "DJAudioPlayer.h"


DJAudioPlayer::DJAudioPlayer(juce::AudioFormatManager& afm) : formatManager(afm)
{
	//formatManager.registerBasicFormats();

	pPos = 0.0;
	isPlaying = false;

}

DJAudioPlayer::~DJAudioPlayer() {

}

void DJAudioPlayer::play()
{
	transportSource.setPosition(pPos);
	transportSource.start();
}

void DJAudioPlayer::pause() {
	pPos = transportSource.getCurrentPosition();
	transportSource.stop();
}

void DJAudioPlayer::stop() {
	transportSource.stop();
	pPos = 0.0;
}

void DJAudioPlayer::setPosition(double posInSecs) {
	if (posInSecs < 0 || posInSecs > transportSource.getLengthInSeconds()) {
		DBG("DJAudioPlayer::setPosition: warning set position " << posInSecs << " greater than length " << transportSource.getLengthInSeconds());
		return;
	}
	
	transportSource.setPosition(posInSecs);
}


void DJAudioPlayer::setPositionRelative(double pos)
{
	double posInSecs = pos * transportSource.getLengthInSeconds();
	setPosition(posInSecs);
}

void DJAudioPlayer::setGain(double gain) {

	if (gain < 0.0 || gain > 1.0) {
		
	}
	else
	{
		transportSource.setGain(gain);
	}
	
}

void DJAudioPlayer::setSpeed(double _speed) {
	resampleSource.setResamplingRatio(_speed);
}

void DJAudioPlayer::setMinLoop(double _min) {
	
	setPositionRelative(_min);
	transportSource.setLooping(true);

}

void DJAudioPlayer::setMaxLoop(double _max) {

	transportSource.setLooping(true);
}

void DJAudioPlayer::loadURL(const juce::URL& audioURL)
{
	
	auto * reader = formatManager.createReaderFor(audioURL.createInputStream(false));
	
	if (reader) // good file!
	{
		std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true));
		transportSource.setSource(newSource.get(), 0, nullptr, reader -> sampleRate);
		readerSource.reset(newSource.release());
		DBG("loadURL working");
	}
	
}

void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	//transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
	resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void DJAudioPlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
	if (!readerSource.get())
	{
		bufferToFill.clearActiveBufferRegion();
		return;
	}
	//transportSource.getNextAudioBlock(bufferToFill);
	resampleSource.getNextAudioBlock(bufferToFill);
}

void DJAudioPlayer::releaseResources()
{
	transportSource.releaseResources();
}

double DJAudioPlayer::getPositionRelative()
{
	return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}

