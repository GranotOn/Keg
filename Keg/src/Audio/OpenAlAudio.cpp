#include "stadx.h"
#include "Audio/OpenAlAudio.h"
#include <iostream>
#include <Core/Logger/Logger.h>

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
				throw("failed to get sound device");

			p_ALCContext = alcCreateContext(p_ALCDevice, nullptr);  // create context
			if (!p_ALCContext)
				throw("Failed to set sound context");

			if (!alcMakeContextCurrent(p_ALCContext))   // make context current
				throw("failed to make context current");

			const ALCchar* name = nullptr;
			if (alcIsExtensionPresent(p_ALCDevice, "ALC_ENUMERATE_ALL_EXT"))
				name = alcGetString(p_ALCDevice, ALC_ALL_DEVICES_SPECIFIER);
			if (!name || alcGetError(p_ALCDevice) != 0)
				name = alcGetString(p_ALCDevice, ALC_DEVICE_SPECIFIER);
			printf("DEVICE VOICE Opened \"%s\"\n", name);
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




	Effect* OpenAlAudio::addEffect(const char* filename) {

		ALuint p_sound_Source;
		ALuint p_sound_Buffer = 0;

		alGenSources(1, &p_sound_Source);
		KEG_ENGINE_INFO("p_source 1", p_sound_Source);
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
			fprintf(stderr, "Could not open audio in %s: %s\n", filename, sf_strerror(sndfile));
			return 0;
		}
		if (sfinfo.frames < 1 || sfinfo.frames >(sf_count_t)(INT_MAX / sizeof(short)) / sfinfo.channels)
		{
			fprintf(stderr, "Bad sample count in %s (%" PRId64 ")\n", filename, sfinfo.frames);
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
			fprintf(stderr, "Unsupported channel count: %d\n", sfinfo.channels);
			sf_close(sndfile);
			return 0;
		}

		/* Decode the whole audio file to a buffer. */
		membuf = static_cast<short*>(malloc((size_t)(sfinfo.frames * sfinfo.channels) * sizeof(short)));

		num_frames = sf_readf_short(sndfile, membuf, sfinfo.frames);
		if (num_frames < 1)
		{
			free(membuf);
			sf_close(sndfile);
			fprintf(stderr, "Failed to read samples in %s (%" PRId64 ")\n", filename, num_frames);
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
			fprintf(stderr, "OpenAL Error: %s\n", alGetString(err));
			if (buffer && alIsBuffer(buffer))
				alDeleteBuffers(1, &buffer);
			return 0;
		}

		//p_SoundEffectBuffers.push_back(buffer);  // add to the list of known buffers
		ee->SetBuffer(buffer);
		return ee;
	}



	void OpenAlAudio::Init() {
		try
		{
			OpenAlDevice();
			//p_SoundEffectBuffers.clear();
		}
		catch (std::exception & e)
		{
			KEG_ENGINE_ERROR("OpenAL error: Init {0}", e.what());
		}

	}


	OpenAlAudio::~OpenAlAudio() {
		//alDeleteBuffers(p_SoundEffectBuffers.size(), p_SoundEffectBuffers.data());
		//p_SoundEffectBuffers.clear();
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
