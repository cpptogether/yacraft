#ifndef ENGINE_FRUSTUM_H
#define ENGINE_FRUSTUM_H

#include <glm/glm.hpp>
#include <vector>

namespace Engine{

	class Frustum{
	private:
		float frustum[6][4];
	public:
		Frustum();

		Frustum(glm::mat4& proj, glm::mat4& modl);

		/**
		* @brief Updates frustum matrix.
		* @param projection Projection space modelView View space.
		**/
		void updateFrustum(const glm::mat4& projection, const glm::mat4& modelView);

		/**
		* @brief Checks, if point intersect frustum.
		* @param pos Position of point.
		* @return Is it intersect?
		**/
		bool intersectPoint(const glm::vec3& pos) const;

		/**
		* @brief Checks, if sphere intersect frustum.
		* @param pos Position of sphere. radius Radius of sphere.
		* @return Is it intersect?
		**/
		bool intersectSphere(const glm::vec3& pos, float radius) const;

		/**
		* @brief Checks, if cube intersect frustum.
		* @param pos Position of cube. radius Size of cube.
		* @return Is it intersect?
		**/
		bool intersectCube(const glm::vec3& pos, float size) const;

		/**
		* @brief Checks, if polygon intersect frustum.
		* @param pointlist List of verteces to check.
		* @return Is it intersect?
		**/
		bool intersectPolygon(const std::vector<glm::vec3>& pointlist) const;
	};

};

#endif