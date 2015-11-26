#include <AL\al.h>
#include <AL\alc.h>
#include <iostream>
#include <stdio.h>

using namespace std;

//int main() {
	/*
	ALCdevice* device = alcOpenDevice(NULL);
	ALCcontext* context = alcCreateContext(device, NULL);
	alcMakeContextCurrent(context);
	alListener3f(AL_POSITION, 0, 0, 0);
	alListener3f(AL_VELOCITY, 0, 0, 0);
	alListener3f(AL_ORIENTATION, 0, 0, -1);
	ALuint source;
	alGenSources(1, &source);

	const int NUM_BUFFERS = 3;
	ALuint buffer;
	alSourcef(source, AL_PITCH, 1);
	alSourcef(source, AL_GAIN, 1);
	alSource3f(source, AL_POSITION, 0, 0, 0);
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	alSourcei(source, AL_LOOPING, AL_FALSE);
	alGenBuffers(1, &buffer);

	//TODO Load data to buffer

	alSourcei(source, AL_BUFFER, buffer);
	FILE* file = fopen("audio.wav", "fb");
	char xbuffer[5];
	xbuffer[4] = '\0';
	if (fread(xbuffer, sizeof(char), 4, file) != 4 || strcmp(xbuffer, "RIFF") != 0)
	throw "Not a WAV file";

	file_read_int32_le(xbuffer, file);

	if (fread(xbuffer, sizeof(char), 4, file) != 4 || strcmp(xbuffer, "WAVE") != 0)
	throw "Not a WAV file";

	if (fread(xbuffer, sizeof(char), 4, file) != 4 || strcmp(xbuffer, "fmt ") != 0)
	throw "Invalid WAV file";

	file_read_int32_le(xbuffer, file);
	short audioFormat = file_read_int16_le(xbuffer, file);
	short channels = file_read_int16_le(xbuffer, file);
	int sampleRate = file_read_int32_le(xbuffer, file);
	int byteRate = file_read_int32_le(xbuffer, file);
	file_read_int16_le(xbuffer, file);
	short bitsPerSample = file_read_int16_le(xbuffer, file);

	if (audioFormat != 16) {
	short extraParams = file_read_int16_le(xbuffer, file);
	file_ignore_bytes(file, extraParams);
	}

	if (fread(xbuffer, sizeof(char), 4, file) != 4 || strcmp(xbuffer, "data") != 0)
	throw "Invalid WAV file";

	int dataChunkSize = file_read_int32_le(xbuffer, file);
	unsigned char* bufferData = file_allocate_and_read_bytes(file, (size_t)dataChunkSize);

	float duration = float(dataChunkSize) / byteRate;
	alBufferData(buffer, GetFormatFromInfo(channels, bitsPerSample), bufferData, dataChunkSize, sampleRate);
	free(bufferData);
	fclose(file);

	alSourcePlay(source);
	fgetc(stdin);
	alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);
	alcDestroyContext(context);
	alcCloseDevice(device);

	}

	static inline ALenum GetFormatFromInfo(short channels, short bitsPerSample) {
	if (channels == 1)
	return AL_FORMAT_MONO16;
	return AL_FORMAT_STEREO16;
	}

	file_read_int32_le(char xbuffer[], FILE file) {
	;
	}

	file_allocate_and_read_bytes(FILE *file, size_t dataChunkSize){
	;
	}

	file_ignore_bytes(FILE * file, extraParams) {
	;
	}

	file_read_int16_le(char xbuffer[], FILE *file) {
	;
	*/
//}