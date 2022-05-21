#include "Common/debug.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>

#ifdef MINERVA_DEBUG
static auto g_logger = spdlog::stdout_color_mt(MINERVA_LOGGER_NAME);
#endif  // MINERVA_DEBUG
