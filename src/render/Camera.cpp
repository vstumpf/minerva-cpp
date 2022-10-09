#include "render/Camera.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

Camera::Camera() {}

float Camera::getCurrentLatitude() const {
	return m_cur.latitude - 180.f;
}

int Camera::getDirection() const {
	return m_direction;
}

void Camera::AddLongitude(float delta) {
	m_cur.longitude += delta;
	m_direction = static_cast<int>(floorf((m_cur.longitude + 22.5f) / 45.f)) % 8;
}

void Camera::AddLatitude(float delta) {
	m_cur.latitude += delta;
}

void Camera::AddDistance(float delta) {
	m_cur.distance += delta;
}

const glm::mat4& Camera::GetInvViewMatrix() const {
	return m_inv_view_matrix;
}

const glm::mat4& Camera::GetViewMatrix() const {
	return m_view_matrix;
}

void Camera::reset() {
	m_cur.distance = 10.f;
	m_cur.longitude = 0.f;
	m_cur.latitude = 225.f;
	m_cur.at = glm::vec3(0.f);
	m_from = m_cur.at + glm::vec3(-m_cur.distance, -m_cur.distance, 0.f);
	m_up = glm::vec3(0.f, -1.f, 0.f);
	m_direction = 0;
}

void Camera::OnCalcViewInfo(const glm::vec3& player_pos) {
	m_cur.at.x = -player_pos.x - 0.5f;
	m_cur.at.y = player_pos.z;
	m_cur.at.z = -player_pos.y - 0.5f;
	BuildViewMatrix();
}

void Camera::BuildViewMatrix() {
	const glm::quat q =
		glm::angleAxis(static_cast<float>(glm::radians(m_cur.latitude)),
						glm::vec3(1.f, 0.f, 0.f))
		* glm::angleAxis(static_cast<float>(glm::radians(m_cur.longitude)),
						glm::vec3(0.f, 1.f, 0.f))
		;
	m_view_matrix = glm::translate(
		glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -m_cur.distance)) *
			glm::mat4_cast(q),
		m_cur.at);
	// m_view_matrix = glm::translate(
	// 	glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -m_cur.distance)),
	// 	m_cur.at);

	m_inv_view_matrix = glm::inverse(m_view_matrix);
}