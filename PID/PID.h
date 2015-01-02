#ifndef PID_h
#define PID_h

class PID {
public:

	PID(double kp, double ki, double kd);

	double compute(double input, double setPoint, double dt);
	
	void setLimits(double min, double max);

	void tune(double kp, double ki, double kd);

	void reset();

private:
	double kp; // * (P)roportional Tuning Parameter
	double ki; // * (I)ntegral Tuning Parameter
	double kd; // * (D)erivative Tuning Parameter

	unsigned long lastTime;
	double lastInput;
	double integral, lastError;

	double outMin, outMax;
};
#endif

