#ifndef MUSIC_PARSER_H
#define MUSIC_PARSER_H

#include <nlohmann/json.hpp>
#include <string>

class MusicParser {
public:
    MusicParser(const std::string& filename);
    bool parse();

    std::string getGroupName() const { return m_groupName; }
    std::unordered_map<std::string, std::string> getMusicTracks() const { return m_musicTracks; }

private:
    std::string m_filename;
    std::string m_groupName;
    std::unordered_map<std::string, std::string> m_musicTracks;

    void parseJson(const nlohmann::json& j);
};

#endif // MUSIC_PARSER_H