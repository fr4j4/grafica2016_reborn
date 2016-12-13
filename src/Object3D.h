#ifndef OBJECT3D_H
#define OBJECT3D_H
#include <GL/glew.h>
#include <string>
#include <iostream>
#include <assert.h>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Tools.h"
#include "maths_funcs.h"

class Object3D{
protected:
	glm::mat4 T;
	glm::mat4 R;
	GLuint vao, vbo;
	GLuint* shader_programme;
	int numvertices;
	int mat_location=0;

public:
	glm::mat4 M;//matriz de transformacion
	mat4 M2;
	float rotateSpeed=0.025f;
	float moveSpeed=0.025f;
	Object3D(const char*,GLuint*);
	~Object3D();
	std::string name;
	glm::vec3 rotation;
	glm::vec3 pos;
	glm::vec3 scale;
	bool enabled;
	GLuint getVao();
	int getnumVertices();
	void move  (float x,float y,float z);
	void move_forward(float d);
	void move_backward(float d);
	void setPos(float x,float y,float z);
	virtual void rotate(float x,float y,float z);
	void set_scale(float,float,float);
	virtual void update();

	void render();
};



#endif