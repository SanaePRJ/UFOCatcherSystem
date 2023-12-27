/*--------------------------------------------------------------------------
* Name: UFOCatcherSystem.ino
* Ver : Beta
* Author     : SanaePRJ
* Description:
    このプログラムは課題研究で製作したUFOキャッチャーの制御プログラムである。
    ハードウェアの仕様についてはHardware.txtを参照。
--------------------------------------------------------------------------*/


/*Include*/
#include "Motor.h"
#include "CommonDef.h"
#include "Command.h"


/*Define*/
#define XMotion  2 //X軸モータ動作用ピン
#define XReverse 3 //X軸動作反転用ピン

#define YMotion  4 //Y軸モータ動作用ピン
#define YReverse 5 //Y軸動作反転用ピン

#define ZMotion  6 //Z軸モータ動作用ピン
#define ZReverse 7 //Z軸動作反転用ピン

//ユーザ入力
#define ButtonX 9
#define ButtonY 10

//リミットスイッチ
#define XLimit 12
#define YLimit 13

#define BUFFER_SIZE 64


Motor<XMotion,XReverse,XLimit> X_Motor; //X軸 正転:2,逆転:3,リミットスイッチ:12
Motor<YMotion,YReverse,YLimit> Y_Motor; //Y軸 正転:4,逆転:5,リミットスイッチ:13
Motor<ZMotion,ZReverse>        Z_Motor; //Z軸 正転:6,逆転:7

//前回の動作の時間を格納
unsigned long Clock;


//すべての動作を停止
void AllStop()
{
    X_Motor.Stop();
    Y_Motor.Stop();
    Z_Motor.Stop();
}

//X,Y軸をホームへ
void UfoCatcherMoveToHome()
{
    Serial.println("[UfoCatcherMoveToHome]Moving to home...");
    Serial.flush();

    X_Motor.MoveHome();
    Y_Motor.MoveHome();

    Serial.println("[UfoCatcherMoveToHome]Success...");
}

//アームを下げて上げる。
//下げる際に自動でアームが開く、上げる際に自動でアームが閉じる。
void Move_Arm()
{
    Serial.println("[Move_Arm]Down...");

    //下げる
    Z_Motor.Move();
    delay(1s);
    
    Serial.println("[Move_Arm]Up...");
    //上げる
    Z_Motor.InverseMove();
    delay(1s);

    Serial.println("[Move_Arm]Success...");

    Z_Motor.Stop();
    Serial.flush();
}


//SetUP
void setup() 
{
    Serial.begin(115200);
    Serial.println("[Copyright]Copyright 2023 SanaeProject.");

    pinMode(ButtonX,INPUT_PULLUP);
    pinMode(ButtonY,INPUT_PULLUP);

    //UfoキャッチャーのポジションをHomeへ
    UfoCatcherMoveToHome();

    //Clockを現在値へ
    Clock = millis();
}
//Loop
void loop() 
{
    uint8_t RetValue = 0;

    RetValue += X_Motor.Listen(ButtonX);
    RetValue += Y_Motor.Listen(ButtonY);

    //パソコンからの入力
    if(Serial.available()){
        //停止
        AllStop();

        char buf[BUFFER_SIZE];
        //読み取り
        Command_Read(buf);
        
        Serial.print("[GetCommand]");
        Serial.println(buf);

        //コマンド実行
        Command
        <
            Motor<XMotion,XReverse,XLimit>,
            Motor<YMotion,YReverse,YLimit>,
            Motor<ZMotion,ZReverse>
        >
        (buf,&X_Motor,&Y_Motor,&Z_Motor);

        Clock = millis();
    }

    //0よりも大きい場合動作しているのでClockを現在値で合わせる。
    if(RetValue>0)
        Clock = millis();

    //10秒間動作していない場合アームを下げる。
    if((millis()-Clock) > 10s)
    {
        //つかみ取る。
        Move_Arm();

        //ホームポジションへ
        UfoCatcherMoveToHome();

        //離す。
        Move_Arm();

        Serial.flush();
        delay(2s);
        Serial.flush();        

        Clock = millis();
    }
}