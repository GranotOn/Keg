#pragma once
#include <al.h>
#include "Audio/Effect.h"

namespace Keg {
    class Audio
	{
	public:
		virtual void Init()=0;
		virtual void PlayEffect(ALuint buffer, ALuint soundSource, ALuint soundBuffer) = 0;
		virtual Effect* AddEffect(const char* filename) = 0;

		virtual void PauseEffect(ALuint& buffer)=0;
		virtual void StopEffect(ALuint& buffer)=0;
		virtual bool IsEffectPlaying(ALuint &buffer)=0;
	};
}


