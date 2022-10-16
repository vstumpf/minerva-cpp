#ifndef MINERVA_RENDER_CAMERA_HPP_
#define MINERVA_RENDER_CAMERA_HPP_

#include <glm/glm.hpp>
//#include "Render/ViewFrustum.h"

struct ViewInfo3d {
  glm::vec3 at;     // where player is
  float latitude;   // up-down angle (hold shift and right click)
  float longitude;  // left-right angle (hold right click)
  float distance;   // distance from zoom (scroll wheel)
};

class Camera {
 public:
  Camera();

  float getCurrentLatitude() const;
  // Return a camera direction that's compatible with GameActor directions
  int getDirection() const;

  void addLongitude(float delta);
  void addLatitude(float delta);
  void addDistance(float delta);

  const glm::mat4& getViewMatrix() const;
  const glm::mat4& getInvViewMatrix() const;

  void reset();
  void onCalcViewInfo(const glm::vec3& playerPos);
  void OnRender();

 private:
  void buildViewMatrix();

 private:
  ViewInfo3d cur_{};
  glm::vec3 from_{};
  glm::vec3 up_{};
  glm::mat4 viewMatrix_{};
  glm::mat4 invViewMatrix_{};
  int direction_{};
};

#endif  // MINERVA_RENDER_CAMERA_HPP_
