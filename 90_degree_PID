
// Motor A (Left Motor) - TivaC and L298N connections
int enA = 40;   // Enable pin (PF2) for Left Motor (PWM control)
int in1 = 12;   // IN1 pin (PA3) for Left Motor direction
int in2 = 11;   // IN2 pin (PA2) for Left Motor direction


// Motor B (Right Motor) - TivaC and L298N connections
int enB = 25;   // Enable pin (PD2) for Right Motor (PWM control)
int in3 = 13;   // IN3 pin (PA4) for Right Motor direction
int in4 = 8;    // IN4 pin (PA5) for Right Motor direction


void setup() {
    Serial.begin(115200); // Serial for debugging


    // Set motor control pins as OUTPUT
    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    
    pinMode(enB, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);


    // Move forward for 2 seconds
    moveForward();
    delay(2000);


    // Turn right
    turnRight();
}


void loop(){
}


// Function to move both motors forward
void moveForward() {
    Serial.println("Moving Forward");


    // Left Motor Forward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, 191);  // 75% Duty Cycle


    // Right Motor Forward
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enB, 71);  } %adjusted speed


// Function to turn right (stopping right motor, moving left motor forward)
void turnRight() {
    Serial.println("Turning Right");


    // Stop Right Motor
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    analogWrite(enB, 0);  // Stop right motor


    // Left Motor Forward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, 191);  // Maintain left motor speed


    delay(700);  // adjusted timing to fine-tune turn angle
}
