/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Metronome.h"
#include "Visualiser.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent,
						public Slider::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;

	void play();
	void stop();

	void sliderValueChanged(Slider* slider) override;

	enum class PlayState
	{
		Playing, 
		Stopped
	};

private:
    
	int mBPM = 60;
	TextButton mPlayButton{ "Play" };
	TextButton mStopButton{ "Stop" };
	Slider mBPMSlider;
	Label mBPMLabel;

	PlayState mPlayState{ PlayState::Stopped };

	Metronome mMetronome;
	Visualiser mVisualiser;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
