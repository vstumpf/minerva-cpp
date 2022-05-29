#include "files/BmpResource.hpp"

#ifndef WIN32
#include <string.h>
#define _strcmpi strcasecmp
#endif

#include "common/debug.hpp"

BmpResource::BmpResource() : m_isAlpha(), m_width(), m_height(), m_data() {}

BmpResource::~BmpResource() { Reset(); }

uint32_t BmpResource::GetWidth() const { return m_width; }

uint32_t BmpResource::GetHeight() const { return m_height; }

const char* BmpResource::GetData() const { return m_data.data(); }

void BmpResource::Reset() {
  m_data.clear();
  m_width = 0;
  m_height = 0;
}

uint32_t BmpResource::GetColor(uint32_t x, uint32_t y) const {
  uint32_t result;

  if (x < 0 || x >= m_width || y < 0 || y >= m_height) {
    result = 0x00FF0000;
  } else {
    result = m_data[static_cast<size_t>(x) + static_cast<size_t>(y) * m_width];
  }

  return result;
}

bool BmpResource::Load(const std::string& filename) {

  Reset();

	int width, height, channels;
	char * data = reinterpret_cast<char *>(stbi_load(filename.c_str(), &width, &height, &channels, 4));

	if (!data) {
		LOG(error, "Failed to load image data for {}", filename);
		return false;
	}

	LOG(debug, "STBI: File {} | Width {} | Height {} | Channels {}", filename, width, height, channels);

	m_width = width;
	m_height = height;


	size_t size = width * height * 4 * sizeof(char);

	m_data.reserve(size);

	memmove(m_data.data(), data, size);

	stbi_image_free(data);
  return true;
}
