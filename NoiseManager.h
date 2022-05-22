/*
  ==============================================================================

    NoiseManager.h
    Created: 21 May 2022 12:58:38pm
    Author:  bodit

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class NoiseManager : private juce::Timer
{
public:
    NoiseManager();

    void updateTimer();
    float failureDensity;

    bool isInMonoState;
    int noisePatchLength;
    bool insertNoiseFlag;
    int positionInCurrentPatch;

    double currentSampleRate = 0.0;

    float getNextNoiseSampleData();

private:
    // constant values
    const int NOISE_PATCH_LENGTH_IN_MILLIS_MIN = 20;
    const int NOISE_PATCH_LENGTH_IN_MILLIS_MAX = 200;
    const int LONGEST_FAILURE_FREE_PERIOD_IN_MILLIS = 5000;
    const int SHORTEST_FAILURE_FREE_PERIOD_IN_MILLIS = 200;

    const float NOISE_MAX_AMPLITUDE = 0.1;
    const float FAILURE_DENSITY_EFFECT_RATIO = 0.1;

    void timerCallback() override;
    int GetFailureInterval();
    int GetNoisePatchDuration();
};