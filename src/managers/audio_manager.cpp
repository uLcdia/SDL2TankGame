#include "audio_manager.h"
#include <iostream>

AudioManager::AudioManager(ResourceManager& resourceManager)
    : m_resourceManager(resourceManager) {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
}

AudioManager::~AudioManager() {
    stopMusic();
    Mix_Quit();
}

bool AudioManager::loadLevelMusic(const std::string& level) {
    std::string musicFilePath = "assets/levels/" + level + "/music.json";
    MusicParser musicParser(musicFilePath);
    if (!musicParser.parse()) {
        std::cerr << "Failed to parse music file: " << musicFilePath << std::endl;
        return false;
    }

    std::cout << "Music parsed successfully." << std::endl;

    const auto& tracks = musicParser.getMusicTracks();
    for (const auto& [trackName, fileName] : tracks) {
        std::string path = musicParser.getGroupName() + "/" + fileName;
        m_resourceManager.loadMusic(trackName, path);
        m_musicTracks[trackName] = m_resourceManager.getMusic(trackName);
        if (!m_musicTracks[trackName]) {
            std::cerr << "Failed to load music track: " << trackName << std::endl;
            return false;
        }
    }
    return true;
}

void AudioManager::playMusic(const std::string& trackName) {
    auto it = m_musicTracks.find(trackName);
    if (it != m_musicTracks.end()) {
        if (m_currentTrack != trackName) {
            stopMusic();
            if (Mix_PlayMusic(it->second, -1) == -1) {
                std::cerr << "Failed to play music track: " << trackName << "! SDL_mixer Error: " << Mix_GetError() << std::endl;
            } else {
                std::cout << "Playing music track: " << trackName << std::endl;
                m_currentTrack = trackName;
            }
        }
    } else {
        std::cerr << "Music track not found: " << trackName << std::endl;
    }
}

void AudioManager::stopMusic() {
    if (!m_currentTrack.empty()) {
        Mix_HaltMusic();
        m_currentTrack.clear();
    }
}