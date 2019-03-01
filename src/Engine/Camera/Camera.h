#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H

#include <vector>
#include <glm/glm.hpp>
#include "Engine/Window/Window.h"
#include "Engine/Frustum/Frustum.h"

enum class CameraDir : int {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

namespace Engine {

	class Camera;

	namespace Global {
		static std::vector<Camera> Cameras;
	};

	class Camera {
	private:
		static constexpr float YAW = -90.0f;

		static constexpr float PITCH = 0.0f;

		static constexpr float SPEED = 2.5f;

		static constexpr float SENSITIVITY = 0.1f;

		static constexpr float MAX_FOV = 360.0f;

		float projNear = 0.01f;

		float projFar = 1000.0f;

		float FOV = 90.0f;

		glm::mat4 projection = glm::perspective(
			static_cast<double>(glm::radians(FOV)), static_cast<double>(800.0 / 600.0), 
			static_cast<double>(projNear), static_cast<double>(projFar));

		float movementSpeed;

		float mouseSensitivity;

		glm::vec3 position;

		glm::vec3 front;

		glm::vec3 up;

		glm::vec3 right;

		glm::vec3 worldUp;

		float yaw;

		float pitch;

		float lastMouseX = 0;

		float lastMouseY = 0;

		Frustum frustum;

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
			float argFOV = 90.0f);

		/**
		* @brief Returns View matrix.
		* @returns glm::mat4 View matrix.
		**/
		const glm::mat4 getViewMatrix() const;

		/**
		* @brief Returns projection space.
		* @return Projection space.
		**/
		const glm::mat4& getProjection() const;

		/**
		* @brief Returns frustum of camera.
		* @return Frustum.
		**/
		const Frustum& getFrustum() const;

		/**
		* @brief Sets projection space.
		* @param proj Projection space.
		**/
		void setProjection(const glm::mat4& proj);

		/**
		* @brief Updates projection. For example, update when screen resolution was changed (because of aspect value).
		**/		
		void updateProjection();

		/**
		* @brief Returns far value of projection space.
		* @return Far value.
		**/		
		float getNear();

		/**
		* @brief Sets far value for projection space.
		* @param far Near value.
		**/			
		void setNear(float near);

		/**
		* @brief Returns far value of projection space.
		* @return Far value.
		**/		
		float getFar();

		/**
		* @brief Sets far value for projection space.
		* @param far Far value.
		**/		
		void setFar(float far);

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
		* @return Sensitivity.
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

};

#endif
