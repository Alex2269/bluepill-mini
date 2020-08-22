/*
  PhotonPWM.h - Library for enabling 16-Bit PWM output on the Particle Photon
  Created by Brendan Spijkerman, Januari 26, 2016.
  Released into the public domain.
*/

#ifndef PhotonPWM_h
#define PhotonPWM_h

#include "stdint.h"
// #include "application.h"

class PhotonPWM {
	public:
		PhotonPWM();
		void initTimers();
		void analogWrite16(uint8_t pin, unsigned int dutyCycle);
		void analogWrite16GC(uint8_t pin, unsigned int dutyCycle);
};

#endif
