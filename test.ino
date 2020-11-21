#include <Servo.h>
#include <stdlib.h>

Servo myservo;  // 定义Servo对象来控制

/*------------------引脚说明-------------------------*/
/*-------------电机引脚       5----------------------*/
/*-------------蜂鸣器引脚     6----------------------*/
/*-------------舵机引脚       7----------------------*/
/*-------------前 左前 右前   22 23 24---------------*/
/*-------------后 左后 右后   34 35 36---------------*/
/*-------------左 右         26 27------------------*/
/*-------------电机变量       5----------------------*/

#define motor       5
#define buzzer      6
#define seRvo       7
#define F           22
#define LF          23
#define RF          24
#define L           26
#define R           27
#define B           34
#define LB          35
#define RB          36


int   isData[8]   =  {0}   ;//红外数据
char  isData_F[6] =  {'\0'};//前进字符数据
char  isData_B[6] =  {'\0'};//后退字符数据
int   value       =  0     ;//变量
int   stPin       =  22    ;//起始红外Pin
int   fwSpeed     =  0     ;//前进速度
int   bkSpeed     =  0     ;//后退速度
bool  choose      =  false ;//模式选择开关
bool  startSwitch =  false ;//启动开关
int   mAngle      =  0     ; // 角度存储变量


void setup() {
  myservo.attach(seRvo);  // 设置引脚状态与波特率
  pinMode(buzzer, OUTPUT);
  pinMode(motor , OUTPUT);
  pinMode(mAngle, OUTPUT);
  pinMode(F     , INPUT );
  pinMode(LF    , INPUT );
  pinMode(RF    , INPUT );
  pinMode(L     , INPUT );
  pinMode(F     , INPUT );
  pinMode(B     , INPUT );
  pinMode(LB    , INPUT );
  pinMode(RB    , INPUT );
  Serial.begin(9600);
}

void loop() {
  int commend = 0;
  if(startSwitch){                            //启动开关
    runCar(fwSpeed);
  }
        for(int j = 0;j < 8;j++){                   //红外读值
          value = !digitalRead(stPin);
          isData[j]=value;
          if(stPin == 24){
            stPin = 26;
          }
          else if(stPin ==27){
            stPin = 34;
          }
          else{
          stPin++;
          }
        }
        for(int j = 0;j < 5;j++){
          //sprintf(isData_F, "%d", isData[j]);
          //strcat(stm, isData_F);
          //strcat(stm," ");
          isData_F[j] = (char)(isData[j]+48);
          isData_B[j] = (char)(isData[j+3]+48);
        }
        stPin = 22;                                 //遍历红外读出
        for(int j = 0;j < 8;j++){                 //串口检验
          Serial.print(isData[j]);
        }
            Serial.print('\n');
        for(int i = 0;i < 5;i++){
            Serial.print(isData_F[i]);
          }
          Serial.print('\n');
        for(int i = 0;i < 5;i++){
           Serial.print(isData_B[i]);
          }
        Serial.print('\n');
        commend = isResult_F(isData_F);
        Serial.println(commend);
        Serial.print('\n');
        delay(100);
}


//前进模式
void runCar(int fwSpeed){           
   analogWrite(motor, fwSpeed);
   delay(500);
}


//转向
void turnCar(int Speed,int comme){
   int pos = 0;            
   myservo.attach(seRvo);
    if(comme == 0){
      if(pos < 90){
        for (; pos <= 90; pos ++) { // 0°到180°
          myservo.write(pos);              // 舵机角度写入
          delay(10);                       // 等待转动到指定角度
          }
         pos = 90;
         myservo.detach();
        }
      else if(pos > 90){
        for (; pos >= 90; pos --) { // 0°到180°
          myservo.write(pos);              // 舵机角度写入
          delay(10);                       // 等待转动到指定角度
          }
         pos = 90;
         myservo.detach();
      }
    }
      if(comme == 1){
        if(pos<45){
        for (; pos <= 45; pos ++) { // 0°到180°
          myservo.write(pos);              // 舵机角度写入
          delay(10);                       // 等待转动到指定角度
          }
         myservo.detach();
         pos = 45;
        }
        else if(pos >45){
          for (; pos >= 45; pos --) { // 0°到180°
            myservo.write(pos);              // 舵机角度写入
            delay(10);                       // 等待转动到指定角度
            }
         myservo.detach();
         pos = 45;
        }
      }
    else if(comme == 2){
    }
    else if(comme == 3){
    }
    else if(comme == 4){
    }
    else if(comme == 5){
    }
    else if(comme == 6){
    }
    else if(comme == 7){
    }
    else if(comme == 8){
    }
    else{
    }
}


//倒车模式
void backCar(int bkSpeed){          
  analogWrite(motor, bkSpeed);
  delay(500);
}


//红外光电结果
//直行 0
//微左 1
//微右 2
//中左 3
//中右 4
//大左 5
//大右 6
//极左 7
//极右 8
//停止-1
int isResult_F(char isR[6]){                              
    int comme = -1;
    myservo.attach(seRvo);
    if(!strcmp(isR,"00000")){
      comme = 0;
    }
    else if(!strcmp(isR,"01000")){
      comme = 1;
    }
    else if(!strcmp(isR,"00010")){
      comme = 2;
    }
    else if(!strcmp(isR,"00100")){
      comme = 3;
    }
    else if(!strcmp(isR,"00001")){
      comme = 4;
    }
    else if(!strcmp(isR,"11000")){
      comme = 5;
    }
    else if(!strcmp(isR,"10010")){
      comme = 6;
    }
    else if(!strcmp(isR,"11100")){
      comme = 7;
    }
    else if(!strcmp(isR,"10011")){
      comme = 8;
    }
    else{
      comme = -1;
    }
  return comme;
}

void isResult_B(){
  int commend = 0;
  return commend;
}


 //模式选择
void modelChoose(int choose){                
  int flag = -1;
  if(choose){
    fwSpeed = 0;
    bkSpeed = 0;
  }
  else{
    fwSpeed = 0;
    bkSpeed = 0;
  }
  return flag;
}
