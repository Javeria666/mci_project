

#include <Servo.h>

// --- Servo and RGB Setup ---
Servo myservo;
const int servoPin = 26; // PD3
const int red = 30, blue = 40, green = 39; // RGB LED pins

// --- Motor A (Left Motor) ---
int enA = 40; // PF2
int in1 = 12; // PA3
int in2 = 10; // PA7

// --- Motor B (Right Motor) ---
int enB = 37; // PC4
int in3 = 13; // PA4
int in4 = 27; // PE1

// --- Ultrasonic Sensor Pins ---
const int frontTrig = 2, frontEcho = 24;   // PB5, PD1
const int leftTrig = 30, leftEcho = 4;     // PF1, PB1
const int rightTrig = 26, rightEcho = 19;  // PD3, PB2

long cmFront, cmLeft, cmRight;

// --- Control Flags ---
char received = ' ';
bool carRunning = false;

void setup() {
    Serial.begin(9600);

    // RGB LED pins
    pinMode(red, OUTPUT); pinMode(green, OUTPUT); pinMode(blue, OUTPUT);
    analogWrite(red, 0); analogWrite(green, 0); analogWrite(blue, 0);

    // Servo
    myservo.attach(servoPin);

    // Motor Pins
    pinMode(enA, OUTPUT); pinMode(in1, OUTPUT); pinMode(in2, OUTPUT);
    pinMode(enB, OUTPUT); pinMode(in3, OUTPUT); pinMode(in4, OUTPUT);

    // Ultrasonic Pins
    pinMode(frontTrig, OUTPUT); pinMode(frontEcho, INPUT);
    pinMode(leftTrig, OUTPUT); pinMode(leftEcho, INPUT);
    pinMode(rightTrig, OUTPUT); pinMode(rightEcho, INPUT);
}

void loop() {
    if (Serial.available() > 0) {
        received = Serial.read();
        Serial.println(received);
        processBluetooth(received);
    }

    if (carRunning) {
        // Update sensor readings
        cmFront = getUltrasonicDistance(frontTrig, frontEcho);
        cmLeft = getUltrasonicDistance(leftTrig, leftEcho);
        cmRight = getUltrasonicDistance(rightTrig, rightEcho);

        Serial.print("Front: "); Serial.print(cmFront); Serial.print(" cm, ");
        Serial.print("Left: "); Serial.print(cmLeft); Serial.print(" cm, ");
        Serial.print("Right: "); Serial.print(cmRight); Serial.println(" cm");

        // Obstacle avoidance logic
       if (cmFront <= 30 && cmFront > 0) {
//            stopMotors();
            if (cmLeft > cmRight) {
                turnLeft();
            } else {
                turnRight();
            }
        } else if (cmLeft <= 30 && cmLeft > 0) {
            turnRight();
        } else if (cmRight <= 30 && cmRight > 0) {
            turnLeft();
        } else {
            moveForward();
        }
    } else {
        stopMotors();
    }
}


// --- Functions ---

void processBluetooth(char sign) {
    switch (sign) {
        case 'S': // Start car
            carRunning = true;
            myservo.write(90);
            analogWrite(red, 0); analogWrite(green, 255); analogWrite(blue, 0);
            break;
        case 'N': // Stop car
            carRunning = false;
            myservo.write(45);
            analogWrite(red, 255); analogWrite(green, 0); analogWrite(blue, 0);
            break;
        default:
            break;
    }
}

long getUltrasonicDistance(int trigPin, int echoPin) {
    digitalWrite(trigPin, LOW); delayMicroseconds(2);
    digitalWrite(trigPin, HIGH); delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    return (pulseIn(echoPin, HIGH) * 0.034) / 2;
}

void moveForward() {
    Serial.println("Moving Forward");
    digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
    analogWrite(enA, 191);
    digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
    analogWrite(enB, 138);
}

void stopMotors() {
    Serial.println("Stopping Motors");
    digitalWrite(in1, LOW); digitalWrite(in2, LOW);
    analogWrite(enA, 0);
    digitalWrite(in3, LOW); digitalWrite(in4, LOW);
    analogWrite(enB, 0);
}

void turnRight() {
    Serial.println("Turning Right");
    digitalWrite(in1, LOW); digitalWrite(in2, HIGH);
    analogWrite(enA, 191);
    digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
    analogWrite(enB, 0);
    delay(180);
}

void turnLeft() {
    Serial.println("Turning Left");
    digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
    analogWrite(enA, 0);
    digitalWrite(in3, LOW); digitalWrite(in4, HIGH);
    analogWrite(enB, 138);
    delay(180);
}
