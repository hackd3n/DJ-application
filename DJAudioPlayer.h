#pragma once
// assumes your JuceHeader file is here
// check your MainComponent.h to see
// how the include is configured on your
// system
#include "../JuceLibraryCode/JuceHeader.h"
class DJAudioPlayer : public juce::AudioSource
{
public:
	DJAudioPlayer(juce::AudioFormatManager& formatManager);
	~DJAudioPlayer();
	void loadURL(const juce::URL& file);
	/** start playing the file */
	void play();
	void pause();
	/** stop playing the file */
	void stop();
	
	void setMinLoop(double _min);
	void setMaxLoop(double _max);

	/** set time position in seconds */
	void setPosition(double posInSecs);
	void setGain(double gain);

	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
	void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
	void releaseResources() override;

	void setPositionRelative(double pos);
	
	void setSpeed(double _speed);

	/** get the relative position of the play head */
	double getPositionRelative();

	double pPos;
private:
	juce::AudioFormatManager& formatManager;
	std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
	juce::AudioTransportSource transportSource;

	bool isPlaying;
	juce::ResamplingAudioSource resampleSource{ &transportSource, false, 2 };

};
