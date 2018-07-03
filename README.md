rpiquad
======

Raspberry Pi based Quadcopter flight controller

Type 1:
Only RPi based,
1. PCA9685 for pwm control (ESC Management)
2. Wifi for wireless control
3. MPU6050 6DOF
4. GPS
5. wiringPi (gpio lib)

Type 2:
RPi + STM32 (programmable realtime unit)

STM32, based on stm32f103c8t6 (blue pill)
libopencm3 and https://github.com/ve3wwg/stm32f103c8t6.git


Purpose:
Just for fun....

NOTE: not using atmega anymore

X = roll Y = Pitch Z = Yaw

Received flight instructions formatted with good units, in that order : [Yaw, Pitch, Roll, Throttle]
 Units:
  - Yaw      : degree/sec
  - Pitch    : degree
  - Roll     : degree
  - Throttle : µs


movements CW: clockwise CCW: counter-clockwise

X configuration ------------------------------------------------
 M1	M2
(CW)   (CCW)

 M3	M4
(CCW)  (CW)

throttle control:
	Up :	M1 M2 M3 M4 +
	down :	M1 M2 M3 M4 -
Pitch control:
	forward :	(M1 = M2) < (M3 = M4)
	backward :	(M1 = M2) > (M3 = M4)
Roll control:
	bend left :	(M1 = M3) < (M2 = M4)
	bend right :	(M1 = M3) > (M2 = M4)
Yaw control:
	rotate left :	(M1 = M4) < (M2 = M3)
	rotate right :	(M1 = M4) > (M2 = M3)

+ configuration -------------------------------------------------
	 M1
	(CW)

 M4		 M2
(CCW)		(CCW)

	 M3
	(CW)

throttle control:
	Up :	M1 M2 M3 M4 +
	down :	M1 M2 M3 M4 -
Pitch control:
	forward :	(M1 = M2 = M4) < (M3)
	backward :	(M2 = M3 = M4) < (M1)
Roll control:
	bend left :	(M1 = M3) < (M2 = M4)
	bend right :	(M1 = M3) > (M2 = M4)
Yaw control:
	rotate left :	(M1 = M4) < (M2 = M3)
	rotate right :	(M1 = M4) > (M2 = M3)


+ configuration appears to be less power hungery but in X configuration rotors would not block view

PID (proportional, integral, derivative):

looptime: 1kHz (timer-event)

Proportional, 












----------------------------------------------------------------------------------------------------------------------------------------
Reference links,
https://github.com/lobodol/drone-flight-controller
