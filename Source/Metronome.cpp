/*
  ==============================================================================

    Metronome.cpp
    Created: 7 Oct 2019 1:10:07pm
    Author:  mattc

  ==============================================================================
*/

#include "Metronome.h"

Metronome::Metronome()
{

	readInSample();

}

void Metronome::prepareToPlay(double samplesPerBlockExpected, double sampleRate)
{
	//set the sample rate 
	mSampleRate = sampleRate;
	mSamplesPerBlock = samplesPerBlockExpected;

	mSamplesPerBeat = mSampleRate * 60.0 / mBPM;

	if (pMetronomeSample != nullptr)
	{
		mClickLength = pMetronomeSample->getTotalLength();
		pMetronomeSample->prepareToPlay(samplesPerBlockExpected, sampleRate);
	}
}

void Metronome::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
	const auto bufferSize = bufferToFill.numSamples;

	mTotalSamples += bufferSize;

	mSamplesRemaining = mTotalSamples % mSamplesPerBeat;

	if ((mSamplesRemaining + bufferSize) >= mSamplesPerBeat)
	{
		const auto timeToStartPlaying = mSamplesPerBeat - mSamplesRemaining;
		pMetronomeSample->setNextReadPosition(0);

		for (auto sample = 0; sample < bufferSize; sample++)
		{
			if (sample == timeToStartPlaying)
			{
				pMetronomeSample->getNextAudioBlock(bufferToFill);
			}
		}
	}

	if (pMetronomeSample->getNextReadPosition() != 0)
	{
		pMetronomeSample->getNextAudioBlock(bufferToFill);
	}
}

void Metronome::readInSample()
{
	mFormatManager.registerBasicFormats();

	auto formatReader = mFormatManager.createReaderFor(new MemoryInputStream(BinaryData::block_wav, BinaryData::block_wavSize, false));

	pMetronomeSample.reset(new AudioFormatReaderSource(formatReader, true));

	if (pMetronomeSample.get() != nullptr)
	{
		clickSampleBuffer.setSize(formatReader->numChannels, (int)formatReader->lengthInSamples);
		formatReader->read(&clickSampleBuffer,
			0,
			(int)formatReader->lengthInSamples,
			0,
			true,
			true);
		position = 0;
		//setAudioChannels(0, formatReader->numChannels);
	}
}

void Metronome::setBPM(float BPM)
{
	mBPM = BPM;
	prepareToPlay(mSamplesPerBlock, mSampleRate);
}
