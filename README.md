# English(Translated by bing AI)
## UFO Catcher System
* This system is designed for a theme-based research project (UFO-Catcher) in high school.
* The programs in this repository are written in Arduino language.
* Author:SanaePRJ  
WebSite:http://sanae.starfree.jp

## UFO Catcher's Architecture
This text explains the operating principle of UFO-Catcher below.

First, the operation of UFO-Catcher involves X, Y, and Z axes, and in this text, we will describe them as follows:

The horizontal direction is X  
The vertical direction is Y  
The height direction is Z  
The motors of X, Y, and Z axes are controlled by relays. The relay module used in this research project operates by inputting Gnd.  

Braking of X, Y axis motors:
* The motor control uses three pins and controls them by sending GND.  
* Sending GND to the first pin makes the current flow and the motor rotate. This is called forward rotation.  
* Sending GND to the second pin can reverse the rotation of the motor. This is called reverse rotation.  
* Sending GND to the third pin can further reverse the rotation that was either forward or reverse by pins 1 and 2.  
* The third pin can be connected to a limit switch, so that when it touches the limit switch, it can bounce back if it continues the same operation.  

Braking of Z axis motor:  
* Forward and reverse rotation are the same as X and Y, but the Z axis does not have a limit switch, so it raises or lowers by time.
The arm opens when it lowers and closes when it raises.
# 日本語
## UFO Catcher System
* このシステムは高校の課題研究(UFO Catcher)用に開発されたものである。
* このリポジトリ内のプログラムはArduino言語で記述されている。
* 作者:SanaePRJ  
ウェブサイト:http://sanae.starfree.jp
## UFO-Catcherの構造
このテキストでは以下に課題研究で開発したUFOキャッチャーの動作原理について説明する。

まずUFOキャッチャーの動作ではX,Y,Z軸が存在しこのテキストでは
横方向をX,縦方向をY,高さ方向をZと置いて記述していく。

X,Y,Z軸のモータはリレーにより操作される。
この課題研究で使用するのはリレーモジュールでGndを入力することでリレーが動作する。

X,Y軸モータの制動:
* モータの制御には3つのピンに対してGNDを送って制御する。
一つ目のピンにGNDを送ることでモータに電流が流れ回転する。これを正転とする。  
* 二つ目のピンにGNDを送ることでモータの回転を逆回転させることができる。これを逆転としている。  
* 三つ目のピンにGNDを送ることで1,2ピンで正転又は逆転されていたものをさらに逆転させることができる。  
尚三つ目のピンはリミットスイッチを接続することでリミットスイッチに触れた際同じ操作をとり続ければ
跳ね返すことができる。  
    
Z軸モータの制動:  
* 正転・逆転はX,Yと同じだがZ軸にはリミットスイッチがないため時間により上げたり下げたりする。
アームは下げた際に開き上げる際に閉じるようになっている。