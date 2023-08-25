#ifndef __CONFIGS_H__
#define __CONFIGS_H__

#include <string.h>



//Piezo
#define PIEZO_PIN 4

//Card scanner
#define SS_PIN 10
#define RST_PIN 9

//Sensors
#define WATER_SENSOR A0
#define POTENTIOMETER A1

#define MOTOR_PIN 5

//Lights 0-Red Alert, 1-Light sensor, 2-blue, 3-red, 4 yellow, 5-green
#define ALERT 1
#define BLUE 2
#define RED 3
#define YELLOW 4
#define GREEN 5
#define PWM 5

//Lock
#define SERVO_PIN 8


#ifdef __cplusplus
 extern "C" {
#endif
//Any external function will be written here

#ifdef __cplusplus
}
#endif

#endif
