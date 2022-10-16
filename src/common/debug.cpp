#include "Common/debug.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>

#ifdef MINERVA_DEBUG
static auto g_logger = spdlog::stdout_color_mt(MINERVA_LOGGER_NAME);
#endif  // MINERVA_DEBUG

#ifdef MINERVA_GL_DEBUG
static auto g_gllogger = spdlog::stdout_color_mt(MINERVA_GL_LOGGER_NAME);
#endif  // MINERVA_GL_DEBUG