#ifndef MINERVA_RENDER_CAMERA_HPP_
#define MINERVA_RENDER_CAMERA_HPP_

#include <glm/glm.hpp>
//#include "Render/ViewFrustum.h"

struct ViewInfo3d {
  glm::vec3 at; // where player is
  float latitude; // up-down angle (hold shift and right click)
  float longitude; // left-right angle (hold right click)
  float distance; // distance from zoom (scroll wheel)
};

class Camera {
 public:
  Camera();

  float getCurrentLatitude() const;
  // Return a camera direction that's compatible with GameActor directions
  int getDirection() const;

  void AddLongitude(float delta);
  void AddLatitude(float delta);
  void AddDistance(float delta);

  const glm::mat4& GetViewMatrix() const;
  const glm::mat4& GetInvViewMatrix() const;

  void reset();
  void OnCalcViewInfo(const glm::vec3& player_pos);
  void OnRender();

 private:
  void BuildViewMatrix();

 private:
  ViewInfo3d m_cur{};
  glm::vec3 m_from{};
  glm::vec3 m_up{};
  glm::mat4 m_view_matrix{};
  glm::mat4 m_inv_view_matrix{};
  int m_direction{};
};

#endif // MINERVA_RENDER_CAMERA_HPP_
