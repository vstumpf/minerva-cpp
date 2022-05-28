#include "Core/GameClient.hpp"

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <glad/glad.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "common/debug.hpp"

#include "modes/LoginMode.hpp"
#include "core/ModeManager.hpp"

#include "render/Window.hpp"

GameClient::GameClient() {}

GameClient::~GameClient() {
    SDL_Quit();
}

bool GameClient::Initialize() {
	LoadConfiguration("minerva.json");
    window_ = std::make_shared<Window>();

    const uint32_t flags = (fullScreen_ ? static_cast<int>(DeviceFlag::FULLSCREEN) : 0) |
        (vsync_ ? static_cast<int>(DeviceFlag::VSYNC) : 0);


    window_->init(window_width_, window_height_, msaa_, flags);

  return true;
}

void GameClient::Run() {

    auto renderer = window_->createRenderer();

    modeManager_ = std::make_shared<ModeManager>(ModeType::LOGIN, "", renderer);

    modeManager_->run();
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
          const auto& graphics_config = json_config.at("graphics");
          fullScreen_ = graphics_config.value("fullscreen", false);
          window_width_ = graphics_config.value("window_width", 640);
          window_height_ = graphics_config.value("window_height", 480);
          vsync_ = graphics_config.value("vsync", false);
          msaa_ = graphics_config.value("msaa", 0);
      }
      catch (const std::exception& ex) {
          LOG(error, "Failed to parse {} ({})", file_name, ex.what());
      }
  }
  else {
    LOG(warn, "Failed to open {}", file_name);
  }

  // Sanatize values
  if (msaa_ > 32) {
    msaa_ = 32;
  }

  LOG(debug, "Fullscreen: {}", fullScreen_);
  LOG(debug, "Resolution: {}x{}", window_width_, window_height_);
  LOG(debug, "Font folder: {}", font_folder_);
  LOG(debug, "Vsync: {}", vsync_ ? "On" : "Off");
  LOG(debug, "Anti-aliasing: MSAA {}x", msaa_);

  return true;
}
