#include "AudioEngine.h"

void SoundEffect::play(int loops) {
	if (Mix_PlayChannel(-1, m_chunk, loops) == -1) {
		if (Mix_PlayChannel(0, m_chunk, loops) == -1) {
			fatalError("Mix_PlayChannel error: " + std::string(Mix_GetError()));
		}
	}
}

void Music::play(int loops) {
	Mix_PlayMusic(m_music, loops);
}

void Music::pause() {
	Mix_PauseMusic();
}

void Music::stop() {
	Mix_HaltMusic();
}

void Music::resume() {
	Mix_ResumeMusic();
}

AudioEngine::AudioEngine() {}


AudioEngine::~AudioEngine() {
	destroy();
}

void AudioEngine::init() {
	// Parameter can be a bitwise combination of MIX_INIT_FAC, MIX_INIT_MOD, MIX_INIT_MP3, MIX_INIT_OGG
	if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == -1) {
		fatalError("Mix_Init error: " + std::string(Mix_GetError()));
	}

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		fatalError("Mix_OpenAudio error: " + std::string(Mix_GetError()));
	}

	m_isInitialized = true;
}

void AudioEngine::destroy() {
	if (m_isInitialized) {
		m_isInitialized = false;
		Mix_Quit();
	}
}

SoundEffect AudioEngine::loadSoundEffect(const std::string& filePath) {
	SoundEffect effect;

	auto it = m_effectMap.find(filePath);
	if (it == m_effectMap.end()) {
		Mix_Chunk* chunk = Mix_LoadWAV(filePath.c_str());
		if (chunk == nullptr) {
			fatalError("Mix_LoadWAV error: " + std::string(Mix_GetError()));
		}

		m_effectMap[filePath] = chunk;
		effect.m_chunk = chunk;
	}
	else {
		effect.m_chunk = it->second;
	}

	return effect;
}

Music AudioEngine::loadMusic(const std::string& filePath) {
	Music music;

	auto it = m_musicMap.find(filePath);
	if (it == m_musicMap.end()) {
		Mix_Music* mixMusic = Mix_LoadMUS(filePath.c_str());
		if (mixMusic == nullptr) {
			fatalError("Mix_LoadWAV error: " + std::string(Mix_GetError()));
		}

		m_musicMap[filePath] = mixMusic;
		music.m_music = mixMusic;
	}
	else {
		music.m_music = it->second;
	}

	return music;
}