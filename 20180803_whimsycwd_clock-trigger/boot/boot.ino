
#include <Stepper.h>

const int stepsPerRevolution = 48;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

int led = 9;           // the PWM pin the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  Serial.begin(115200);
//  Serial1.begin(115200);
  
//  pinMode(led, OUTPUT);
  pinMode(3, INPUT);  // hall
  pinMode(13, OUTPUT);  // light
  pinMode(2, INPUT); //button
//  pinMode(5, INPUT); // endstop
//  pinMode(10, OUTPUT);  test output

 myStepper.setSpeed(60);
}


int buttonState = 0;
int k = 0;
int sensorState = 1;
long lastDebounceTime = 0;
long debounceDelay = 50;

long lastButtonState = LOW;
long lastButtonDebounceTime = 0;
long buttonDebounceDelay = 50;

int servor = 0;
long lastServor = 0;
int step_moter = 0;

// the loop routine runs over and over again forever:
void loop() {
//  int endstop = digitalRead(5);
//  Serial.println(endstop);

//  if (millis() - lastServor > 1000) {
//    if (servor == 0) {
//      analogWrite(10, 0);
//    } else {
//      analogWrite(10, 255);
//    }
//    servor = 1 - servor;
//    
//    lastServor = millis();
//  } 
  
  int t = digitalRead(3);
  // Serial.println(t);
  
  buttonState = digitalRead(2);

// Move 10mm
   unsigned char buff[] = {0xAA, 0x55, 0x05, 0x06, 0x1D, 0x00, 0x00,  0x01, 0xDC};


// 3D Pause
//  unsigned char buff[] = {0xAA, 0x55, 0x05, 0x00, 0x30, 0x00, 0x00,  0x01, 0xCF};

// 3D Resume 
//  unsigned char buff[] = {0xAA, 0x55, 0x05, 0x00, 0x31, 0x00, 0x00,  0x01, 0xCF};


  // Pause
  unsigned char pause_buff[] = {0xAA, 0x55, 0x05, 0x0F, 0x3F, 0x00, 0x00,  0x01, 0xB1};

  // Resume 
  unsigned char resume_buff[] = {0xAA, 0x55, 0x05, 0x0F, 0x3E, 0x00, 0x00,  0x01, 0xB2};

//  for (int i = 0; i < sizeof(buff); ++i) {
//    Serial.write(buff[i]);
//  }
//  Serial.write(buff, sizeof(buff));
  // Serial.write(pause_buff, sizeof(pause_buff));
//  Serial.write(resume_buff, sizeof(resume_buff));

  if (buttonState != lastButtonState) {
    if (millis() - lastButtonDebounceTime > buttonDebounceDelay) {
      if (buttonState == HIGH) {
        
        digitalWrite(13, HIGH);
        
    //    Serial.write(resume_buff, sizeof(resume_buff));
    
                  step_moter = 1 - step_moter; // switch.
        Serial.println(step_moter);
      
    
     
      } else {
        digitalWrite(13, LOW);
     
    //    Serial.write(pause_buff, sizeof(pause_buff));
      }

      lastButtonState = buttonState;
        
      lastButtonDebounceTime = millis();
      
    }
  }


  if (step_moter == 1) {
    if (millis() - lastDebounceTime > debounceDelay) {
      if (t != sensorState) {
           if (t == 0) {
              k = k + 1;
              if (k % 2 == 1) {
                 Serial.write(pause_buff, sizeof(pause_buff));
              } else {
                 Serial.write(resume_buff, sizeof(resume_buff));
              }  
            }

            sensorState = t;
            lastDebounceTime = millis();
      }
      
    
    }
    
  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
//  delay(500);

  // step one revolution in the other direction:
//  Serial.println("counterclockwise");
//  myStepper.step(-stepsPerRevolution);
//  delay(500);
    
  } else {
    myStepper.step(0);
  }

//  delay(30);
}
