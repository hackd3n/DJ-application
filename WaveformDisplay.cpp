/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 16 Mar 2022 9:26:27am
    Author:  hacke

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(juce::AudioFormatManager& formatManagerToUse, juce::AudioThumbnailCache& cacheToUse) : audioThumbnail(1000, formatManagerToUse, cacheToUse), fileLoaded(false), position(0)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

	audioThumbnail.addChangeListener(this);
	//minPos = 0;
	//maxPos = 0;


}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint(juce::Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
	g.setColour(juce::Colours::grey);
	g.drawRect(getLocalBounds(), 1);
	g.setColour(juce::Colours::pink);
	if (fileLoaded)
	{
		audioThumbnail.drawChannel(g, getLocalBounds(), 0, audioThumbnail.getTotalLength(), 0, 1.0f);
			g.setColour(juce::Colours::lightblue);
			g.drawRect(position * getWidth(), 0, 5, getHeight());


			auto b = juce::Rectangle<int>(0, 0, getWidth() * 0.95, getHeight() * 0.95);
			int timeStamp = int(position * audioThumbnail.getTotalLength());
			juce::String sampleLength = juce::String(audioThumbnail.getTotalLength());
			g.drawFittedText(juce::String(timeStamp), b, juce::Justification::bottomRight, 1);
	}
	else
	{
		g.setFont(20.0f);
		g.drawText("DRAG AND DROP or LOAD file", getLocalBounds(),
		juce::Justification::centred, true); // draw some placeholder text
	}


}


void WaveformDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void WaveformDisplay::loadURL(juce::URL audioURL)
{
	audioThumbnail.clear();
	fileLoaded = audioThumbnail.setSource(new juce::URLInputSource(audioURL));
}

void WaveformDisplay::changeListenerCallback(juce::ChangeBroadcaster * source)
{
	std::cout << "wfd: change received!" << std::endl;
	repaint();
}

void WaveformDisplay::setPositionRelative(double pos)
{
	if (pos != position)
	{
		position = pos;
		repaint();
	}
}

