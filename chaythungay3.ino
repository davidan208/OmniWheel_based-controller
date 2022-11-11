#include <PID_v1.h>
#include <SoftwareSerial.h>

SoftwareSerial bluetooth(50,51);

// L298
#define PWM1 5
#define IN11 23
#define IN12 22

#define PWM2 6
#define IN21 27
#define IN22 26

#define PWM3 7
#define IN31 31
#define IN32 30

// Encoder
#define ENCA 2
#define ENCB A3

#define ENCA2 3
#define ENCB2 A4

#define ENCA3 18
#define ENCB3 A5

String tinhieu = "115";

#define PPR = 480

int v1, v2, v3;
float vtt = 150;  float vquay = 80;

double kp = 5, ki = 1, kd = 0.01;

volatile long encoderPos1;
volatile long encoderPos2;
volatile long encoderPos3;

unsigned long present = 0;
unsigned long previous = 0;

boolean dir1 = true;
boolean dir2 = true;
boolean dir3 = true;

double input1 = 0, output1 = 0, setpoint1 = 0;
PID myPID1(&input1, &output1, &setpoint1, kp, ki, kd, DIRECT);

double input2 = 0, output2 = 0, setpoint2 = 0;
PID myPID2(&input2, &output2, &setpoint2, kp, ki, kd, DIRECT);

double input3 = 0, output3 = 0, setpoint3 = 0;
PID myPID3(&input3, &output3, &setpoint3, kp, ki, kd, DIRECT);

void follow_angle(int goc_de)
{

  float goc = goc_de*PI/180.0;
  
  v1 = ((2.0/3) * cos(goc)) * vtt;
  v2 = ((-1.0/3) * cos(goc) + (sqrt(3)/3.0) * sin(goc)) * vtt;
  v3 = ((-1.0/3) * cos(goc) - (sqrt(3)/3.0) * sin(goc)) * vtt;

  
//  analogWrite(PWM1, abs(v1));
//  analogWrite(PWM2, abs(v2));
//  analogWrite(PWM3, abs(v3));

//  Serial.print("Bánh 1: "); Serial.print(vtt*abs(v1));  Serial.print(" ");
//  Serial.print("Bánh 2: "); Serial.print(vtt*abs(v2));  Serial.print(" ");
//  Serial.print("Bánh 3: "); Serial.println(vtt*abs(v3));
  
  
  if (v1 < 0) dir1 = false;
  else if (v1 >=0) dir1 = true;
  v1 = abs(v1);
  
  if (v2 < 0) dir2 = false;
  else if (v2 >=0) dir2 = true;
  v2 = abs(v2);
  
  if (v3 < 0) dir3 = false;
  else if (v3 >=0) dir3 = true;
  v3 = abs(v3);
  
  if (dir1 == true) 
  {
    digitalWrite(IN11, HIGH);
    digitalWrite(IN12, LOW);
  }
  else if (dir1 == false)
  {
    digitalWrite(IN11, LOW);
    digitalWrite(IN12, HIGH);
  }

  if (dir2 == true) 
  {
    digitalWrite(IN21, HIGH);
    digitalWrite(IN22, LOW);
  }
  else if (dir2 == false)
  {
    digitalWrite(IN21, LOW);
    digitalWrite(IN22, HIGH);
  }

  if (dir3 == true) 
  {
    digitalWrite(IN31, HIGH);
    digitalWrite(IN32, LOW);
  }
  else if (dir1 == false)
  {
    digitalWrite(IN31, LOW);
    digitalWrite(IN32, HIGH);
  }
}

void turn_CW()
{
  analogWrite(PWM1, output1);
  analogWrite(PWM2, output2);
  analogWrite(PWM3, output3);

  digitalWrite(IN11, HIGH); digitalWrite(IN12, LOW);
  digitalWrite(IN21, HIGH); digitalWrite(IN22, LOW);
  digitalWrite(IN31, HIGH); digitalWrite(IN32, LOW);
}

void turn_CCW()
{
  analogWrite(PWM1, output1);
  analogWrite(PWM2, output2);
  analogWrite(PWM3, output3);

  digitalWrite(IN12, HIGH); digitalWrite(IN11, LOW);
  digitalWrite(IN22, HIGH); digitalWrite(IN21, LOW);
  digitalWrite(IN32, HIGH); digitalWrite(IN31, LOW);
}

