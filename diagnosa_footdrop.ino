#include <Wire.h>
#include "MPU6050_light.h"
MPU6050 mpu1(Wire);
MPU6050 mpu2(Wire);
unsigned long timer = 0;

#define TCAADR 0x70
void tcaselect (uint8_t i){
  if (i > 7) return;

  Wire.beginTransmission(TCAADR);
  Wire.write(1<<i);
  Wire.endTransmission();
}

const int TOE = 3;
const int HEEL = 2;
int heel;
int toe;

String fase_gait;
float AnklePos;
float gyro1;
float gyro2;
int positive;
int negative;
float percentage;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  tcaselect(0);
  inisialisasi1();
  tcaselect(1);
  inisialisasi2();
  pinMode(TOE, INPUT);
  pinMode(HEEL, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  toe = digitalRead(TOE);
  heel = digitalRead(HEEL);

  tcaselect(0);
  mpu1.update();
  if((millis()-timer)>1){
    gyro1 = mpu1.getAngleZ();
    timer = millis();
  }
  tcaselect(1);
  mpu2.update();
  if((millis()-timer)>1){
    gyro2 = mpu2.getAngleZ();
    timer = millis();
  }

  AnklePos = gyro2 - gyro1;

  if((toe==0)&&(heel==0)){
    counter();
    fase_gait = "P4";
  }
  else if((toe==0)&&(heel==1)){
    percentage = (negative/(positive+negative))*100;
    fase_gait = "P1";
  }
  else if((toe==1)&&(heel==1)){
    negative = 0;
    positive = 0;
    fase_gait = "P2";
  }
  Serial.print("Fase Gait: ");
  Serial.print(fase_gait);
  Serial.print(" Gyro 1: ");
  Serial.print(gyro1);
  Serial.print(" Gyro 2: ");
  Serial.print(gyro2);
  Serial.print(" Ankle position: ");
  Serial.print(AnklePos);
  Serial.print(" Percentage: ");
  Serial.print(percentage);
  Serial.print(" Positive: ");
  Serial.print(positive);
  Serial.print(" Negative: ");
  Serial.println(negative);
}

void inisialisasi1(){
 byte status = mpu1.begin();
    Serial.print(F("MPU6050 status: "));
    Serial.println(status);
    while(status!=0){ } // stop everything if could not connect to MPU6050
    
    Serial.println(F("Calculating offsets, do not move MPU6050"));
    delay(1000);
    // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
    mpu1.calcOffsets(); // gyro and accelero
    Serial.println("Done!\n");
 
}

void inisialisasi2(){
 byte status = mpu2.begin();
    Serial.print(F("MPU6050 status: "));
    Serial.println(status);
    while(status!=0){ } // stop everything if could not connect to MPU6050
    
    Serial.println(F("Calculating offsets, do not move MPU6050"));
    delay(1000);
    mpu2.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
    mpu2.calcOffsets(); // gyro and accelero
    Serial.println("Done!\n");
 
}

void counter(){
  if(AnklePos>0){
    positive = positive + 1;
  }
  else if(AnklePos<0){
    negative = negative + 1;
  }
}
