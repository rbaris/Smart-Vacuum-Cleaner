//HCSR-04
#define rightTrig 13
#define rightEcho 12
#define leftTrig 11
#define leftEcho 10
//L298N
#define rightEn 3
#define rightForward 4
#define rightReverse 5
#define leftEn 6
#define leftForward 7
#define leftReverse 8
//led
#define led 9

int minimumRange = 30;

void setup() {
    
    pinMode(rightEn,OUTPUT);
    pinMode(rightForward,OUTPUT);
    pinMode(rightReverse,OUTPUT);
    pinMode(leftEn,OUTPUT);
    pinMode(leftForward,OUTPUT);
    pinMode(leftReverse,OUTPUT);

    pinMode(rightTrig,OUTPUT);
    pinMode(rightEcho,INPUT);
    pinMode(leftTrig,OUTPUT);
    pinMode(leftEcho,INPUT);

    pinMode(led,OUTPUT);
    Serial.begin(9600);

}

void loop() {
  
  int LeftDistance = leftDistance();
  int RightDistance = rightDistance();

  digitalWrite(rightEn,150);
  digitalWrite(leftEn,150);
  
  Stop();
  delay(150);
  

  if(LeftDistance && RightDistance > minimumRange){

      goForward();
      delay(200);
  }
  else if(LeftDistance && RightDistance < minimumRange){
      if(LeftDistance<RightDistance){
        goReverse();
        delay(200);
        goRight();
        delay(200);
      }
      else if(LeftDistance>=RightDistance){
        goReverse();
        delay(200);
        goLeft();
        delay(200);
      }
  }
  else if(LeftDistance<minimumRange){
      goRight();
      delay(200);
  }
  else if(RightDistance<minimumRange){
      goLeft();
      delay(200);
  }
  else{
    goForward();
    delay(200);
  }
}

int leftDistance(void){
  
  long duration;
  int distance;

  digitalWrite(leftTrig,LOW);
  delayMicroseconds(2);
  digitalWrite(leftTrig,HIGH);
  delayMicroseconds(10);
  digitalWrite(leftTrig,LOW);

   duration = pulseIn(leftEcho,HIGH);

   distance= duration*0.034/2;
   
   return distance;
}

int rightDistance(void){

    long duration;
    int distance;

    digitalWrite(rightTrig,LOW);
    delayMicroseconds(2);
    digitalWrite(rightTrig,HIGH);
    delayMicroseconds(10);
    digitalWrite(rightTrig,LOW);

    duration = pulseIn(rightEcho,HIGH);
    distance= duration*0.034/2;

    return distance;
}

void RightMotorForward(){
  
 // Serial.println("Right Motor's going forward.");
  analogWrite(rightEn,100);
  digitalWrite(rightForward,HIGH);
  digitalWrite(rightReverse,LOW);

}
void LeftMotorForward(){

  //Serial.println("Left Motor's going forward.");
  analogWrite(leftEn,100);
  digitalWrite(leftForward,HIGH);
  digitalWrite(leftReverse,LOW);
  
}
void RightMotorReverse(){

  //Serial.println("Right Motor's going reverse.");
  analogWrite(rightEn,100);
  digitalWrite(rightForward,LOW);
  digitalWrite(rightReverse,HIGH);
  
}
void LeftMotorReverse(){

  //Serial.println("Left Motor's going reverse.");
  analogWrite(leftEn,100);
  digitalWrite(leftForward,LOW);
  digitalWrite(leftReverse,HIGH);
  
}
void Stop(){

  Serial.println("Both are stopped.");
  digitalWrite(rightForward,LOW);
  digitalWrite(rightReverse,LOW);
  digitalWrite(leftForward,LOW);
  digitalWrite(leftReverse,LOW);
  
}
void goForward(){

  Serial.println("Vacuum bot's going forward.");
  analogWrite(rightEn,100);
  analogWrite(leftEn,100);
  RightMotorForward();
  LeftMotorForward();

  digitalWrite(led,HIGH);
  delay(100);
  
}
void goLeft(){

  Serial.println("Vacuum bot's turning left.");
  analogWrite(rightEn,150);
  analogWrite(leftEn,100);
  RightMotorForward();
  LeftMotorReverse();
  
}
void goRight(){

  Serial.println("Vacuum bot's turning right.");
  analogWrite(rightEn,100);
  analogWrite(leftEn,150);
  RightMotorReverse();
  LeftMotorForward();
  
}
void goReverse(){

  Serial.println("Vacuum bot's going reverse.");
  analogWrite(rightEn,100);
  analogWrite(leftEn,100);
  LeftMotorReverse();
  RightMotorReverse();
  
}