void pause()
{
  analogWrite(PWM1, 0);
  analogWrite(PWM2, 0);
  analogWrite(PWM3, 0);

  digitalWrite(IN11, LOW); digitalWrite(IN12, LOW);
  digitalWrite(IN21, LOW); digitalWrite(IN22, LOW);
  digitalWrite(IN31, LOW); digitalWrite(IN32, LOW);
}

void setup() {
  pinMode(ENCA, INPUT_PULLUP);
  pinMode(ENCB, INPUT_PULLUP);

  pinMode(ENCA2, INPUT_PULLUP);
  pinMode(ENCB2, INPUT_PULLUP);

  pinMode(ENCA3, INPUT_PULLUP);
  pinMode(ENCB3, INPUT_PULLUP);

  pinMode(PWM1, OUTPUT);
  pinMode(IN11, OUTPUT);
  pinMode(IN12, OUTPUT);
  
  pinMode(PWM2, OUTPUT);
  pinMode(IN21, OUTPUT);
  pinMode(IN22, OUTPUT);
  
  pinMode(PWM3, OUTPUT);
  pinMode(IN31, OUTPUT);
  pinMode(IN32, OUTPUT);

  attachInterrupt(0, encoder1, FALLING);
  attachInterrupt(0, encoder2, FALLING);
  attachInterrupt(0, encoder3, FALLING);

  TCCR1B = TCCR1B & 0b11111000 | B00000001;

  myPID1.SetMode(AUTOMATIC);
  myPID1.SetSampleTime(1);
  myPID1.SetOutputLimits(-255,255);

  myPID2.SetMode(AUTOMATIC);
  myPID2.SetSampleTime(1);
  myPID2.SetOutputLimits(-255,255);

  myPID3.SetMode(AUTOMATIC);
  myPID3.SetSampleTime(1);
  myPID3.SetOutputLimits(-255,255);

  Serial.begin(9600);
  Serial.setTimeout(10000);
  bluetooth.begin(9600); 
}

void hinhvuong()
{
  present = millis();
  if (present - previous < 1000) follow_angle(0);
  else if ((present - previous >= 1000) and (present - previous < 2000)) follow_angle(90);
  else if ((present - previous >= 2000) and (present - previous < 3000)) follow_angle(180);
  else if ((present - previous >= 3000) and (present - previous < 4000)) follow_angle(270);
  else previous = present;
}

void hinhtamgiac()
{
  present = millis(); 
  if (present - previous < 1000) follow_angle(0);
  else if ((present - previous >= 1000) and (present - previous < 2000)) follow_angle(120);
  else if ((present - previous >= 2000) and (present - previous < 3000)) follow_angle(240);
  else previous = present;
}


