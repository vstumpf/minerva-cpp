#ifndef MINERVA_COMMON_DEBUG_H_
#define MINERVA_COMMON_DEBUG_H_

#include <spdlog/spdlog.h>

#ifdef MINERVA_DEBUG
#define MINERVA_LOGGER_NAME "Minerva"
#define LOG(LEVEL, FMT, ...) \
  spdlog::get(MINERVA_LOGGER_NAME)->LEVEL(FMT, ##__VA_ARGS__)
#else
#define LOG(CHANNEL, FMT, ...)
#endif  // MINERVA_DEBUG

#endif  // MINERVA_COMMON_DEBUG_H_
