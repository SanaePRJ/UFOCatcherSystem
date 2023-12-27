/*--------------------------------------------------------------------------
* Name   : Motor.h
* Ver    : Beta
* Author : SanaePRJ
--------------------------------------------------------------------------*/


/*INCLUDE GUARD*/
#ifndef SANAE_MOTER_H
#define SANAE_MOTER_H


/*INCLUDE*/
#include "CommonDef.h"


/*---Motor制御用Class---
Motion  : 正転用
Reverse : 反転動作ピン
Limit   : 255の状態ではリミットスイッチがない判定
*/
template<Pin Motion,Pin Reverse,Pin Limit = 255>
class Motor
{
    /*PrivateVariables*/
private:
    //直前の動作を保存 normal-rotate:0,inverse-rotate:1
    unsigned char Previous_move = 255;


    /*PublicVariables*/
public:
    bool Is_Move_Normally = true;


    /*PrivateFunctions*/
private:
    //Activation
    void ActivateWithPin(Pin ActivePinNum)
    {
        //Active LOW
        digitalWrite(ActivePinNum,LOW);
        return;
    }
    //Deactivation
    void DeactivateWithPin(Pin PassivePinNum)
    {
        //Passive HIGH
        digitalWrite(PassivePinNum,HIGH);
        return;
    }
    
    //正転
    void NormalRotate()
    {
        Previous_move = 0;
        this->ActivateWithPin(Motion);
    }
    //逆転
    void InverseRotate()
    {
        Previous_move = 1;
        this->ActivateWithPin(Motion);
        this->ActivateWithPin(Reverse);
    }

    //リミットスイッチの状態を取得
    bool Is_TouchingLimit()
    {
        if(Limit==255)
            return false;
        
        return (digitalRead(Limit)==LOW);
    }
    //リミットスイッチに触れている際の動作
    void Move_TouchingLimit()
    {
        Serial.println("[Move_TouchingLimit]Start...");

        //前の動作を復元
        if(Previous_move == 0)
            this->NormalRotate();
        else if(Previous_move == 1)
            this->InverseRotate();
        
        //スイッチに触れている間ロック
        while(this->Is_TouchingLimit());
        this->Stop();

        Serial.println("[Move_TouchingLimit]Success...");
        Serial.flush();
    }

    
    /*PublicFunctions*/
public:
    //コンストラクタ
    Motor()
    {
        //各ピンを初期化
        pinMode(Motion,OUTPUT);
        pinMode(Reverse,OUTPUT);
        //チャタリング防止のためPULLUP
        pinMode(Limit,INPUT_PULLUP);

        //すべてのリレーをDeactiveする。
        this->Stop();
    }

    //順方向
    void Move()
    {
        Serial.println("[Move]Moving...");

        if(this->Is_Move_Normally)
            this->NormalRotate();
        else
            this->InverseRotate();
        
        return;
    }
    //逆方向
    void InverseMove()
    {
        Serial.println("[InverseMove]Moving inverse...");
        Serial.flush();

        if(this->Is_Move_Normally)
            this->InverseRotate();
        else
            this->NormalRotate();
        
        return;
    }
    //停止命令
    void Stop()
    {
        this->DeactivateWithPin(Motion);
        this->DeactivateWithPin(Reverse);
    }

    //ホームポジションへ送る。
    void MoveHome()
    {
        //逆方向へ
        this->InverseMove();
        //リミットスイッチに触れるまで
        while(!this->Is_TouchingLimit());
        //リミットスイッチに触れた際の動作
        this->Move_TouchingLimit();
        
        this->Stop();
        return;
    }

    //ユーザ入力(BUTTON)
    uint8_t Listen(Pin Button)
    {
        //Listenの結果 0:動作なし,1:Move,2:Move_TouchingLimit 
        uint8_t Code = 0;

        //ボタンが押されているか
        if(digitalRead(Button)==LOW)
        {
            this->Move();
            Code = 1;
        }
        else
            this->Stop();

        //LimitSwitchに触れているかどうか
        if(this->Is_TouchingLimit()){
            this->Move_TouchingLimit();
            Code = 2;
        }

        return Code;
    }
};


#endif