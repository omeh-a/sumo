//HC-SR04   https://create.arduino.cc/projecthub/abdularbi17/ultrasonic-sensor-hc-sr04-with-arduino-tutorial-327ff6
//DataSheet https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf 
#define ECHO_PIN 12
#define TRIG_PIN 11

//L298 dual full H-Bridge
#define IN1 7
#define IN2 6

#define IN3 3
#define IN4 2

long wait;
int distance;

int main() {
  init();
  
  Serial.begin (9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);

  pinMode(IN1, OUTPUT);
  digitalWrite(IN1, LOW);
  pinMode(IN2, OUTPUT);
  digitalWrite(IN2, LOW);
  pinMode(IN3, OUTPUT);
  digitalWrite(IN3, LOW);
  pinMode(IN4, OUTPUT);
  digitalWrite(IN4, LOW);
  
  drive(255);

  for(;;) {
    sense();
    delay(300);
  }
}


//Returns distance in CM, do not call without delay between!
int sense(){
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  wait = pulseIn(ECHO_PIN, HIGH);
  distance = wait*0.0343/2;
  Serial.print("Distance: ");
  Serial.println(distance);

  return distance;
}

//0-255, -'ve backwards
void drive(int speed) {
  stopMotors();
  if (speed >= 0) {
    analogWrite(IN1, speed);
    analogWrite(IN3, speed);
  } else {
    analogWrite(IN2, speed);
    analogWrite(IN4, speed);
  }
}

//Speed 0-255, direction: -1 Left, 1 Right
void turn(int speed, int direction) {
  stopMotors();
  if (direction == 1) {
    analogWrite(IN1, speed);
    analogWrite(IN4, speed);
  } else if (direction == -1) {
    analogWrite(IN2, speed);
    analogWrite(IN3, speed);
  }
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
