#ifndef MINERVA_COMMON_DEBUG_HPP_
#define MINERVA_COMMON_DEBUG_HPP_

#include <spdlog/spdlog.h>

// #define MINERVA_GL_DEBUG

#ifdef MINERVA_DEBUG
#define MINERVA_LOGGER_NAME "Minerva"
#define LOG(LEVEL, FMT, ...) \
  spdlog::get(MINERVA_LOGGER_NAME)->LEVEL(FMT, ##__VA_ARGS__)
#else
#define LOG(CHANNEL, FMT, ...)
#endif  // MINERVA_DEBUG

#ifdef MINERVA_GL_DEBUG
#define MINERVA_GL_LOGGER_NAME "GL"
#define GLLOG(LEVEL, FMT, ...) \
  spdlog::get(MINERVA_GL_LOGGER_NAME)->LEVEL(FMT, ##__VA_ARGS__)
#else
#define GLLOG(CHANNEL, FMT, ...)
#endif  // MINERVA_GL_DEBUG

#endif  // MINERVA_COMMON_DEBUG_HPP_
