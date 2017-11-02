#pragma once

#include <vector>
#include <cstdlib>
#include <iostream>

#include "GL\glew.h"
#include "glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

//axis-aligned bounding box
class AABB
{
private:
	static GLuint boxCount;

public:

	glm::vec4 min;
	glm::vec4 max;

	inline AABB() : min(-10.5f, -10.5f, -10.5f, 1.0f), max(1.5f, 1.5f, 1.5f, 1.0f) {
		boxCount++;
	}
	inline AABB(glm::vec3 mi, glm::vec3 ma) : min(mi.x, mi.y, mi.z, 1.0f), max(ma.x, ma.y, ma.z, 1.0f) {
		boxCount++;
	}
	~AABB();

	inline bool intersects(const AABB& b2) const {
		//// Use up to 6 separating planes
		//if (max.x < b2.min.x)
		//	return false;
		//if (max.y < b2.min.y)
		//	return false;
		//if (max.z < b2.min.z)
		//	return false;
		//if (min.x > b2.max.x)
		//	return false;
		//if (min.y > b2.max.y)
		//	return false;
		//if (min.z > b2.max.z)
		//	return false;
		//// otherwise, must be intersecting
		//return true;

		return(max.x > b2.min.x &&
			min.x < b2.max.x &&
			max.y > b2.min.y &&
			min.y < b2.max.y &&
			max.z > b2.min.z &&
			min.z < b2.max.z);
	}

	inline void transform(const glm::mat4 mat) {
		min = mat * min;
		max = mat * max;
	}

	inline void scale(GLfloat s) {
		glm::mat4x4 scaleMat = glm::mat4();
		scaleMat = glm::scale(scaleMat, glm::vec3(s, s, s)); // scaling with matrix NOT A SCALAR value

		min = scaleMat * min;
		max = scaleMat * max;
	}

	inline void draw(glm::mat4x4 mat) {
		GLuint aabbVBO = 3;

		//align visual with actual data NOT INVERTING THE MATRIX DESTROYS EVERYTHING YOU LOVE
		glm::vec4 tMax = glm::inverse(mat) * max;
		glm::vec4 tMin = glm::inverse(mat) * min;

		std::vector<glm::vec3> vertices({
		glm::vec3(tMin.x, tMin.y, tMin.z),//front using line loop should be tMinimum side
		glm::vec3(tMin.x, tMax.y, tMin.z),
		glm::vec3(tMax.x, tMax.y, tMin.z),
		glm::vec3(tMax.x, tMin.y, tMin.z),

		glm::vec3(tMin.x, tMax.y, tMax.z),//back using line loop
		glm::vec3(tMin.x, tMin.y, tMax.z),
		glm::vec3(tMax.x, tMin.y, tMax.z),
		glm::vec3(tMax.x, tMax.y, tMax.z),

		//sides, 4 lines, 2 verts each = 8 connectors for front and back
		glm::vec3(tMin.x, tMax.y, tMin.z), //1-4
		glm::vec3(tMin.x, tMax.y, tMax.z),
		glm::vec3(tMax.x, tMax.y, tMin.z), //2-7
		glm::vec3(tMax.x, tMax.y, tMax.z),
		glm::vec3(tMax.x, tMin.y, tMin.z), //3-6
		glm::vec3(tMax.x, tMin.y, tMax.z),
		glm::vec3(tMin.x, tMin.y, tMin.z), //0-5
		glm::vec3(tMin.x, tMin.y, tMax.z),
		});

		glGenBuffers(1, &aabbVBO);
		glBindBuffer(GL_ARRAY_BUFFER, aabbVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), &vertices.front(), GL_STATIC_DRAW);

		GLint colorAttrib = glGetAttribLocation(3, "color"); //programID is 3 for some reason
		glVertexAttrib3f(colorAttrib, 0.0f, 1.0f, 1.0f); //cyan

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe

		GLint posAttrib = glGetAttribLocation(3, "vPosition");
		glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(posAttrib);

		//send matrix to shader
		GLint modelUniform = glGetUniformLocation(3, "vModel");
		glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(mat));

		glDrawArrays(GL_LINE_LOOP, 0, 4); //front
		glDrawArrays(GL_LINE_LOOP, 4, 4); //back
		glDrawArrays(GL_LINES, 8, 8); //connect
	}
};
