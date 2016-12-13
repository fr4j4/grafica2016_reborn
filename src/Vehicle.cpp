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
	velocity-=accel;
	pos.x-=velocity*cos(rotation.y);
	pos.z-=velocity*sin(rotation.y);
}

void Vehicle::girar(int sentido){
	float max=0.025f;//*(velocity*10);//giro maximo segun la velocidad
	if(sentido>0&&giro<0 || sentido<0&&giro>0){
		giro=0.0f;
	}else{
		if(fabs(giro)<max){//giro maximo
			giro+=giro_incremento*sentido;
		}else{
			giro=max*sentido;
		}
	}
	if(fabs(velocity)>0){
		Object3D::rotate(0.0f,giro,0.0f);
	}
}

void Vehicle::centrar(){
	if(fabs(giro)<0.00125f){
		giro=0.0f;
	}else{
		if(giro>0.0f){
			giro-=giro_incremento;
		}else if(giro<0.0f){
			giro+=giro_incremento;
		}
	}
}

void Vehicle::decelerate(){
	if(fabs(velocity)<0.00125f){
		velocity=0.0f;
	}else{
		if(velocity>0.0f){
			//printf("desacelerando...\n");
			velocity-=decel;
			pos.x-=velocity*cos(rotation.y);
			pos.z-=velocity*sin(rotation.y);
		}
		if(velocity<0.0f){
			//printf("desacelerando...\n");
			velocity+=decel;
			pos.x-=velocity*cos(rotation.y);
			pos.z-=velocity*sin(rotation.y);
		}
	}
}

void Vehicle::brake(){

}

void Vehicle::update(){
	Object3D::update();
	//system("clear");
	printf("\nCar_velocity: %f\n",velocity);
	printf("Car_giro    : %f\n",giro);
}