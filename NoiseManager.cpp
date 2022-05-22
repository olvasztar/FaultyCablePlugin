/*
  ==============================================================================

    NoiseManager.cpp
    Created: 21 May 2022 12:58:38pm
    Author:  bodit

  ==============================================================================
*/

#include "NoiseManager.h"

NoiseManager::NoiseManager()
{
    updateTimer();
}

void NoiseManager::updateTimer()
{
    startTimer(GetFailureInterval());
}

int NoiseManager::GetFailureInterval()
{
    return juce::Random::getSystemRandom().nextInt(
        juce::Range<int>(SHORTEST_FAILURE_FREE_PERIOD_IN_MILLIS, LONGEST_FAILURE_FREE_PERIOD_IN_MILLIS))
        / (failureDensity * FAILURE_DENSITY_EFFECT_RATIO);
}

int NoiseManager::GetNoisePatchDuration()
{
    return juce::Random::getSystemRandom().nextInt(
        juce::Range<int>(NOISE_PATCH_LENGTH_IN_MILLIS_MIN, NOISE_PATCH_LENGTH_IN_MILLIS_MAX));
}

void NoiseManager::timerCallback()
{
    insertNoiseFlag = true;
    isInMonoState = juce::Random::getSystemRandom().nextBool();
    noisePatchLength = GetNoisePatchDuration() / 1000.0f * currentSampleRate;
    positionInCurrentPatch = 0;

    int interval = GetFailureInterval();
    DBG("Time is up (next: " << interval << ")" << (isInMonoState ? "MONO" : "STEREO"));

    startTimer(interval);
}

float NoiseManager::getNextNoiseSampleData()
{
    positionInCurrentPatch++;
    if (positionInCurrentPatch >= noisePatchLength)
    {
        insertNoiseFlag = false;
    }
    float sampleData = juce::Random::getSystemRandom().nextFloat()
        * NOISE_MAX_AMPLITUDE * 2 - NOISE_MAX_AMPLITUDE;

    return sampleData;
}