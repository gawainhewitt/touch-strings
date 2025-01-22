#define UP 0
#define LEFT 1
#define CENTRE 2
#define RIGHT 3
#define DOWN 4
#define NUM_BUTTONS 5

boolean bigMenu = false;
boolean updateDisplayFlag = true;

int activeMenuInput = 0;
byte menuItems = 4;

byte buttonStates[NUM_BUTTONS];

unsigned int scrollTime = 250;
long unsigned int heldTimer = 0;
long unsigned int menuTimer = 0;

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

void updateButtonState(int button, int buttonState) {
    if (buttonStates[button] == 3) {
      buttonStates[button] = 2;
    }
    if ((buttonState == 1) && (buttonStates[button] == 0)) {
      buttonStates[button] = 3;
      heldTimer = millis();
      menuTimer = millis();
      bigMenu = false;
    }
    if (buttonStates[button] == 1) {
      buttonStates[button] = 0;
    }
    if ((buttonState == 0) && (buttonStates[button] == 2)) {
      buttonStates[button] = 1;
    }
    //0-off
    //3-momentary on
    //2-on
    //1-momentary off
    // Serial.println(buttonStates);
    // Serial.print("button ");
    // Serial.print(button);
    // Serial.print(": state is ");
    // Serial.println(buttonStates[button]);
}

void readButton() {
    int centreButtonReading = digitalRead(joyButton);

    if (centreButtonReading != lastButtonState) {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (centreButtonReading != buttonState) {
            buttonState = centreButtonReading;
            updateButtonState(CENTRE, buttonState);
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
        updateButtonState(LEFT, 1);
        updateButtonState(RIGHT, 0);
    } else if (xPosition > joystickCentre + joystickSensitivity) {
        joystickXPosition = 1;
        updateButtonState(LEFT, 0);
        updateButtonState(RIGHT, 1);
    } else {
        joystickXPosition = 0;
        updateButtonState(LEFT, 0);
        updateButtonState(RIGHT, 0);
    }

    

    if (joystickXPosition != lastJoystickXPosition){
        Serial.print("X joystick = ");
        Serial.println(joystickXPosition);
        lastJoystickXPosition = joystickXPosition;
    }

    if (yPosition < joystickCentre - joystickSensitivity) {
        joystickYPosition = -1;
        updateButtonState(DOWN, 1);
        updateButtonState(UP, 0);
    } else if (yPosition > joystickCentre + joystickSensitivity) {
        joystickYPosition = 1;
        updateButtonState(DOWN, 0);
        updateButtonState(UP, 1);
    } else {
        joystickYPosition = 0;
        updateButtonState(DOWN, 0);
        updateButtonState(UP, 0);
    }

    if (joystickYPosition != lastJoystickYPosition){
        Serial.print("Y joystick = ");
        Serial.println(joystickYPosition);
        lastJoystickYPosition = joystickYPosition;
    }
}


void joyStickActions() {
  if (buttonStates[UP] == 3) {
    Serial.print("up menu: ");
    Serial.println(activeMenuInput);
    Serial.print("buttonState ");
    Serial.println(buttonStates[0]);
    activeMenuInput--;
  }

  if (buttonStates[DOWN] == 3) {
    Serial.print("down menu: ");
    Serial.println(activeMenuInput);
    activeMenuInput++;
  }

  if (buttonStates[LEFT] == 3) {
    switch (activeMenuInput) {
      case 0:
        keyPosition = keyPosition - 1;
        if (keyPosition < 0) {
          keyPosition = 11;
        }
        keyName = noteNames[keyPosition];
        break;
      case 1:
        currentScale = currentScale - 1;
        if (currentScale < 0) {
          currentScale = numScales - 1;
        }
        changeScale(currentScale);
        break;
      case 2:
        currentFunction = currentFunction - 1;
        if (currentFunction < 0) {
          currentFunction = numFunctions - 1;
        }
        break;
      case 3:
        mainVolume = mainVolume - 0.01;
        if (mainVolume < 0) {
          mainVolume = 0;
        }
        changeMainVolume();
    }
  }

  if (buttonStates[CENTRE] == 3) {
    switch (activeMenuInput) {
      case 0:
        // Serial.print("centre menu: ");
        // Serial.println(activeMenuInput);
        break;
      case 4:
        // Serial.print("centre menu: ");
        // Serial.println(activeMenuInput);
        break;
    }
  }

  if (buttonStates[RIGHT] == 3) {
    switch (activeMenuInput) {
      case 0:
        keyPosition = keyPosition + 1;
        if (keyPosition > 11) {
          keyPosition = 0;
        }
        keyName = noteNames[keyPosition];
        keyName = noteNames[keyPosition];
        break;
      case 1:
        currentScale = currentScale + 1;
        if (currentScale > numScales - 1) {
          currentScale = 0;
        }
        changeScale(currentScale);
        break;
      case 2:
        currentFunction = currentFunction + 1;
        if (currentFunction > numFunctions - 1) {
          currentFunction = 0;
        }
        break;
      case 3:
        mainVolume = mainVolume + 0.01;
        if (mainVolume > 1) {
          mainVolume = 1;
        }
        changeMainVolume();
    }
  }

  if (activeMenuInput < 0) {
    activeMenuInput = menuItems - 1; //menu looping
  } else if (activeMenuInput > (menuItems - 1)) {
    activeMenuInput = 0;
  }

  for (int i = 0; i < NUM_BUTTONS; i++) {
    if ((buttonStates[i] == 2) && ((millis() - heldTimer) > scrollTime)) { //if a button has been held for enough time
      buttonStates[i] = 0;
      updateDisplayFlag = true;
      //saveState();
      return;
    } else if (buttonStates[i] == 1) { //if a button has been released
      updateDisplayFlag = true;
      return;
    }
  }

  if ((millis() - menuTimer) > 10000 && bigMenu == false) {
    bigMenu = true;
    updateDisplayFlag = true;
  }
}
