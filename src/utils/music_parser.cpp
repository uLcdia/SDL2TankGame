#include "music_parser.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

MusicParser::MusicParser(const std::string& filename)
    : m_filename(filename) {}

bool MusicParser::parse() {
    std::ifstream file(m_filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open music config file: " << m_filename << std::endl;
        return false;
    }

    try {
        json j;
        file >> j;
        parseJson(j);
        return true;
    } catch (json::parse_error& e) {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
        return false;
    }
}

void MusicParser::parseJson(const json& j) {
    m_groupName = j["groupName"];
    for (const auto& [key, value] : j["musicTracks"].items()) {
        m_musicTracks[key] = value.get<std::string>();
        std::cout << "Parsed music: " << key << " -> " << m_musicTracks[key] << std::endl;
    }
}