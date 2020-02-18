
  //////////////////\\\\\\\\\\\\\\\\\\
  //                                \\
  //  CMD Breda, Avans Hogeschool   \\
  //  Werkplaats instructies        \\
  //  Corne Ossenblok &             \\
  //  Scott van Haastrecht          \\
  //                                \\
  //  23-08-2019                    \\
  //                                \\
  //////////////////\\\\\\\\\\\\\\\\\\


/*=================== SETTINGS ===================*/
#include <Servo.h>

// INPUT - constants won't change. They're used here to set pin numbers:
const int btn_Pin = 2;      // Digital input pin for the pushbutton pin
const int ldr_Pin = A0;     // Analog input pin for the LDR sensor
const int pot_Pin = A1;     // Analog input pin for the potentiometer

// OUTPUT - constants won't change. They're used here to set pin numbers:
Servo servo_Mot;            // create servo object to control a servo
const int LED_Mot = 11;       // the number of the DC motor pin
const int btn_Led = 8;     // the number of the LED pin

// Variables will/can change
int buttonState = 0;        // variable for reading the pushbutton status
int ldrValue = 0;           // variable to store the value coming from the LDR sensor
int potValue = 0;           // variable to store the value coming from the Potmeter sensor
int servo_Pos = 0;          // variable to store the value converted from LRD -> Servo motor
int pwm_Value = 0;          // variable to store the value converted from Potmeter -> DC motor & LED


/*===================== SETUP =====================*/
void setup() {
  // put your setup code here, to run once:
  servo_Mot.attach(6);        // attaches the servo on pin 6 to the servo object
  pinMode(btn_Pin, INPUT);
  pinMode(LED_Mot, OUTPUT);
  pinMode(btn_Led, OUTPUT);
}


/*====================== LOOP ======================*/
void loop() {
  // read and store the value of the input devices (button, LDR & potentiometer)
  ldrValue = analogRead(ldr_Pin);
  potValue = analogRead(pot_Pin);
  buttonState = digitalRead(btn_Pin);
  
  // Button & LED
  // if button is pressed turn LED on, if not pressed, turn LED off
  if (buttonState == HIGH) {
    digitalWrite(btn_Led, HIGH);
  } else {
    digitalWrite(btn_Led, LOW);
  }

  // LDR & Servo
  // scale the analog input from the LDR (0-1023) to a usable range
  // for the PWM pin (digital output with wave symbol ~)
  // sets the servo position according to the scaled value
  servo_Pos = map (ldrValue, 500, 1023, 0, 180);
  servo_Mot.write(servo_Pos);                  

  // Potmeter & DC motor / LED
  // scale the analog input from the potentiometer (0-1023) to a 
  // usable range for the PWM pin (digital output with wave symbol ~)
  // sets the dc motor speed and LED brightness according to the scaled value
  pwm_Value = map (potValue, 0, 1023, 0, 255);
  analogWrite(LED_Mot, pwm_Value);
}
