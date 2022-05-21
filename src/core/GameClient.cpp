#include "Core/GameClient.hpp"

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <glad/glad.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "Common/debug.hpp"

GameClient::GameClient() {}

GameClient::~GameClient() {
}

bool GameClient::Initialize() {
	LoadConfiguration("minerva.json");
  return true;
}

void GameClient::Run() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL2 video subsystem couldn't be initialized. Error: "
            << SDL_GetError()
            << std::endl;
        exit(1);
    }

    SDL_Window* window = SDL_CreateWindow(
        "Glad Sample",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        window_width_,
        window_height_,
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr) {
        std::cerr << "SDL2 Renderer couldn't be created. Error: "
            << SDL_GetError()
            << std::endl;
        exit(1);
    }

    // Create a OpenGL context on SDL2
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Delay(3000);

    SDL_DestroyWindow(window);
    SDL_Quit();
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
