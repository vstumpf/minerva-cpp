#include "Core/GameClient.hpp"

#include <glad/glad.h>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "common/debug.hpp"
#include "common/globals.hpp"
#include "core/ModeManager.hpp"
#include "modes/LoginMode.hpp"

#include "render/Window.hpp"

namespace minerva {

GameClient::GameClient() {}

GameClient::~GameClient() {
  SDL_Quit();
}

bool GameClient::initialize() {
  loadConfiguration("minerva.json");
  window_ = std::make_shared<render::Window>();

  const uint32_t flags =
      (fullScreen_ ? static_cast<int>(render::DeviceFlag::FULLSCREEN) : 0) |
      (vsync_ ? static_cast<int>(render::DeviceFlag::VSYNC) : 0);

  window_->init(windowWidth_, windowHeight_, msaa_, flags);

  return true;
}

void GameClient::run() {
  globals::gRenderer = window_->createRenderer();

  modeManager_ = std::make_shared<ModeManager>(ModeType::LOGIN, "");

  modeManager_->run();
}

bool GameClient::loadConfiguration(const std::string& fileName) {
  using json = nlohmann::json;

  json jsonConfig;

  std::ifstream json_file(fileName);
  if (json_file.is_open()) {
    json_file >> jsonConfig;
    json_file.close();
    try {
      // Graphics settings
      const auto& graphicsConfig = jsonConfig.at("graphics");
      fullScreen_ = graphicsConfig.value("fullscreen", false);
      windowWidth_ = graphicsConfig.value("window_width", 640);
      windowHeight_ = graphicsConfig.value("window_height", 480);
      vsync_ = graphicsConfig.value("vsync", false);
      msaa_ = graphicsConfig.value("msaa", 0);
    } catch (const std::exception& ex) {
      LOG(error, "Failed to parse {} ({})", fileName, ex.what());
    }
  } else {
    LOG(warn, "Failed to open {}", fileName);
  }

  // Sanitize values
  if (msaa_ > 32) {
    msaa_ = 32;
  }

  LOG(debug, "Fullscreen: {}", fullScreen_);
  LOG(debug, "Resolution: {}x{}", windowWidth_, windowHeight_);
  LOG(debug, "Font folder: {}", fontFolder_);
  LOG(debug, "Vsync: {}", vsync_ ? "On" : "Off");
  LOG(debug, "Anti-aliasing: MSAA {}x", msaa_);

  return true;
}

}  // namespace minerva
