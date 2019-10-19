/*
  ==============================================================================

    Visualiser.h
    Created: 18 Oct 2019 2:44:28pm
    Author:  mattc

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class Visualiser : public AudioVisualiserComponent

{
public:
	//construct a visualiser passing 1 as the number of channels
	Visualiser() : AudioVisualiserComponent(1)
	{
	}

	~Visualiser()
	{
	}

	void paintChannel(Graphics& g, Rectangle<float> area,
		const Range<float>* levels, int numLevels, int nextSample) override
	{
		/*
		float centerX = (area.getRight() - getX()) / 2;
		float centerY = area.getY();
		float cLineWidth = 2.0f;
		float height = getBottom()-area.getY();

		g.fillRect(centerX, centerY, cLineWidth, height);
		*/
		Path p;
		getChannelAsPath(p, levels, numLevels, nextSample);

	
		p.applyTransform(AffineTransform::fromTargetPoints(0.0f, -1.0f, getX(), area.getY(),
			0.0f, 1.0f, area.getX(), area.getBottom(),
			(float)numLevels, -1.0f, area.getRight()/2, area.getY()));

		p.scaleToFit(area.getX(), area.getY(), area.getWidth(), area.getHeight(), true);

		//g.fillPath(p);

		g.strokePath(p, PathStrokeType(1.0f));
	}
};