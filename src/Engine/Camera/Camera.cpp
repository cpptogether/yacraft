#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <iostream>
#include "Camera.h"

void Camera::updateCameraVectors() {
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	this->front = glm::normalize(front);

	right = glm::normalize(glm::cross(this->front, worldUp));
	up = glm::normalize(glm::cross(right, this->front));
}

void Camera::globalAdd() {
	//Global::Cameras.push_back(*this);
}

Camera::Camera(glm::vec3 argPosition,
	glm::vec3 argUp,
	float argYaw,
	float argPitch,
	float argMouseSensitivity,
	float argMovementSpeed,
	float argFOV)
	: FOV(argFOV)
	, yaw(argYaw)
	, pitch(argPitch)
	, mouseSensitivity(argMouseSensitivity)
	, movementSpeed(argMovementSpeed)
	, position(argPosition)
	, worldUp(argUp) {
	globalAdd();
	updateCameraVectors();
};

glm::mat4 Camera::getViewMatrix() const {
	return glm::lookAt(position, position + front, up);
}

void Camera::processKeyboard(CameraDir direction, float deltaTime) {
	float velocity = movementSpeed * deltaTime;
	if (direction == CameraDir::FORWARD)
		position += front * velocity;
	if (direction == CameraDir::BACKWARD)
		position -= front * velocity;
	if (direction == CameraDir::LEFT)
		position -= right * velocity;
	if (direction == CameraDir::RIGHT)
		position += right * velocity;
	if (direction == CameraDir::UP)
		position += up * velocity;
	if (direction == CameraDir::DOWN)
		position -= up * velocity;
}

void Camera::processMouseMovement(float X, float Y, bool constrainPitch) {
	float xoffset, yoffset;

	xoffset = X - lastMouseX;
	yoffset = lastMouseY - Y;

	lastMouseX = X;
	lastMouseY = Y;

	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (constrainPitch) {
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}

	updateCameraVectors();
}

void Camera::setFOV(float FOV) { this->FOV = FOV; }

float Camera::getFOV() const { return this->FOV; }

void Camera::setSpeed(float speed) { movementSpeed = speed; }

float Camera::getSpeed() const { return movementSpeed; }

void Camera::setSensitivity(float sense) { mouseSensitivity = sense; }

float Camera::getSensitivity() const { return mouseSensitivity; }

void Camera::setPosition(const glm::vec3 & position) { this->position = position; }

const glm::vec3 & Camera::getPosition() const { return position; }

void Camera::setFront(const glm::vec3 & front) { this->front = front; }

const glm::vec3 & Camera::getFront() const { return front; }

bool Camera::operator==(const Camera & camera) const {
	if (camera.FOV != FOV) {
		return false;
	}
	
	if (camera.front != front) {
		return false;
	}

	if (camera.lastMouseX != lastMouseX) {
		return false;
	}

	if (camera.lastMouseY != lastMouseY) {
		return false;
	}

	if (camera.mouseSensitivity != mouseSensitivity) {
		return false;
	}

	if (camera.movementSpeed != movementSpeed) {
		return false;
	}

	if (camera.pitch != pitch) {
		return false;
	}

	if (camera.yaw != yaw) {
		return false;
	}

	if (camera.position != position) {
		return false;
	}

	return true;
}

Camera::~Camera() {
	//using namespace Global;
	//Cameras.erase(std::find(Cameras.begin(), Cameras.end(), *this));
}