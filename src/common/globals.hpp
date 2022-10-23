#ifndef MINERVA_COMMON_GLOBALS_HPP_
#define MINERVA_COMMON_GLOBALS_HPP_

#include "core/ResourceManager.hpp"
#include "render/Renderer.hpp"

namespace minerva::globals {

extern minerva::render::Renderer* gRenderer;
extern minerva::core::ResourceManager* gResourceManager;

}  // namespace minerva::globals

#endif
