#include "Arduino.h"

#include "PID.h"

PID::PID(double Kp, double Ki, double Kd) {
	PID::setLimits(0, 255);
	PID::tune(Kp, Ki, Kd);
	this->reset();
	this->lastInput = 0.0;
}

double PID::compute(double input, double setPoint, double dt) {
	double error = setPoint - input;

	//Integrate error with delta time
	integral += error * dt;

	//Derive error over time
	//Normally "(error - lastError) / dt", but this avoid derivativ kick as explain in
	//http://brettbeauregard.com/blog/2011/04/improving-the-beginner%E2%80%99s-pid-derivative-kick/
	double derivative = -(input - lastInput) / dt;
	//double derivative = (error - lastError) / dt;

	//compute pid
	double output = this->kp * error + this->ki * integral + this->kd * derivative;

	//store error and input for next loop
	this->lastError = error;
	this->lastInput = input;
	
	//constraint the ouptut
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
}
