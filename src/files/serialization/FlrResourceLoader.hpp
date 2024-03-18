#ifndef MINERVA_FILES_SERIALIZATION_FLR_RESOURCE_LOADER_HPP_
#define MINERVA_FILES_SERIALIZATION_FLR_RESOURCE_LOADER_HPP_

#include <stdint.h>
#include <string>
#include <vector>

namespace minerva::files::serialization {

enum class CellType { walkable = 0x01, shootable = 0x02, water = 0x04 };

struct Cell {
  bool walkable{false};
  bool shootable{false};
  bool water{false};
};

/**
 * A resource that loads a Flr file
 * Flr (floor) files describe the cells on the ground
 * They can be any combination of walkable, shootable, water
 */
class FlrResourceLoader {
 public:

  std::vector<Cell> load(const std::string&);

  uint32_t width_{};
  uint32_t height_{};
  std::vector<char> data_{};
};

}  // namespace minerva::files::serialization

#endif  // MINERVA_FILES_SERIALIZATION_FLR_RESOURCE_LOADER_HPP_
