/*--------------------------------------------------------------------------
* Name   : Command.h
* Ver    : Beta
* Author : SanaePRJ
--------------------------------------------------------------------------*/


/*INCLUDE GUARD*/
#ifndef SANAE_COMMAND_H
#define SANAE_COMMAND_H


/*Include*/
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 64


//Command Read
void Command_Read(char buf[BUFFER_SIZE]){
  Serial.println("[Command]Please Wait.");
  delay(1000);  //バッファ蓄積

  for(unsigned char pos = 0;pos<BUFFER_SIZE;pos++)
  {
    char data = Serial.read();
    //番兵
    if(data == ';'){
      buf[pos] = '\0';
      break;
    }
    //データセット
    buf[pos] = data;
  }
}
//Process Command
template<typename MotorX,typename MotorY,typename MotorZ>
void Command(char data[BUFFER_SIZE],MotorX* motor_x,MotorY* motor_y,MotorZ* motor_z){
  //コマンドの説明
  if(strcmp("command",(const char*)data)==0){
    const char* command = 
      "\"home;\":すべての軸をホームへ戻します。\n\"stop;\":すべての動作を停止させます。\n   \"restart;\":システムを再開させます。";
    Serial.println(command);
  //ホームポジションへ
  }else  if(strcmp("home",(const char*)data)==0){
    motor_x->MoveHome();
    motor_y->MoveHome();
  }else  if(strcmp("xhome",(const char*)data)==0){
    motor_x->MoveHome();
  }else  if(strcmp("yhome",(const char*)data)==0){
    motor_y->MoveHome();
  //停止命令
  }else if(strcmp("stop",(const char*)data)==0){
    Serial.println("[Command]System is stopping...");
    Serial.println("[Command]You can resume by typing \"restart\"");

    //すべてのモータを停止
    motor_x->Stop();
    motor_y->Stop();
    motor_z->Stop();

    while(true)
    {
      //再開命令受け取り開始
      if(Serial.available()>0){
        //バッファ
        char restart[BUFFER_SIZE];

        //コマンドを入手
        Command_Read(restart);

        //再開
        if(strcmp("restart",(const char*)restart)==0)
          break;
      }
    }
    Serial.println("[Command]Restart...");
  }else{
    //コマンド該当なし
    Serial.println("[Command]NotFound...");
  }
}


#endif