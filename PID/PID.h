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
	/**
	 * (P)roportional Tuning Parameter
     */
	double kp;
	/**
	 * (I)ntegral Tuning Parameter
	 */
	double ki;
	/**
	 * (D)erivative Tuning Parameter
	 */
	double kd;

	double lastInput;
	double integral;
	double lastError;

	double outMin, outMax;
};
#endif

