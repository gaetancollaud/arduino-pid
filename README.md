arduino-pid
===========

An arduino library to simply use a PID controller.

This implementation is based on the [wikipedia article](http://en.wikipedia.org/wiki/PID_controller#Pseudocode). Some improvement have been taken from [brettbeauregard.com](http://brettbeauregard.com/blog/2011/04/improving-the-beginners-pid-introduction/).


## Installation

Put the _PID_ directory in the arduino library folder (Usually _C:\Program Files (x86)\Arduino\libraries_). Don't forget to restart the Arduino IDE after installation

## Usage

First you must include the library

```c
#include <PID.h>
```

Then create an instance
```c
//PID (proportional, integral, derivative)
PID myPId(1.0, 2.0, 3.0);
```

Then compute value from input
```c
//output = PID.compute(input, setpoint, dt)
double myOuptut = myPId.compute(myInput, mySetPoint, loopDt);
```

#Example 
```c
double loopLastTime;
PID myPId(1.0, 2.0, 3.0);

void setup(){
  loopLastTime = micros();
}
void loop(){
  double loopNow = micros();
  double loopDt = ((double) loopNow - loopLastTime)*0.000001;//delta time [s]
  loopLastTime = loopNow;
  
  double mySetPoint = 0.0; //we want to go to zero
  double myInput = analogRead(A0);//put some sensor reading here
  
  double myOuptut = myPId.compute(myInput, mySetPoint, loopDt);
  
  //by default the limits are [0,255]
  analogWrite(13, myOutput);
  
  
  delay(100);
}
```


