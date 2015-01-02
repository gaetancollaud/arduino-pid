/**********************************************************************************************
 * Arduino PID Library - Version 1.0.1
 * by Brett Beauregard <br3ttb@gmail.com> brettbeauregard.com
 *
 * This Library is licensed under a GPLv3 License
 **********************************************************************************************/

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "PID.h"

PID::PID(double Kp, double Ki, double Kd) {
	PID::setLimits(0, 255);
	PID::tune(Kp, Ki, Kd);
	this->reset();
	lastTime = micros();
	this->lastInput = 0.0;
}

double PID::compute(double input, double setPoint, double dt) {
	double error = setPoint - input;

	integral += error * dt;

	//Normally "(error - lastError) / dt", but this avoid derivativ kick as explain in
	//http://brettbeauregard.com/blog/2011/04/improving-the-beginner%E2%80%99s-pid-derivative-kick/
	double derivative = -(input - lastInput) / dt;
	//double derivative = (error - lastError) / dt;

	double output = this->kp * error + this->ki * integral + this->kd * derivative;

	this->lastError = error;
	this->lastInput = input;
	
	return constrain(output, outMin, outMax);
}

void PID::tune(double Kp, double Ki, double Kd) {
	this->kp = Kp;
	this->ki = Ki;
	this->kd = Kd;
}

void PID::setLimits(double Min, double Max) {
	if (Min >= Max) return;
	outMin = Min;
	outMax = Max;
}

void PID::reset() {
	integral = 0.0;
	lastError = 0.0;
	lastTime = micros();
}
