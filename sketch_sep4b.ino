int xPin = A4;  // X-axis pin
int yPin = A5;  // Y-axis pin

int xValue; // X value
int yValue; // Y value

int buttonState = 0; // Joystick button

int lastX = 0;  // Store last X value
int lastY = 0;  // Store last Y value

/// LEDs on the breadboard & joystick button
#define UP_LED 10
#define RIGHT_LED 11
#define LEFT_LED 8
#define DOWN_LED 9
#define BUTTONDOWN 13

/// Defining pins and starting COM port
void setup() {
  pinMode(xPin,   INPUT);
  pinMode(yPin,   INPUT);
  pinMode(BUTTONDOWN, INPUT);
  pinMode(UP_LED , OUTPUT);
  pinMode(RIGHT_LED , OUTPUT);
  pinMode(LEFT_LED , OUTPUT);
  pinMode(DOWN_LED , OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int xValue = analogRead(xPin);  // Read X value
  int yValue = analogRead(yPin);  // Read Y value
  buttonState = digitalRead(BUTTONDOWN);

  /// Only print if X or Y value has changed
  if (xValue != lastX || yValue != lastY) {
    
    /// Printing to COM port
    if (xValue > 500 && xValue < 510) { Serial.print(512); } else { Serial.print(xValue); } // Stick drift prevention
    Serial.print(",");
    if (yValue > 490 && yValue < 500) { Serial.print(512); } else { Serial.print(yValue); } // Stick drift prevention
    Serial.print(",");
    Serial.println(buttonState);

    /// Turning off LEDs after loop
    digitalWrite(UP_LED, LOW);
    digitalWrite(DOWN_LED, LOW);
    digitalWrite(LEFT_LED, LOW);
    digitalWrite(RIGHT_LED, LOW);

    /// Turning on LEDs depending on the direction of the joystick
    if (yValue < 300) {
      digitalWrite(UP_LED, HIGH);
    }
    else if (yValue > 800) {
      digitalWrite(DOWN_LED, HIGH);
    }
    else if (xValue < 200) {
      digitalWrite(RIGHT_LED, HIGH);
    }
    else if (xValue > 800) {
      digitalWrite(LEFT_LED, HIGH);
    }

    
    // Update last values
    lastX = xValue;
    lastY = yValue;
  }

  delay(1);
}