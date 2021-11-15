#pragma once
#include <alc.h>
#include <al.h>
#include <stdio.h>
#include <exception>
#include <sndfile.h>
#include <inttypes.h>
#include <alext.h>
#include "Audio/Effect.h"

namespace Keg {
    class Audio
	{
	public:
		virtual void Init()=0;
		virtual void PlayEffect(ALuint buffer, ALuint soundSource, ALuint soundBuffer) = 0;
		virtual Effect* addEffect(const char* filename) = 0;

		virtual void PauseEffect(ALuint& buffer)=0;
		virtual void StopEffect(ALuint& buffer)=0;
		//virtual void StopSong()=0;
		//virtual void OnFinish()=0;
		virtual bool IsEffectPlaying(ALuint &buffer)=0;
		//virtual void PlayEffect()=0;
	};
}


