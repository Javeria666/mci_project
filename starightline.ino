//motor A (Left Motor) - TivaC and L298N connections
int enA = 40;   // Enable pin (PF2) for Left Motor (PWM control)
int in1 = 12;   // IN1 pin (PA3) for Left Motor direction
int in2 = 11;   // IN2 pin (PA2) for Left Motor direction

//motor B (Right Motor) - TivaC and L298N connections
int enB = 25;   // Enable pin (PD2) for Right Motor (PWM control)
int in3 = 13;   // IN3 pin (PA4) for Right Motor direction
int in4 = 8;    // IN4 pin (PA5) for Right Motor direction
//
void setup() {
    Serial.begin(115200); // Serial for debugging

    // Set motor control pins as OUTPUT
    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    
    pinMode(enB, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);

    // Move forward at 50% speed
    moveForward();
}

void loop(){
}

 //Function to move both motors forward at 50% speed
void moveForward()  {
    Serial.println("Moving Forward at 50% speed");

    // Left Motor Forward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, 80);  // 50% Duty Cycle

    // Right Motor Forward
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enB, 80);  // 50% Duty Cycle
}

