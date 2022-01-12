#include "stadx.h"
#include "Effect.h"
#include "Audio/AudioBuilder.h"

namespace Keg {
		Effect::Effect() {
			m_buffer = 0;
			m_isPlaying = false;
		}
		ALuint Effect::GetBuffer() { return m_buffer; }
		void Effect::SetBuffer(ALuint buffer) { m_buffer = buffer; }

		void Effect::SetSoundSource(ALuint soundSource)
		{
			this->p_sound_Source = soundSource;
		}

		void Effect::SetSoundBuffer(ALuint soundBuffer)
		{
			this->p_sound_Buffer = soundBuffer;
		}

		//virtual void Init();
		void Effect::Play() { AudioBuilder::GetAudio()->PlayEffect(m_buffer, p_sound_Source, p_sound_Buffer); }
		void Effect::pause() { AudioBuilder::GetAudio()->PauseEffect(m_buffer); }
		void Effect::stop() { AudioBuilder::GetAudio()->StopEffect(m_buffer); }
		bool Effect::isPlaying()
		{
			return AudioBuilder::GetAudio()->IsEffectPlaying(m_buffer);
		}
}

