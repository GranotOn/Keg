#include "stadx.h"
#include "Audio/OpenAlAudio.h"
#include <Core/Logger/Logger.h>


#include <alc.h>
#include <sndfile.h>
#include <alext.h>

namespace Keg {

	OpenAlAudio* OpenAlAudio::s_Audio = nullptr;
	static ALCdevice* p_ALCDevice = nullptr;

	OpenAlAudio* OpenAlAudio::GetInstance()
	{
		if (s_Audio == nullptr)
		{
			s_Audio = new OpenAlAudio();
		}

		return s_Audio;
	}


	void OpenAlAudio::OpenAlDevice() {
			p_ALCDevice = alcOpenDevice(nullptr); // nullptr = get default device
			if (!p_ALCDevice)
				KEG_ENGINE_ERROR("OpenAlAudio::OpenAlDevice : failed to get sound device")
			p_ALCContext = alcCreateContext(p_ALCDevice, nullptr);  // create context

			if (!p_ALCContext)
				KEG_ENGINE_ERROR("OpenAlAudio::OpenAlDevice : Failed to set sound context")

			if (!alcMakeContextCurrent(p_ALCContext))   // make context current
				KEG_ENGINE_ERROR("OpenAlAudio::OpenAlDevice : failed to make context current")

			const ALCchar* name = nullptr;
			if (alcIsExtensionPresent(p_ALCDevice, "ALC_ENUMERATE_ALL_EXT"))
				name = alcGetString(p_ALCDevice, ALC_ALL_DEVICES_SPECIFIER);
			if (!name || alcGetError(p_ALCDevice) != 0)
				name = alcGetString(p_ALCDevice, ALC_DEVICE_SPECIFIER);
			
			KEG_ENGINE_INFO("OpenAlAudio::OpenAlDevice: DEVICE VOICE Opened {0}", name)
	};

	void OpenAlAudio::PlayEffect(ALuint buffer, ALuint soundSource, ALuint soundBuffer) {
		if (buffer != soundBuffer)
		{
			soundBuffer = buffer;
			alSourcei(soundSource, AL_BUFFER, (ALint)soundBuffer);
		}
		alSourcePlay(soundSource);
	}


	bool OpenAlAudio::IsEffectPlaying(ALuint &buffer) {
		ALint state;

		alGetSourcei(buffer, AL_SOURCE_STATE, &state);
		if (state == AL_PLAYING && alGetError() == AL_NO_ERROR) {
			return true;
		}

		return false;
	}




	Effect* OpenAlAudio::AddEffect(const char* filename) {

		ALuint p_sound_Source;
		ALuint p_sound_Buffer = 0;

		alGenSources(1, &p_sound_Source);
		alSourcei(p_sound_Source, AL_BUFFER, p_sound_Buffer);

		Effect* ee = new Effect();
		ee->SetSoundBuffer(p_sound_Buffer);
		ee->SetSoundSource(p_sound_Source);


		ALenum err, format;
		ALuint buffer;
		SNDFILE* sndfile;
		SF_INFO sfinfo;
		short* membuf;
		sf_count_t num_frames;
		ALsizei num_bytes;

		/* Open the audio file and check that it's usable. */
		sndfile = sf_open(filename, SFM_READ, &sfinfo);
		if (!sndfile)
		{
			KEG_ENGINE_ERROR("OpenALAudio::AddEffect : Could not open audio in {0} : {1}", filename, sf_strerror(sndfile));
			return 0;
		}
		if (sfinfo.frames < 1 || sfinfo.frames >(sf_count_t)(INT_MAX / sizeof(short)) / sfinfo.channels)
		{
			KEG_ENGINE_ERROR("OpenALAudio::AddEffect : Bad sample count in {0} : {1}", filename, sfinfo.frames);
			sf_close(sndfile);
			return 0;
		}

		/* Get the sound format, and figure out the OpenAL format */
		format = AL_NONE;
		if (sfinfo.channels == 1)
			format = AL_FORMAT_MONO16;
		else if (sfinfo.channels == 2)
			format = AL_FORMAT_STEREO16;
		else if (sfinfo.channels == 3)
		{
			if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
				format = AL_FORMAT_BFORMAT2D_16;
		}
		else if (sfinfo.channels == 4)
		{
			if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
				format = AL_FORMAT_BFORMAT3D_16;
		}

		if (!format)
		{
			KEG_ENGINE_ERROR("OpenALAudio::AddEffect : Unsupported channel count {0}", sfinfo.channels);
			sf_close(sndfile);
			return 0;
		}

		/* Decode the whole audio file to a buffer. */
		membuf = static_cast<short*>(malloc((size_t)(sfinfo.frames * sfinfo.channels) * sizeof(short)));

		num_frames = sf_readf_short(sndfile, membuf, sfinfo.frames);
		if (num_frames < 1)
		{
			KEG_ENGINE_ERROR("OpenALAudio::AddEffect : Failed to read samples in {0} ({1})", filename, num_frames);
			free(membuf);
			sf_close(sndfile);
			return 0;
		}
		num_bytes = (ALsizei)(num_frames * sfinfo.channels) * (ALsizei)sizeof(short);

		/* Buffer the audio data into a new buffer object, then free the data and
		 * close the file.
		 */
		buffer = 0;
		alGenBuffers(1, &buffer);
		alBufferData(buffer, format, membuf, num_bytes, sfinfo.samplerate);

		free(membuf);
		sf_close(sndfile);

		/* Check if an error occured, and clean up if so. */
		err = alGetError();
		if (err != AL_NO_ERROR)
		{
			KEG_ENGINE_ERROR("OpenALAudio::AddEffect : Failed to read samples in {0} ({1})", filename, num_frames);
			if (buffer && alIsBuffer(buffer))
				alDeleteBuffers(1, &buffer);
			return 0;
		}

		ee->SetBuffer(buffer);
		return ee;
	}



	void OpenAlAudio::Init() {
		try
		{
			OpenAlDevice();
		}
		catch (std::exception & e)
		{
			KEG_ENGINE_ERROR("OpenALAudio::AddEffect : OpenAL error: Init {0}", e.what());
		}

	}


	OpenAlAudio::~OpenAlAudio() {
		alcMakeContextCurrent(nullptr);
		alcDestroyContext(p_ALCContext);
		alcCloseDevice(p_ALCDevice);
	}


	void OpenAlAudio::PauseEffect(ALuint& buffer) {
		alSourcePause(buffer);
	}
	void OpenAlAudio::StopEffect(ALuint& buffer) {
		alSourceStop(buffer);
	}
}
