#pragma once
#include <AL\al.h>
#include <stdio.h>
#include <exception>
#include <sndfile.h>
#include <inttypes.h>
#include <AL\alext.h>


namespace Keg {
	class Effect
	{
	public:
		Effect();
		ALuint GetBuffer();
		void SetBuffer(ALuint buffer);
		void SetSoundSource(ALuint soundSource);
		void SetSoundBuffer(ALuint soundBuffer);
		virtual void Play();
		virtual void pause();
		virtual void stop();
		virtual bool isPlaying();

	private:
		ALuint m_buffer;
		bool m_isPlaying;
		ALuint p_sound_Source = 0;
		ALuint p_sound_Buffer = 0;
	};
}