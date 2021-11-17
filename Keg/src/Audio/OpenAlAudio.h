#pragma once

#include "Audio/Audio.h"

namespace Keg {
	class OpenAlAudio : public Audio
	{
	public:
		~OpenAlAudio();
		virtual void Init();
		virtual void PlayEffect(ALuint buffer, ALuint soundSource, ALuint soundBuffer);
		virtual Effect* AddEffect(const char* filename);

		static OpenAlAudio* GetInstance();

		virtual void PauseEffect(ALuint& buffer);
		virtual void StopEffect(ALuint& buffer);
		virtual bool IsEffectPlaying(ALuint &buffer);
		void OpenAlDevice();
	
	private:
		OpenAlAudio() = default;

	private:
		static OpenAlAudio* s_Audio;
		ALCcontext* p_ALCContext;
		uint32_t m_SourceHandle = 0;
	};
}

