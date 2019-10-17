/*playButton
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
	mBPMSlider.setRange(30, 220, 1);
	mBPMSlider.setValue(60);
	mBPMSlider.setNumDecimalPlacesToDisplay(0);
	mBPMSlider.addListener (this);
	mBPMSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
	addAndMakeVisible(mBPMSlider);
	
	mBPMLabel.attachToComponent(&mBPMSlider, false);
	addAndMakeVisible(mBPMLabel);


	mPlayButton.setRadioGroupId(1);
	mPlayButton.setToggleState( false, NotificationType::dontSendNotification );
	mPlayButton.onClick = [this]() { play(); };
	addAndMakeVisible(mPlayButton);

	mStopButton.setRadioGroupId(1);
	mStopButton.setToggleState(true, NotificationType::dontSendNotification);
	mStopButton.onClick = [this]() { stop(); };
	addAndMakeVisible(mStopButton);

    // Make sure you set the size of the component after
    // you add any child components.
    setSize (300, 200);

    // Some platforms require permissions to open input channels so request that here

	//NOTE: Inputs are set to 0 to prevent feedback as input is connected to output by 
	//default in JUCE. I didn't delete this because i may want to add features requiring input
    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                     [&] (bool granted) { if (granted)  setAudioChannels (0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (0, 2);
    }
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
	
	mMetronome.prepareToPlay(samplesPerBlockExpected, sampleRate);

}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{

	if (mPlayState == PlayState::Playing)
	{
		mMetronome.getNextAudioBlock(bufferToFill);
	}
	else {
	
	}

}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
	Rectangle<int> bounds = getLocalBounds(); //get the area of the component we're in

	FlexBox flexbox;
	
	flexbox.items.add(FlexItem(100, 100, mBPMSlider));
	flexbox.items.add(FlexItem(100, 100, mPlayButton));
	flexbox.items.add(FlexItem(100, 100, mStopButton));
	flexbox.performLayout(bounds); //layout the items within the local bounds as retreived by getLoclBounds above
}

void MainComponent::play()
{
	mPlayState = PlayState::Playing;
}

void MainComponent::stop()
{
	mPlayState = PlayState::Stopped;
}

void MainComponent::sliderValueChanged(Slider* slider)
{
	mBPM = slider->getValue();
	mMetronome.setBPM(mBPM);
}
