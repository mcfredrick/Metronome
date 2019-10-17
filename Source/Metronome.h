/*
  ==============================================================================

    Metronome.h
    Created: 7 Oct 2019 1:10:07pm
    Author:  mattc

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class Metronome

{
public:
	Metronome();

	void prepareToPlay(double samplesPerBlockExpected, double sampleRate);
	void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill);
	void readInSample();
	void setBPM(float BPM);

private:
	//audio device state variables
	int mTotalSamples{ 512 };
	int mSampleRate{ 44100 };

	//user variables
	std::atomic<int> mBPM = 60;

	//calculated variables
	int mSamplesPerBlock;
	int mClickLength;								//actual length of the click in samples
	int mSamplesPerBeat{ 60 / mBPM * mSampleRate };	//number of samples at current rate and BPM

	int mSamplesRemaining{ 0 };

	int position;

	AudioFormatManager mFormatManager;
	std::unique_ptr<AudioFormatReaderSource> pMetronomeSample{ nullptr };
	AudioSampleBuffer clickSampleBuffer;
};