#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H

#include <vector>
#include <glm/glm.hpp>

class Camera;

namespace Global {
	static std::vector<Camera> Cameras;
};

enum class CameraDir : int {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Camera {
private:
	static constexpr float YAW = -90.0f;

	static constexpr float PITCH = 0.0f;

	static constexpr float SPEED = 2.5f;

	static constexpr float SENSITIVITY = 0.1f;

	static constexpr float MAX_FOV = 360.0f;

	float movementSpeed;

	float mouseSensitivity;

	float FOV;

	glm::vec3 position;

	glm::vec3 front;

	glm::vec3 up;

	glm::vec3 right;

	glm::vec3 worldUp;

	float yaw;

	float pitch;

	float lastMouseX = 0;

	float lastMouseY = 0;

	/**
	* @brief Updates camera rotation.
	**/
	void updateCameraVectors();

	/**
	* @brief Helper method which adds camera to Global::Cameras.
	**/
	void globalAdd();


public:
	/**
	* @brief Creates camera.
	* @param argposition Position.
	* @param argUp Worlds up direction.
	* @param argYaw Yaw in degrees.
	* @param argPitch Pitch in degrees.
	* @param argMouseSensitivity Mouse sensitivity
	* @param argMovementSpeed Speed
	* @param argFOV Field Of View
	**/
	Camera(glm::vec3 argPosition = glm::vec3(0),
		glm::vec3 argUp = glm::vec3(0, 1, 0),
		float argYaw = YAW,
		float argPitch = PITCH,
		float argMouseSensitivity = SENSITIVITY,
		float argMovementSpeed = SPEED,
		float argFOV = MAX_FOV);

	/**
	* @brief Returns View matrix.
	* @returns glm::mat4 View matrix.
	**/
	glm::mat4 getViewMatrix() const;

	/**
	* @brief Processes input
	* @param direction Where to go.
	* @param deltaTime Delta time.
	**/
	void processKeyboard(CameraDir direction, float deltaTime);

	/**
	* @brief Processes mouse input
	* @param X Cursor X.
	* @param Y Cursor Y.
	* @param constrainPitch Limit rotation to up/down or not.
	**/
	void processMouseMovement(float X, float Y, bool constrainPitch = true);

	/**
	* @brief Sets FOV.
	* @param FOV FOV.
	**/
	void setFOV(float FOV);

	/**
	* @brief Returns FOV.
	* @returns FOV.
	**/
	float getFOV() const;

	/**
	* @brief Sets speed.
	* @param speed Speed.
	**/
	void setSpeed(float speed);

	/**
	* @brief Returns speed.
	* @returns Speed.
	**/
	float getSpeed() const;

	/**
	* @brief Sets mouse sensitivity.
	* @param sense Mouse sensitivity.
	**/
	void setSensitivity(float sense);

	/**
	* @brief Returns sensitivity.
	* @returns Sensitivity.
	**/
	float getSensitivity() const;

	/**
	* @brief Sets position.
	* @param position Position.
	**/
	void setPosition(const glm::vec3 & position);

	/**
	* @brief Returns position.
	* @returns Position.
	**/
	const glm::vec3 & getPosition() const;

	/**
	* @brief Sets view direction.
	* @param front View direction.
	**/
	void setFront(const glm::vec3 & front);

	/**
	* @brief Returns view direction.
	* @returns View direction.
	**/
	const glm::vec3 & getFront() const;

	bool operator==(const Camera& camera) const;

	~Camera();
};

#endif
