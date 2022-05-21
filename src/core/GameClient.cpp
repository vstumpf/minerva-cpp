#include "Core/GameClient.hpp"

#include <nlohmann/json.hpp>
#include <fstream>

#include "Common/debug.hpp"

GameClient::GameClient()
    : full_screen_(),
      window_width_(),
      window_height_(),
      vsync_(),
      msaa_(),
      font_folder_() {}

GameClient::~GameClient() {
}

bool GameClient::Initialize() {
	LoadConfiguration("minerva.json");
  return true;
}

void GameClient::Run() {

}

bool GameClient::LoadConfiguration(const std::string& file_name) {
  using json = nlohmann::json;

  json json_config;

  std::ifstream json_file(file_name);
  if (json_file.is_open()) {
      json_file >> json_config;
      json_file.close();
      try {
          // Graphics settings
          const auto graphics_config = json_config.at("graphics");
          full_screen_ = graphics_config.value("fullscreen", false);
          window_width_ = graphics_config.value("window_width", 640);
          window_height_ = graphics_config.value("window_height", 480);
          vsync_ = graphics_config.value("vsync", false);
          msaa_ = graphics_config.value("msaa", 0);

          // Fonts settings
          const auto settings_config = json_config.at("fonts");
          font_folder_ = settings_config.value("font_folder", "");
      }
      catch (const std::exception& ex) {
          LOG(error, "Failed to parse {} ({})", file_name, ex.what());
          return false;
      }
  }
  else {
    LOG(warn, "Failed to open {}", file_name);
  }

  // Sanatize values
  if (msaa_ > 32) {
    msaa_ = 32;
  }

  LOG(debug, "Fullscreen: {}", full_screen_);
  LOG(debug, "Resolution: {}x{}", window_width_, window_height_);
  LOG(debug, "Font folder: {}", font_folder_);
  LOG(debug, "Vsync: {}", vsync_ ? "On" : "Off");
  LOG(debug, "Anti-aliasing: MSAA {}x", msaa_);

  return true;
}
