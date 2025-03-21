#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include "../utils/music_parser.h"
#include "resource_manager.h"
#include <SDL_mixer.h>
#include <string>
#include <unordered_map>

class AudioManager {
public:
    AudioManager(ResourceManager& resourceManager);
    ~AudioManager();
    
    bool loadLevelMusic(const std::string& level);
    void playMusic(const std::string& trackName);
    void stopMusic();

private:
    ResourceManager& m_resourceManager;

    std::unordered_map<std::string, Mix_Music*> m_musicTracks;
    std::string m_currentTrack;
};

#endif // AUDIO_MANAGER_H