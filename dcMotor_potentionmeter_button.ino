
#define enA 2
#define in1 3
#define in2 4
#define button 7

boolean buttonState = LOW;
int rotDirection = 0;
int pressed = false;


void setup() {
  // put your setup code here, to run once:
  pinMode(enA,OUTPUT);
  pinMode(in1,INPUT);
  pinMode(in2,INPUT);
  pinMode(button,INPUT);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int potValue = analogRead(A0);
  //Serial.print("potentionmeter value: ");
  //Serial.println(potValue);
  int pwmOutput = map(potValue,0,1023,0,255);
  analogWrite(enA,pwmOutput);
  //Serial.println(pressed);  
  if(digitalRead(button)==true){
    pressed = !pressed;
    Serial.print("Button: ");
    Serial.println(pressed);
  }
  Serial.println(pressed);
  delay(20);

  if(pressed == 0 & rotDirection ==0){
    Serial.println("node1 ");
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    rotDirection = 1;
    delay(20);
  }

  if(pressed == 1 & rotDirection ==1){
    Serial.println("Direction Changed ");
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    rotDirection = 0;
    delay(20);
  }
  delay(500);
}
