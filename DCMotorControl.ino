// Define pins
int drivePin      = 9; // Driving the motor(PWM)
int startStopPin  = 8; // Start and stop(buttom)
int gofixPin      = 7; // Go a fixed distance(buttom)
int speedPot      = 0; // Determine the motorspeed(potmeter)

// Define variables
int speedValue    = 0; // Selected speed
int driveState    = HIGH;
int lastDriveState    = LOW; // Buttom value 0=stop, 1=drive 

//Botton Variables
int buttonState;                          // the current reading from the input pin
int lastButtonState             = HIGH;    // the previous reading from the input pin
unsigned long lastDebounceTime  = 0;      // the last time the output pin was toggled
unsigned long debounceDelay     = 50;     // the debounce time; increase if the output flickers
bool bottonState                = true;
 
void setup() {
  pinMode(drivePin, OUTPUT);
  pinMode(startStopPin, INPUT);
  pinMode(speedPot, INPUT);
  digitalWrite(drivePin,HIGH);
  Serial.begin(115200);
  Serial.println("DCMotorControl");
}

// the loop function runs over and over again forever
void loop() {
  bottonHandling();

  Serial.print("driveState=" + String(driveState));
  Serial.print("\n");

  speedValue = analogRead(speedPot);
  speedValue = map(speedValue, 0, 1023, 0, -255);
  
  Serial.print("speedValue=" + String(speedValue));
  Serial.print("\n");

  if (driveState == HIGH) {
        analogWrite(drivePin,LOW);
      }
      else {
        analogWrite(drivePin,HIGH);
      }
  
  Serial.print("drivePin=" + String(digitalRead(drivePin)));
  Serial.print("\n");
delay(1000);
}

void bottonHandling(){  
  int reading = digitalRead(startStopPin); // check to see if you just pressed the button
  // if (reading != lastButtonState) {     // If the switch changed, due to noise or pressing:
  //   lastDebounceTime = millis();        // reset the debouncing timer
  // }
  
  // if ((millis() - lastDebounceTime) > debounceDelay) {     // whatever the reading is at, it's been there for longer than the debounce
    if (reading != buttonState) {                          // delay, so take it as the actual current state:
      buttonState = reading;                            
      if (buttonState == HIGH) {                           // if the button state has changed:   
         driveState = !driveState;
      }
    }
  // }
  // lastButtonState = reading;                  // save the reading. Next time through the loop, it'll be the lastButtonState: 
}