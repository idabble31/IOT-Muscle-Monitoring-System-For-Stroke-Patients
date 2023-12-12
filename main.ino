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

const int EMGPin = A1;
const int TOE = 3;
int toe;
const int HEEL = 2;
int heel;

int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState_TOE = 0;         // current state of the button
int buttonState_HEEL = 0;
int lastButtonState_HEEL=0;
int lastButtonState_TOE = 0;     // previous state of the button

int point;
int point_arr[4];
int score;
int i;
int u;
int a1;
int a2;
int EMGVal = 0;
//int button_state;
String fase_gait;
String status_otot;
String ketepatan;
String diagnosa;
float AnklePos;
float gyro1;
float gyro2;
float positive;
float negative;
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
  EMGVal = analogRead(EMGPin);
  //button_state = (toe==1)||(heel==1);
  buttonState_TOE = toe;
  buttonState_HEEL = heel;

  // compare the buttonState to its previous state
  if ((buttonState_TOE != lastButtonState_TOE)||(buttonState_HEEL != lastButtonState_HEEL)) {
    // if the state has changed, increment the counter
    if ((buttonState_TOE == HIGH)||(buttonState_HEEL == HIGH)) {
      // if the current state is HIGH then the button went from off to on:
      buttonPushCounter++;

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

  if(EMGVal==0){
    status_otot = "Inactive";
  }
  else{
    status_otot = "Active";
  }

      if ((heel==1)&&(toe==0)){
    //Serial.print("P1");
    percentage = (negative/(positive+negative))*100;
    fase_gait = "P1";
    point = 1;
    //button_state=0;
  }
      else if((heel==1)&&(toe==1)){
        //Serial.print("P2");
        negative = 0;
        positive = 0;
        fase_gait = "P2";
        point = 2;
        //button_state=0;
      }
      else if((heel==0)&&(toe==1)){
        //Serial.print("P3");
        fase_gait = "P3";
        point = 3;
    //button_state=0;
    }
    }
    else if((buttonState_TOE==LOW)&&(buttonState_HEEL==LOW)){
      counter();
      fase_gait = "P4";
      point = 4;
    }
    //mengisi array point
    a2 = point;
    score=a2-a1;
    a1=a2;

    if((score==1)||(score==0)||(score==-3)){
      
    Serial.print("OK");
    Serial.print(";");
    }

    else{
      Serial.print("NOT OK");
      Serial.print(";");
      u=u+1;
    }
    Serial.print("u= ");
    Serial.println(u);

    if(((fase_gait == "P2")||(fase_gait=="P4"))&&(status_otot=="Active")){
    ketepatan = "Tepat";
  }
  else{
    ketepatan = ("Tidak tepat");
  }
  Serial.print(" Ketepatan: ");
  Serial.print(ketepatan);
  Serial.print(" Fase Gait: ");
  Serial.print(fase_gait);
  Serial.print(" EMG Value: ");
  Serial.print(EMGVal);
  Serial.print(" Status otot: ");
  Serial.print(status_otot);
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
  Serial.print(" Button pushed: ");
  Serial.print(buttonPushCounter);

  if(buttonPushCounter==9){
    //Foot drop?
    if(percentage>20){
      diagnosa = "Pasien mengalami footdrop. Alat bantu tidak terpasang.";
    }
    else{
      //Gait phase berurutan?
      if(u<=10){
        //EMG Aktif secara tepat?
        if(ketepatan=="Tepat"){
          diagnosa = "Gait berjalan pasien adalah baik. Lepas alat bantu dan ambil data kembali.";
        }
        else if(ketepatan=="Tidak tepat"){
          diagnosa = "Settingan alat bantu tidak tepat.";
        }
      }
      else if(u>0){
        //EMG aktif secara tepat?
        if(ketepatan=="Tepat"){
          diagnosa = "Gait berjalan pasien mulai pulih. Lepas alat bantu dan ambil data kembali.";
        }
        else if(ketepatan=="Tidak tepat"){
          diagnosa = "Settingan alat bantu tidak tepat.";
        }
      }
    }
  }
  else{
    diagnosa = "Collecting data...";
    delay(3000);
  }

  Serial.print(" Diagnosa: ");
  Serial.println(diagnosa);

    // Delay a little bit to avoid bouncing
    delay(50);
    lastButtonState_TOE = buttonState_TOE;
    lastButtonState_HEEL = buttonState_HEEL;
}
}
  // save the current state as the last state, for next time through the loop
  //lastButtonState_TOE = buttonState_TOE;
  //lastButtonState_HEEL = buttonState_HEEL;

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
