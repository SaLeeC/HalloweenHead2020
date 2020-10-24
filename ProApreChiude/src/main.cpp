#include <Arduino.h>

#define delayCiclo 1000

//   Board                     SERVO_PIN_A   SERVO_PIN_B   SERVO_PIN_C
//   -----                     -----------   -----------   -----------
//   Arduino Uno, Duemilanove       9            10          (none)
//   Arduino Mega                  11            12            13
//   Sanguino                      13            12          (none)
//   Teensy 1.0                    17            18            15
//   Teensy 2.0                    14            15             4
//   Teensy++ 1.0 or 2.0           25            26            27
//   Teensy LC & 3.x                 (all PWM pins are usable)

#include <PWMServo.h>
PWMServo myservo;  // create servo object to control a servo
int myservoPos = 0;    // variable to store the servo position

void FlipServo() {
  for(myservoPos = 0; myservoPos < 180; myservoPos += 1) { // goes from 0 degrees to 180 degrees, 1 degree steps
    myservo.write(myservoPos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for(myservoPos = 180; myservoPos >= 1; myservoPos -= 1) {   // goes from 180 degrees to 0 degrees
    myservo.write(myservoPos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

/*
 * Ultrasonic Simple
 * Prints the distance read by an ultrasonic sensor in
 * centimeters. They are supported to four pins ultrasound
 * sensors (liek HC-SC04) and three pins (like PING)))
 * and Seeed Studio sensors).
 *
 * The circuit:
 * * Module HR-SC04 (four pins) or PING))) (and other with
 *   three pins), attached to digital pins as follows:
 * ---------------------    --------------------
 * | HC-SC04 | Arduino |    | 3 pins | Arduino |
 * ---------------------    --------------------
 * |   Vcc   |   5V    |    |   Vcc  |   5V    |
 * |   Trig  |   12    | OR |   SIG  |   13    |
 * |   Echo  |   13    |    |   Gnd  |   GND   |
 * |   Gnd   |   GND   |    --------------------
 * ---------------------
 * Note: You do not obligatorily need to use the pins defined above
 * 
 * By default, the distance returned by the read()
 * method is in centimeters. To get the distance in inches,
 * pass INC as a parameter.
 * Example: ultrasonic.read(INC)
 *
 * created 3 Apr 2014
 * by Erick Simões (github: @ErickSimoes | twitter: @AloErickSimoes)
 * modified 23 Jan 2017
 * by Erick Simões (github: @ErickSimoes | twitter: @AloErickSimoes)
 * modified 03 Mar 2017
 * by Erick Simões (github: @ErickSimoes | twitter: @AloErickSimoes)
 * modified 11 Jun 2018
 * by Erick Simões (github: @ErickSimoes | twitter: @AloErickSimoes)
 *
 * This example code is released into the MIT License.
 */
#include <Ultrasonic.h>
/*
 * Pass as a parameter the trigger and echo pin, respectively,
 * or only the signal pin (for sensors 3 pins), like:
 * Ultrasonic ultrasonic(13);
 */
Ultrasonic ultrasonic(12, 13);
int usDistance = 0;
#define DistanzaMinima 150

void usRead() {
  // Pass INC as a parameter to get the distance in inches
  usDistance = ultrasonic.read();
  
  Serial.print("Distance in CM: ");
  Serial.println(usDistance);
  delay(1000);
}

void setup() 
{
  myservo.attach(SERVO_PIN_A);  // attaches the servo on pin 9 to the servo object
  //myservo.attach(SERVO_PIN_A, 1000, 2000); // some motors need min/max setting
}

void loop() 
{
  //Legge il sensore a ultrasuoni
  usRead();
  //Se la distanza misurata è minore a DistanzaMinima
  if (usDistance < DistanzaMinima)
  {
    //Mappa la distanza fra i 160 e i 50 cm su un angolo da 0 a 179 gradi
    myservoPos = map(usDistance, 160, 50, 0, 179);
  }
  delay(delayCiclo);
}