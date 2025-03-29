
// Motor Pins (same as your original setup)
int left_M1 = 4, left_M2 = 5, right_M1 = 6, right_M2 = 7;
int left_en = 9, right_en = 10;
int button = 12;

// PID Variables
float Kp = 1.7, Ki = 0.05, Kd = 0.5;
float error = 0, lastError = 0, P = 0, I = 0, D = 0;
int PIDvalue = 0;

// Sensors
#define sensorPins[] = {A0, A1, A2, A3, A4};
int sensorValues[5];

// Button Logic
bool button_stat = LOW, last = HIGH;

void setup() {
  pinMode(left_M1, OUTPUT); pinMode(left_M2, OUTPUT);
  pinMode(right_M1, OUTPUT); pinMode(right_M2, OUTPUT);
  pinMode(left_en, OUTPUT); pinMode(right_en, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  for (int i = 0; i < 5; i++) pinMode(sensorPins[i], INPUT);
}

void loop() {
  bool st = digitalRead(button);
  if (st == LOW && last == HIGH) {
    button_stat = !button_stat;
    delay(50); // Debounce
  }
  last = st;

  if (button_stat == HIGH) {
    readSensors();
    computePID();
    setMotors(150); // Base speed (0-255)
  } else {
    // Stop motors
    analogWrite(left_en, 0);
    analogWrite(right_en, 0);
  }
}

void readSensors() {
  for (int i = 0; i < 5; i++) {
    sensorValues[i] = (analogRead(sensorPins[i]) > 500 ? 1 : 0);
  }
  error = (-2 * sensorValues[0]) + (-1 * sensorValues[1]) + (0 * sensorValues[2]) +
          (1 * sensorValues[3]) + (2 * sensorValues[4]);
}

void computePID() {
  P = error;
  I += error;
  D = error - lastError;
  lastError = error;
  PIDvalue = (Kp * P) + (Ki * I) + (Kd * D);
}

void setMotors(int baseSpeed) {
  int leftSpeed = baseSpeed + PIDvalue;
  int rightSpeed = baseSpeed - PIDvalue;
  leftSpeed = constrain(leftSpeed, 0, 255);
  rightSpeed = constrain(rightSpeed, 0, 255);

  analogWrite(left_en, leftSpeed);
  analogWrite(right_en, rightSpeed);
  digitalWrite(left_M1, HIGH); digitalWrite(left_M2, LOW);
  digitalWrite(right_M1, HIGH); digitalWrite(right_M2, LOW);
}
