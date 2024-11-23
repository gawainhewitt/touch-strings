int xJoystick = 25;
int yJoystick = 24;
int joyButton = 3;
         
int buttonState; 
int lastButtonState = LOW;  
int joystickXPosition = 0;
int lastJoystickXPosition = 0;
int joystickYPosition = 0;
int lastJoystickYPosition = 0;

unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 50; 

void setupJoystick() {
    pinMode(xJoystick, INPUT);
    pinMode(yJoystick, INPUT);
    pinMode(joyButton, INPUT_PULLUP);
}
void selectItem(int buttonstatus) {
    if (buttonstatus == HIGH) {
        Serial.println("button off");
      } else {
        Serial.println("button on");
      }
}

void readButton() {
    int centreButtonReading = digitalRead(joyButton);

    if (centreButtonReading != lastButtonState) {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (centreButtonReading != buttonState) {
            buttonState = centreButtonReading;
            selectItem(buttonState);
        }
    }

    lastButtonState = centreButtonReading;
}

void readJoystick() {  
    readButton();

    int joystickCentre = 500;
    int joystickSensitivity = 100;

    int xPosition = analogRead(xJoystick);
    int yPosition = analogRead(yJoystick);

    if (xPosition < joystickCentre - joystickSensitivity) {
        joystickXPosition = -1;
    } else if (xPosition > joystickCentre + joystickSensitivity) {
        joystickXPosition = 1;
    } else {
        joystickXPosition = 0;
    }

    if (joystickXPosition != lastJoystickXPosition){
        Serial.print("X joystick = ");
        Serial.println(joystickXPosition);
        lastJoystickXPosition = joystickXPosition;
    }

    if (yPosition < joystickCentre - joystickSensitivity) {
        joystickYPosition = -1;
    } else if (yPosition > joystickCentre + joystickSensitivity) {
        joystickYPosition = 1;
    } else {
        joystickYPosition = 0;
    }

    if (joystickYPosition != lastJoystickYPosition){
        Serial.print("Y joystick = ");
        Serial.println(joystickYPosition);
        lastJoystickYPosition = joystickYPosition;
    }


}

