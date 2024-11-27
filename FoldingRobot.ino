#include <Servo.h>

Servo leftServo;  
Servo rightServo; 
Servo bottomServo; 

const int servoLeftStart = 150;
const int servoRightStart = 35;
const int servoBottomStart = 180;
int servoLeftCurrent = 0;
int servoRightCurrent = 0; 
int servoBottomCurrent = 0; 

const int timeBetweenMotion = 900;
const int increment = 5;
const int servoIncrement = 3;
const int servoIncrement2 = 15;

void setup() {
  Serial.begin(9600);

  leftServo.attach(13);  
  rightServo.attach(12); 
  bottomServo.attach(11);

  leftServo.write(servoLeftStart);
  rightServo.write(servoRightStart);
  bottomServo.write(servoBottomStart);

  servoLeftCurrent = servoLeftStart;
  servoRightCurrent = servoRightStart; 
  servoBottomCurrent = servoBottomStart; 
  Serial.println("START");
  Serial.println("Enter '1' to initiate the fold:");
  delay(2000);
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == '1') {
      // Repeat the folding sequence 5 times
      delay(10000);

      for (int i = 0; i < 50; i++) { 
        // Left servo fold

        for (servoLeftCurrent; servoLeftCurrent >= 50; servoLeftCurrent = servoLeftCurrent - increment) {
          leftServo.write(servoLeftCurrent);
          delay(servoIncrement);
        }
      

        // Right servo fold
        for (servoRightCurrent; servoRightCurrent <= 140; servoRightCurrent = servoRightCurrent + increment) { 
          servoLeftCurrent = servoLeftCurrent + increment; 
          rightServo.write(servoRightCurrent);
          leftServo.write(servoLeftCurrent);
          delay(servoIncrement);
        }

        for (servoRightCurrent; servoRightCurrent >= 80; servoRightCurrent = servoRightCurrent - increment) { 
          rightServo.write(servoRightCurrent);
          delay(servoIncrement);
        }

        // Bottom servo movement (and adjust right servo)
        for (servoBottomCurrent; servoBottomCurrent >= 40; servoBottomCurrent = servoBottomCurrent - increment) {
          servoRightCurrent = servoRightCurrent - increment;

          // Ensure servoRightCurrent doesn't go below 35
          if (servoRightCurrent < servoRightStart) {
            servoRightCurrent = servoRightStart;
          }

          rightServo.write(servoRightCurrent);
          bottomServo.write(servoBottomCurrent);
          delay(servoIncrement2);
        }

        // Return to starting position
        for (servoLeftCurrent; servoLeftCurrent < servoLeftStart; servoLeftCurrent = servoLeftCurrent + increment) {
          leftServo.write(servoLeftCurrent);
          delay(servoIncrement);
        }

        for (servoRightCurrent; servoRightCurrent >= servoRightStart; servoRightCurrent = servoRightCurrent - increment) { 
          rightServo.write(servoRightCurrent);
          delay(servoIncrement);
        }

        for (servoBottomCurrent; servoBottomCurrent < servoBottomStart; servoBottomCurrent = servoBottomCurrent + increment) { 
          bottomServo.write(servoBottomCurrent);
          delay(servoIncrement);
        }

        delay(timeBetweenMotion); // Delay between each fold
      } 
    }
  }
}