#include "Vehicle.h"

Vehicle::Vehicle(const char* file_name,GLuint* shader_programme):Object3D(file_name,shader_programme){
	velocity=0.0f;
}

void Vehicle::move_forward(){
	velocity=accel+velocity;
	pos.x-=velocity*cos(rotation.y);
	pos.z-=velocity*sin(rotation.y);
}

void Vehicle::move_backward(){
	velocity=decel-velocity;
	pos.x+=velocity*cos(rotation.y);
	pos.z+=velocity*sin(rotation.y);
}

void Vehicle::decelerate(){
	if(velocity>0){
		velocity=decel-velocity;
	}else if(velocity<0){
		velocity=decel+velocity;
	}
	pos.x+=velocity*cos(rotation.y);
	pos.z+=velocity*sin(rotation.y);
}

void Vehicle::brake(){

}

void Vehicle::update(){
	M=glm::mat4();
	M=glm::translate(M,pos);
	M=glm::scale(M,scale);
	M=glm::rotate(M,-rotation.y,glm::vec3(0.0f,1.0f,0.0f));
	M=glm::translate(M,glm::vec3(-0.250f,0.0f,0.0f));
}