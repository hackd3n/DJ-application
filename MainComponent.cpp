#include "MainComponent.h"


//==============================================================================
MainComponent::MainComponent()
{
	// Make sure you set the size of the component after
	// you add any child components.
	setSize(800, 600);
	addAndMakeVisible(deckGUI1);
	addAndMakeVisible(deckGUI2);
	addAndMakeVisible(playlistComponent);

	// Some platforms require permissions to open input channels so request that here
	if (juce::RuntimePermissions::isRequired(juce::RuntimePermissions::recordAudio)
		&& !juce::RuntimePermissions::isGranted(juce::RuntimePermissions::recordAudio))
	{
		juce::RuntimePermissions::request(juce::RuntimePermissions::recordAudio,
			[&](bool granted) { setAudioChannels(granted ? 2 : 0, 2); });
	}
	else
	{
		// Specify the number of input and output channels that we want to open
		setAudioChannels(2, 2);
	}

	//addAndMakeVisible(crossfade);
	crossfade.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
	crossfade.setRange(-1.0f, 1.0f, 0.05f);
	crossfade.setValue(0.0);

	formatManager.registerBasicFormats(); //waveform -audiothumbnail
}

MainComponent::~MainComponent()
{
	// This shuts down the audio device and clears the audio source.
	shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	mixerSource.addInputSource(&player1, false);
	mixerSource.addInputSource(&player2, false);
	// note that this will call prepareToPlay
	// automatically on the two players
	mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
	// so this is not needed:
	//player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
	//player2.prepareToPlay(samplesPerBlockExpected, sampleRate);

}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
	mixerSource.getNextAudioBlock(bufferToFill);
}


void MainComponent::releaseResources()
{
	mixerSource.removeAllInputs();
	mixerSource.releaseResources();
	player1.releaseResources();
	player2.releaseResources();

}

//==============================================================================
void MainComponent::paint(juce::Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

	// You can add your drawing code here!
}

void MainComponent::resized()
{
	deckGUI1.setBounds(0, 0, getWidth() / 2, getHeight()/2);
	deckGUI2.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight()/2);
	playlistComponent.setBounds(0, getHeight() / 2, getWidth(), getHeight() / 2);
	crossfade.setBounds(0, getHeight()*0.9, getWidth(), getHeight()*0.1);
}



void MainComponent::buttonClicked(juce::Button* button)
{
}
void MainComponent::sliderValueChanged(juce::Slider* slider)
{
}

