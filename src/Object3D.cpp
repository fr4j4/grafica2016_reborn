#include "Object3D.h"
#include <math.h>

Object3D::Object3D(const char* file_name,GLuint* shader_programme){
	this-> shader_programme=shader_programme;
	assert(tools::load_mesh(file_name, &vao, &numvertices));
	glUseProgram (*shader_programme);
	mat_location = glGetUniformLocation (*shader_programme, "model");
	M=glm::mat4();
	R=glm::mat4();
	T=glm::mat4();
	pos=glm::vec3();
	scale=glm::vec3(1.0f,1.0f,1.0f);
	rotation=glm::vec3();
	enabled=true;
	update();
}

int Object3D::getnumVertices(){
	return this->numvertices;
}

GLuint Object3D::getVao(){
	return this->vao;
}

void Object3D::move(float x,float y,float z){
	pos.x+=x;
	pos.y+=y;
	pos.z+=z;
}

void Object3D::move_forward(float d){
	float newX=d*cos(rotation.y);
	float newZ=d*sin(rotation.y);
	pos.x-=newX;
	pos.z-=newZ;
}

void Object3D::move_backward(float d){
	pos.x+=d*cos(rotation.y);
	pos.z+=d*sin(rotation.y);
}

void Object3D::setPos(float x,float y,float z){
	pos.x=x;
	pos.y=y;
	pos.z=z;
}

void Object3D::set_scale(float x,float y,float z){
	scale.x=x;
	scale.y=y;
	scale.z=z;
}

void Object3D::rotate(float x,float y,float z){
	rotation.x=fmod(rotation.x+x,2.0f*M_PI);
	rotation.y=fmod(rotation.y+y,2.0f*M_PI);
	rotation.z=fmod(rotation.z+z,2.0f*M_PI);
}

 void Object3D::update(){
	M=glm::mat4();
	M=glm::translate(M,pos);
	M=glm::scale(M,scale);
	M=glm::rotate(M,-rotation.y,glm::vec3(0.0f,1.0f,0.0f));
	M=glm::translate(M,glm::vec3(-0.250f,0.0f,0.0f));
}

void Object3D::render(){
	glUniformMatrix4fv (mat_location, 1, GL_FALSE, glm::value_ptr(M));
	glBindVertexArray(getVao());
	glDrawArrays(GL_TRIANGLES,0,getnumVertices());
}
