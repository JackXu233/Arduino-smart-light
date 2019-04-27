// demo of Starter Kit V2.0
#include <Arduino.h>
#include <math.h>
#include <ld3320.h>
#include <EEPROM.h>


const int potentiometer = A0;                    // rotary angle sensor connect to A0
const int pinLight = A1;
const int button = 7;
const int soft = 5;
const int hard = 6;
const double pi =3.14159265358;
int flag = 0;
int readdd=0;
VoiceRecognition Voice;                         //声明一个语音识别对象
#define Led 8  
double light=0;
double bright=0;
double color=0;
double softv=0;
double hardv=0;
void setup()
{
    Serial.begin(9600);                         // set the serial communication frequency at 9600 bits per sec
    pinMode(potentiometer, INPUT);
    pinMode(pinLight,INPUT);
    pinMode(button,INPUT);
    pinMode(soft,OUTPUT);
    pinMode(hard,OUTPUT);
    pinMode(Led,OUTPUT);                        //初始化LED引脚为输出模式
    digitalWrite(Led,LOW);                      //LED引脚低电平
     
    Voice.init();                               //初始化VoiceRecognition模块  
    Voice.addCommand("kai deng",0);             //添加指令，参数（指令内容，指令标签（可重复））
    Voice.addCommand("guan deng",1);            //添加指令，参数（指令内容，指令标签（可重复））
    Voice.addCommand("bian liang",2);
    Voice.addCommand("liang yi dian",2);
    Voice.addCommand("zai liang yi dian",2);
    Voice.addCommand("bian an",3);
    Voice.addCommand("an yi dian",3);
    Voice.addCommand("zai an yi dian",3);
    Voice.addCommand("zui liang",4);
    Voice.start();//开始识别

}

void loop()
{
    color = analogRead(potentiometer);
    light = analogRead(pinLight);
    readdd=EEPROM.read(0);
    delay(100);
    switch(Voice.read())                          //判断识别
  {
    case 0:                                     //若是指令“kai deng”
    if(readdd==0)readdd=127;
    bright=readdd;                //点亮LED
        flag=0;
        break;
    case 1:                                     //若是指令“guan deng”
    bright=0;//熄灭LED
        flag=0;
        break;  
    case 2:
    readdd+=32;
    if(readdd>=255)readdd=255;
    bright=readdd;
    flag=0;
    break;
    case 3:
    readdd-=32;
    if(readdd<=0)readdd=0;
    bright=readdd;
    flag=0;
    break;
    case 4:
    softv=255;
    hardv=255;
    readdd=255;
    bright=readdd;
    flag=1;
    break;
    default:
        break;
  }
  
  if(bright>=255)bright=255;
  if(bright<=0)bright=0;
  if(flag==0){
  softv=bright*sin(color/1024*pi/2);
  hardv=bright*cos(color/1024*pi/2);}
  analogWrite(soft,softv);
  analogWrite(hard,hardv);
  EEPROM.write(0,readdd);
  

    
    
   // if(digitalRead(button)!=0){
   //   flag=1;
   // }else{
   //   flag=0;
   // }
   // if(flag==0){
   //   analogWrite(soft,value);
   // }else{
   //   analogWrite(hard,value);
   // }
   Serial.println(readdd);                      // pirnt the value on the serial monitor screen
   delay(100);                                  // wait 100ms before printing next value
}
