#pragma once
#include "Audio/Audio.h"
#include "Audio/OpenAlAudio.h"

namespace Keg
{

	class AudioBuilder
	{
	public:
		//static AudioBuilder* GetInstance();

		static Audio* GetAudio()
		{
			return OpenAlAudio::GetInstance();
		}

	private:
		//static AudioBuilder* s_Builder;
	};

}