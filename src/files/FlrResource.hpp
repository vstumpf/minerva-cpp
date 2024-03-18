#ifndef MINERVA_FILES_FLRRESOURCE_HPP_
#define MINERVA_FILES_FLRRESOURCE_HPP_

#include <stb_image.h>
#include <stdint.h>
#include <string>
#include <vector>

#include "files/Resource.hpp"

namespace minerva::files {

enum class CellType { walkable = 0, shootable, water };

/**
 * A resource that loads a Flr file
 * Flr (floor) files describe the cells on the ground
 * They can be any combination of walkable, shootable, water
 */
class FlrResource : public Resource {
 public:
  FlrResource() = default;
  ~FlrResource() override;

  bool load(const std::string&) override;

  uint32_t getWidth() const;
  uint32_t getLength() const;
  const char* getData() const;

 protected:
  void reset() override;

 private:
  uint32_t width_{};
  uint32_t length_{};
  std::vector<char> data_{};
};

}  // namespace minerva::files

#endif
