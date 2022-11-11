#include "render/Camera.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

float Camera::getCurrentLatitude() const {
  return cur_.latitude - 180.f;
}

int Camera::getDirection() const {
  return direction_;
}

void Camera::addLongitude(float delta) {
  cur_.longitude += delta;
  direction_ = static_cast<int>(floorf((cur_.longitude + 22.5f) / 45.f)) % 8;
}

void Camera::addLatitude(float delta) {
  cur_.latitude += delta;
}

void Camera::addDistance(float delta) {
  cur_.distance += delta;
}

const glm::mat4& Camera::getInvViewMatrix() const {
  return invViewMatrix_;
}

const glm::mat4& Camera::getViewMatrix() const {
  return viewMatrix_;
}

void Camera::reset() {
  cur_.distance = 300.f;
  cur_.longitude = 0.f;
  cur_.latitude = 225.f;
  cur_.at = glm::vec3(0.f);
  from_ = cur_.at + glm::vec3(-cur_.distance, -cur_.distance, 0.f);
  up_ = glm::vec3(0.f, -1.f, 0.f);
  direction_ = 0;
}

void Camera::onCalcViewInfo(const glm::vec3& playerPos) {
  cur_.at.x = -playerPos.x - 0.5f;
  cur_.at.y = playerPos.z;
  cur_.at.z = -playerPos.y - 0.5f;
  buildViewMatrix();
}

void Camera::buildViewMatrix() {
  const glm::quat q =
      glm::angleAxis(static_cast<float>(glm::radians(cur_.latitude)),
                     glm::vec3(1.f, 0.f, 0.f)) *
      glm::angleAxis(static_cast<float>(glm::radians(cur_.longitude)),
                     glm::vec3(0.f, 1.f, 0.f));
  viewMatrix_ = glm::translate(
      glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -cur_.distance)) *
          glm::mat4_cast(q),
      cur_.at);
  // viewMatrix_ = glm::translate(
  // 	glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -cur_.distance)),
  // 	cur_.at);

  invViewMatrix_ = glm::inverse(viewMatrix_);
}
