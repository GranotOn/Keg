#pragma once

#include "Audio/Audio.h"

namespace Keg {
	class OpenAlAudio : public Audio
	{
	public:
		//OpenAlAudio() { Init(); }
		~OpenAlAudio();
		virtual void Init();
		virtual void PlayEffect(ALuint buffer, ALuint soundSource, ALuint soundBuffer);
		virtual Effect* addEffect(const char* filename);

		static OpenAlAudio* GetInstance();

		virtual void PauseEffect(ALuint& buffer);
		virtual void StopEffect(ALuint& buffer);
		//virtual void StopSong() = 0;
		//virtual void OnFinish() = 0;
		virtual bool IsEffectPlaying(ALuint &buffer);
		void OpenAlDevice();
	private:
//		int m_MaxThreads;
//		bool m_EngineRunning;
		static OpenAlAudio* s_Audio;
		ALCcontext* p_ALCContext;
		uint32_t m_SourceHandle = 0;
		//std::vector<ALuint> p_SoundEffectBuffers;
	};
}

