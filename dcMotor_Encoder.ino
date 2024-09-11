#define enA 5
#define in1 6
#define in2 7

const int encoderPinA = 2;
const int encoderPinB = 3;

boolean buttonState = LOW;
int rotDirection = 0;
int pressed = false;

volatile int encoderPosition = 0;  // Tracks the encoder's position
int lastReportedPosition = 0;      // Last position reported to the serial monitor
boolean rotating = false;          // Flag to track rotation

void doEncoderA() {
  rotating = true;  // Set rotating flag to true
  // Check direction by reading pin B
  if (digitalRead(encoderPinA) == digitalRead(encoderPinB)) {
    encoderPosition++;  // Clockwise rotation
  } else {
    encoderPosition--;  // Counterclockwise rotation
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(enA,OUTPUT);
  pinMode(in1,OUTPUT);  // Set as OUTPUT to control motor direction
  pinMode(in2,OUTPUT);  // Set as OUTPUT to control motor direction

  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  Serial.begin(9600);

  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);

  // Use internal pull-up resistors if necessary
  digitalWrite(encoderPinA, HIGH);
  digitalWrite(encoderPinB, HIGH);

  // Attach interrupt to encoder pin A
  attachInterrupt(digitalPinToInterrupt(encoderPinA), doEncoderA, CHANGE);
}

void loop() {
  if (rotating) {
    // Only print if the position has changed
    if (lastReportedPosition != encoderPosition) {
      Serial.print("Position: ");
      Serial.println(encoderPosition);
      lastReportedPosition = encoderPosition;
    }
    rotating = false;  // Reset the rotating flag
  }
  
  // Constrain the encoder position to a reasonable range
  encoderPosition = constrain(encoderPosition, -600, 600);
  
  // Map the encoder position to a PWM value (0 to 255)
  int motorSpeed = map(abs(encoderPosition), 0, 600, 0, 255);
  
  // Set motor speed
  analogWrite(enA, motorSpeed);
  
  // Control motor direction based on encoder direction
  if (encoderPosition >= 0) {
    digitalWrite(in1, HIGH);  // Forward
    digitalWrite(in2, LOW);
  } else {
    digitalWrite(in1, LOW);   // Reverse
    digitalWrite(in2, HIGH);
  }
}
