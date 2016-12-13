#ifndef VEHICLE_H
#define VEHICLE_H
#include "Object3D.h"

class Vehicle : public Object3D{
public:
	float velocity=0.0f;
	float accel=0.000125f;//aceleracion
	float decel=0.000125f;//desaceleracion
	float decel_brake=0.75f;//freno
	
	Vehicle(const char*,GLuint*);
	~Vehicle();
	
	void move_forward();
	void move_backward();
	void brake();
	void update();//sobre-escritura metodo update
	void rotate(float,float,float);
	void decelerate();
};
#endif