#include <Wire.h>        //调用IIC库函数
#include "MH_TCS34725.h" //调用颜色识别传感器库函数
#define qianServoPin 12
#define houServoPin 4
#define zhongServoPin 3
#define tuopanServoPin 8

#define LH 10     //左电机正转负极引脚
#define LL 9   //左电机正转正极引脚
#define RH 5    //右电机正转负极引脚
#define RL 6     //右电机正转正极引脚
#define upHW 7    //上方红外
#define forwardHW A2    //前方红外
#define flankHW 11  //侧方红外
#define LW A3    //左灰度传感器引脚
#define RW A0   //中白标传感器引脚

#define LM 100       //左白标区别值
#define RM 100       //右白标区别值
int pos=0 ;
int h=0;

//颜色传感器不同通道值设置
MH_TCS34725 tcs = MH_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X); //设置颜色传感器采样周期50毫秒
enum{Forward=1,Back,Left,Right,Stop};//定义小车状态

void setup() 
{
  Serial.begin(115200);  //开启串口，并设置串口波特率位115200
  Serial.println("Color View Test!"); //串口打印：Color View Test!
  //检测是否有颜色传感器模块
  if (tcs.begin()) {                 //如果检测到颜色传感器模块
    Serial.println("IIC颜色传感器已连接");  //串口打印 Found sensor
  } else {                           //如果没有检测到颜色传感器模块
    Serial.println("IIC颜色传感器未连接");//串口打印：没有找到颜色识别传感器模块
    while (1); // halt! //程序陷入死循环
  }
 // Motor_pin_init();//直流电机引脚初始化
 
  houServo(0);delay(500);
  pinMode(RL, OUTPUT);
  pinMode(RH, OUTPUT);
  pinMode(LL, OUTPUT);
  pinMode(LH, OUTPUT);
  pinMode(LW, INPUT);
  pinMode(RW, INPUT);
  pinMode(houServoPin,OUTPUT);
  digitalWrite(houServoPin,LOW);
  pinMode(zhongServoPin,OUTPUT);
  digitalWrite(zhongServoPin,LOW);
  pinMode(tuopanServoPin,OUTPUT);
  digitalWrite(tuopanServoPin,LOW);delay(1000);
  zhongServo(30);delay(1000);
  tuopanServo(0); delay(1000);
  
  advance();delay(1500);    //******过斜坡
  upramp_advance();delay(2500);
  downramp_advance();delay(1200);
  stoping();delay(500);     //******过完斜坡
  pinMode(qianServoPin,OUTPUT);
  digitalWrite(qianServoPin,LOW);
  qianServo(27);delay(1000);
}


void loop() {
  twoservo();
//  if(digitalRead(upHW)==1&&digitalRead(flankHW)==0)
//  {    
//    stoping();delay(500);
//    if(Get_Color_Data()=='N')
//     {
//        advance();delay(500);   
//      }
//    else
//     {
//       stoping();  
//       card_danzu();delay(1000);
//       advance();delay(1000);
//     }
//  }
//  else if(digitalRead(forwardHW) == 0)
//  {
//    stoping();
//    delay(500);
//     jieti();
//  }
//  else  if( analogRead(LW) > LM && analogRead(RW) < RM  )
//  {
//    turnLeft();
//  }
//  else if( analogRead(LW) < LM && analogRead(RW) > RM  )
//  {
//    turnRight();
//  }
//  else advance(); 

}
