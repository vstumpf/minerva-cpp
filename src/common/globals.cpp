#include "common/globals.hpp"

namespace minerva::globals {

minerva::render::Renderer* gRenderer = nullptr;
minerva::core::ResourceManager* gResourceManager =
    new minerva::core::ResourceManager();

}  // namespace minerva::globals