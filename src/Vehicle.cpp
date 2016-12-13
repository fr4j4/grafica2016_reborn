#include "Vehicle.h"

Vehicle::Vehicle(const char* file_name,GLuint* shader_programme):Object3D(file_name,shader_programme){
	velocity=0.0f;
}

void Vehicle::move_forward(){
	printf("acelerando...\n");
	velocity+=accel;
	pos.x-=velocity*cos(rotation.y);
	pos.z-=velocity*sin(rotation.y);
}

void Vehicle::move_backward(){
	/*
	velocity+=accel;
	pos.x+=velocity*cos(rotation.y);
	pos.z+=velocity*sin(rotation.y);
	*/
}

void Vehicle::rotate(float x,float y,float z){
	if(fabs(velocity)>0){
		Object3D::rotate(x,y,z);
	}
}

void Vehicle::decelerate(){
	if(fabs(velocity)<0.00125f){
		velocity=0.0f;
	}else{
	if(velocity>accel){
		//printf("desacelerando...\n");
		velocity=decel-velocity;
	}
	if(velocity<accel){
		//printf("desacelerando...\n");
		velocity=decel+velocity;
	}
	pos.x+=velocity*cos(rotation.y);
	pos.z+=velocity*sin(rotation.y);
	}
}

void Vehicle::brake(){

}

void Vehicle::update(){
	M=glm::mat4();
	M=glm::translate(M,pos);
	M=glm::scale(M,scale);
	M=glm::rotate(M,-rotation.y,glm::vec3(0.0f,1.0f,0.0f));
	M=glm::translate(M,glm::vec3(-0.650f,0.0f,0.0f));
	printf("Car_velocity: %f\n",velocity);
}