void loop() {
  // put your main code here, to run repeatedly:
  if (bluetooth.available() > 0) tinhieu = bluetooth.read();
//  Serial.println(tinhieu);
  if (tinhieu == "115")  {pause();  previous = millis();}
  // TINH TIEN
  else if (tinhieu == "119") 
  {
    follow_angle(90);
    
    setpoint1 = v1;
    input1 = encoderPos1;
    myPID1.Compute();

    setpoint2 = v2;
    input2 = encoderPos2;
    myPID2.Compute();
    
    setpoint3 = v3;
    input3 = encoderPos3;
    myPID3.Compute();

    Serial.print(output1);  Serial.print(" ");  Serial.print(output2);  Serial.print(" ");  Serial.println(output3);

    analogWrite(PWM1, output1);
    analogWrite(PWM2, output2);
    analogWrite(PWM3, output3);
  }
  else if (tinhieu == "97")  
  {
    follow_angle(180);
    
    setpoint1 = v1;
    input1 = encoderPos1;
    myPID1.Compute();

    setpoint2 = v2;
    input2 = encoderPos2;
    myPID2.Compute();
    
    setpoint3 = v3;
    input3 = encoderPos3;
    myPID3.Compute();

    Serial.print(output1);  Serial.print(" ");  Serial.print(output2);  Serial.print(" ");  Serial.println(output3);
    
    analogWrite(PWM1, output1);
    analogWrite(PWM2, output2);
    analogWrite(PWM3, output3);
  }
  else if (tinhieu == "100") 
  {
    follow_angle(0);

    setpoint1 = v1;
    input1 = encoderPos1;
    myPID1.Compute();

    setpoint2 = v2;
    input2 = encoderPos2;
    myPID2.Compute();
    
    setpoint3 = v3;
    input3 = encoderPos3;
    myPID3.Compute();

    Serial.print(output1);  Serial.print(" ");  Serial.print(output2);  Serial.print(" ");  Serial.println(output3);

    analogWrite(PWM1, output1);
    analogWrite(PWM2, output2);
    analogWrite(PWM3, output3);
  }
  else if (tinhieu == "120") 
  {
    follow_angle(270);

    setpoint1 = v1;
    input1 = encoderPos1;
    myPID1.Compute();

    setpoint2 = v2;
    input2 = encoderPos2;
    myPID2.Compute();
    
    setpoint3 = v3;
    input3 = encoderPos3;
    myPID3.Compute();

    Serial.print(output1);  Serial.print(" ");  Serial.print(output2);  Serial.print(" ");  Serial.println(output3);

    analogWrite(PWM1, output1);
    analogWrite(PWM2, output2);
    analogWrite(PWM3, output3);
  }

  else if (tinhieu == "122") 
  {
    follow_angle(240);

    setpoint1 = v1;
    input1 = encoderPos1;
    myPID1.Compute();

    setpoint2 = v2;
    input2 = encoderPos2;
    myPID2.Compute();
    
    setpoint3 = v3;
    input3 = encoderPos3;
    myPID3.Compute();

    Serial.print(output1);  Serial.print(" ");  Serial.print(output2);  Serial.print(" ");  Serial.println(output3);

    analogWrite(PWM1, output1);
    analogWrite(PWM2, output2);
    analogWrite(PWM3, output3);
  }
  else if (tinhieu == "101") 
  {
    follow_angle(30);

    setpoint1 = v1;
    input1 = encoderPos1;
    myPID1.Compute();

    setpoint2 = v2;
    input2 = encoderPos2;
    myPID2.Compute();
    
    setpoint3 = v3;
    input3 = encoderPos3;
    myPID3.Compute();

    Serial.print(output1);  Serial.print(" ");  Serial.print(output2);  Serial.print(" ");  Serial.println(output3);

    analogWrite(PWM1, output1);
    analogWrite(PWM2, output2);
    analogWrite(PWM3, output3);
  }

  else if (tinhieu == "99")  
  {
    follow_angle(330);
    
    setpoint1 = v1;
    input1 = encoderPos1;
    myPID1.Compute();

    setpoint2 = v2;
    input2 = encoderPos2;
    myPID2.Compute();
    
    setpoint3 = v3;
    input3 = encoderPos3;
    myPID3.Compute();

    Serial.print(output1);  Serial.print(" ");  Serial.print(output2);  Serial.print(" ");  Serial.println(output3);

    analogWrite(PWM1, output1);
    analogWrite(PWM2, output2);
    analogWrite(PWM3, output3);
  }
  else if (tinhieu == "113") 
  {
    follow_angle(150);
    
    setpoint1 = v1;
    input1 = encoderPos1;
    myPID1.Compute();

    setpoint2 = v2;
    input2 = encoderPos2;
    myPID2.Compute();
    
    setpoint3 = v3;
    input3 = encoderPos3;
    myPID3.Compute();

    Serial.print(output1);  Serial.print(" ");  Serial.print(output2);  Serial.print(" ");  Serial.println(output3);

    analogWrite(PWM1, output1);
    analogWrite(PWM2, output2);
    analogWrite(PWM3, output3);
  }
  // XOAY TAI CHO
  else if (tinhieu == "49")  
  {  
    setpoint1 = vquay;
    input1 = encoderPos1;
    myPID1.Compute();

    setpoint2 = vquay;
    input2 = encoderPos2;
    myPID2.Compute();
    
    setpoint3 = vquay;
    input3 = encoderPos3;
    myPID3.Compute();

    turn_CW();
  }
  else if (tinhieu == "50")  
  {
    setpoint1 = vquay;
    input1 = encoderPos1;
    myPID1.Compute();

    setpoint2 = vquay;
    input2 = encoderPos2;
    myPID2.Compute();
    
    setpoint3 = vquay;
    input3 = encoderPos3;
    myPID3.Compute();

    turn_CCW();
  }
}

void encoder1()
{
  if (digitalRead(A3) == HIGH) encoderPos1++;
  else encoderPos1--;
}

void encoder2()
{
  if (digitalRead(A4) == HIGH) encoderPos2++;
  else encoderPos2--;
}

void encoder3()
{
  if (digitalRead(A5) == HIGH) encoderPos3++;
  else encoderPos3--;
}
