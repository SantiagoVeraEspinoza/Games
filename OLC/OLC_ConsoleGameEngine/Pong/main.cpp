//
//  main.cpp
//  Pong
//
//  Created by Santiago Vera on 25/07/20.
//  Copyright © 2020 Mistic_Lion. All rights reserved.
//

#include <iostream>
#include "olcConsoleGameEngineSDL.h"
using namespace std;

class Prueba : public olcConsoleGameEngine{
private:
    
    int ScreenWidthGame=200;
    int ScreenHeightGame=150;
    
    int const SPR_Size=6;
    int const HalfSPR_Size=SPR_Size;
    
    int PaddleWidth=SPR_Size*0.66;
    int PaddleLenght=20;
    
    float HorzBallSpeed=0.5f;
    float VertBallSpeed=1.0f;
    
    bool HorizontalBallDirection=rand()%2;
    bool VerticalBallDirection=rand()%2;

    
    int cont_2=0;
    int cont_3=0;
    
    int P1=0;
    int P2=0;
    
    int const GameOverDelay=20;
    
public:
    
    float OffSetBall_Y=Ball_Y+(SPR_Size/2);
    
    float Ball_X=(ScreenWidthGame/2)-HalfSPR_Size;
    float Ball_X2=Ball_X+SPR_Size;
    float Ball_Y=(ScreenHeightGame/2)-HalfSPR_Size;
    float Ball_Y2=Ball_Y+SPR_Size;
    
    float RightPaddle_X=ScreenWidthGame-10;
    float RightPaddle_X2=RightPaddle_X+PaddleWidth;
    float RightPaddle_Y=ScreenHeightGame/2-PaddleLenght/2;
    float RightPaddle_Y2=RightPaddle_Y+PaddleLenght;
    
    float LeftPaddle_X=10-PaddleWidth;
    float LeftPaddle_X2=LeftPaddle_X+PaddleWidth;
    float LeftPaddle_Y=ScreenHeightGame/2-PaddleLenght/2;
    float LeftPaddle_Y2=LeftPaddle_Y+PaddleLenght;
    
    //Detects Ball Hitbox
    bool DoesBallTouchHorizontal(){
        if(Ball_Y<=0 or Ball_Y2>=ScreenHeight()) return true;
        return false;
    }
    
    int DoesBallGetPoint(){
        if(Ball_X2<=0-GameOverDelay) return 0;
        else if(Ball_X>ScreenWidth()+GameOverDelay) return 1;
        else return 2;
    }
    
    bool AlternateBoolean(bool &Hola){
        if(Hola==false) Hola=true;
        else if(Hola==true) Hola=false;
        
        return Hola;
    }
    
    bool AlternatePaddleSections(){
        int n=0;
        
        if (OffSetBall_Y<RightPaddle_Y2+HalfSPR_Size and OffSetBall_Y>RightPaddle_Y-HalfSPR_Size){
            if (Ball_X2==RightPaddle_X){
                AlternateBoolean(HorizontalBallDirection);
                
                n=RightPaddle_Y2+HalfSPR_Size-OffSetBall_Y;
                
                switch (n) {
                    case 0:
                        VertBallSpeed=2;
                        VerticalBallDirection=true;
                        break;
                    case 1:
                        VertBallSpeed=1.9;
                        VerticalBallDirection=true;
                        break;
                    case 2:
                        VertBallSpeed=1.8;
                        VerticalBallDirection=true;
                        break;
                    case 3:
                        VertBallSpeed=1.7;
                        VerticalBallDirection=true;
                        break;
                    case 4:
                        VertBallSpeed=1.6;
                        VerticalBallDirection=true;
                        break;
                    case 5:
                        VertBallSpeed=1.5;
                        VerticalBallDirection=true;
                        break;
                    case 6:
                        VertBallSpeed=1.45;
                        VerticalBallDirection=true;
                        break;
                    case 7:
                        VertBallSpeed=1.4;
                        VerticalBallDirection=true;
                        break;
                    case 8:
                        VertBallSpeed=1.35;
                        VerticalBallDirection=true;
                        break;
                    case 9:
                        VertBallSpeed=1.3;
                        VerticalBallDirection=true;
                        break;
                    case 10:
                        VertBallSpeed=1.25;
                        VerticalBallDirection=true;
                        break;
                    case 11:
                        VertBallSpeed=1.2;
                        VerticalBallDirection=true;
                        break;
                    case 12:
                        VertBallSpeed=1.15;
                        VerticalBallDirection=true;
                        break;
                    case 13:
                        VertBallSpeed=1.1;
                        VerticalBallDirection=true;
                        break;
                    case 14:
                        VertBallSpeed=1;
                        VerticalBallDirection=true;
                        break;
                    case 15:
                        VertBallSpeed=0.7;
                        VerticalBallDirection=true;
                        break;
                    case 16:
                        VertBallSpeed=0.5;
                        VerticalBallDirection=true;
                        break;
                    case 17:
                        VertBallSpeed=0.7;
                        VerticalBallDirection=false;
                        break;
                    case 18:
                        VertBallSpeed=1;
                        VerticalBallDirection=false;
                        break;
                    case 19:
                        VertBallSpeed=1.1;
                        VerticalBallDirection=false;
                        break;
                    case 20:
                        VertBallSpeed=1.15;
                        VerticalBallDirection=false;
                        break;
                    case 21:
                        VertBallSpeed=1.2;
                        VerticalBallDirection=false;
                        break;
                    case 22:
                        VertBallSpeed=1.25;
                        VerticalBallDirection=false;
                        break;
                    case 23:
                        VertBallSpeed=1.3;
                        VerticalBallDirection=false;
                        break;
                    case 24:
                        VertBallSpeed=1.35;
                        VerticalBallDirection=false;
                        break;
                    case 25:
                        VertBallSpeed=1.4;
                        VerticalBallDirection=false;
                        break;
                    case 26:
                        VertBallSpeed=1.45;
                        VerticalBallDirection=false;
                        break;
                    case 27:
                        VertBallSpeed=1.5;
                        VerticalBallDirection=false;
                        break;
                    case 28:
                        VertBallSpeed=1.6;
                        VerticalBallDirection=false;
                        break;
                    case 29:
                        VertBallSpeed=1.7;
                        VerticalBallDirection=false;
                        break;
                    case 30:
                        VertBallSpeed=2;
                        VerticalBallDirection=false;
                        break;
                    case 31:
                        VertBallSpeed=1;
                        VerticalBallDirection=false;
                        break;
                    case 32:
                        VertBallSpeed=2;
                        VerticalBallDirection=false;
                        break;
                    
                }
                
                
            }
        }
        
        if (OffSetBall_Y<LeftPaddle_Y2+HalfSPR_Size and OffSetBall_Y>LeftPaddle_Y-HalfSPR_Size){
            if (Ball_X==LeftPaddle_X2){
                AlternateBoolean(HorizontalBallDirection);
                
                n=LeftPaddle_Y2+HalfSPR_Size-OffSetBall_Y;
                
                switch (n) {
                    case 0:
                        VertBallSpeed=2;
                        VerticalBallDirection=true;
                        break;
                    case 1:
                        VertBallSpeed=1.9;
                        VerticalBallDirection=true;
                        break;
                    case 2:
                        VertBallSpeed=1.8;
                        VerticalBallDirection=true;
                        break;
                    case 3:
                        VertBallSpeed=1.7;
                        VerticalBallDirection=true;
                        break;
                    case 4:
                        VertBallSpeed=1.6;
                        VerticalBallDirection=true;
                        break;
                    case 5:
                        VertBallSpeed=1.5;
                        VerticalBallDirection=true;
                        break;
                    case 6:
                        VertBallSpeed=1.45;
                        VerticalBallDirection=true;
                        break;
                    case 7:
                        VertBallSpeed=1.4;
                        VerticalBallDirection=true;
                        break;
                    case 8:
                        VertBallSpeed=1.35;
                        VerticalBallDirection=true;
                        break;
                    case 9:
                        VertBallSpeed=1.3;
                        VerticalBallDirection=true;
                        break;
                    case 10:
                        VertBallSpeed=1.25;
                        VerticalBallDirection=true;
                        break;
                    case 11:
                        VertBallSpeed=1.2;
                        VerticalBallDirection=true;
                        break;
                    case 12:
                        VertBallSpeed=1.15;
                        VerticalBallDirection=true;
                        break;
                    case 13:
                        VertBallSpeed=1.1;
                        VerticalBallDirection=true;
                        break;
                    case 14:
                        VertBallSpeed=1;
                        VerticalBallDirection=true;
                        break;
                    case 15:
                        VertBallSpeed=0.7;
                        VerticalBallDirection=true;
                        break;
                    case 16:
                        VertBallSpeed=0.5;
                        VerticalBallDirection=true;
                        break;
                    case 17:
                        VertBallSpeed=0.7;
                        VerticalBallDirection=false;
                        break;
                    case 18:
                        VertBallSpeed=1;
                        VerticalBallDirection=false;
                        break;
                    case 19:
                        VertBallSpeed=1.1;
                        VerticalBallDirection=false;
                        break;
                    case 20:
                        VertBallSpeed=1.15;
                        VerticalBallDirection=false;
                        break;
                    case 21:
                        VertBallSpeed=1.2;
                        VerticalBallDirection=false;
                        break;
                    case 22:
                        VertBallSpeed=1.25;
                        VerticalBallDirection=false;
                        break;
                    case 23:
                        VertBallSpeed=1.3;
                        VerticalBallDirection=false;
                        break;
                    case 24:
                        VertBallSpeed=1.35;
                        VerticalBallDirection=false;
                        break;
                    case 25:
                        VertBallSpeed=1.4;
                        VerticalBallDirection=false;
                        break;
                    case 26:
                        VertBallSpeed=1.45;
                        VerticalBallDirection=false;
                        break;
                    case 27:
                        VertBallSpeed=1.5;
                        VerticalBallDirection=false;
                        break;
                    case 28:
                        VertBallSpeed=1.6;
                        VerticalBallDirection=false;
                        break;
                    case 29:
                        VertBallSpeed=1.7;
                        VerticalBallDirection=false;
                        break;
                    case 30:
                        VertBallSpeed=2;
                        VerticalBallDirection=false;
                        break;
                    case 31:
                        VertBallSpeed=1;
                        VerticalBallDirection=false;
                        break;
                    case 32:
                        VertBallSpeed=2;
                        VerticalBallDirection=false;
                        break;
                        
                }
                
                
            }
        }
        
        return true;
    }
    
    
    //Changes Ball Direction depending on the hitbox detection
    void ChangeBallDirection(){
        if(DoesBallTouchHorizontal()){
            AlternateBoolean(VerticalBallDirection);
        }
    }
    
    bool GameOver(){
        switch (DoesBallGetPoint()) {
            case 0:
                P2++;
                HorizontalBallDirection=rand()%2;
                VerticalBallDirection=rand()%2;
                Ball_X=(ScreenWidth()/2)-HalfSPR_Size;
                Ball_Y=(ScreenHeight()/2)-HalfSPR_Size;
                
                cout << "Player 1 = " << P1 << "\nPlayer 2 = " << P2 << endl << "-------------------------" << endl;
                
                break;
                
            case 1:
                P1++;
                HorizontalBallDirection=rand()%2;
                VerticalBallDirection=rand()%2;
                Ball_X=(ScreenWidth()/2)-HalfSPR_Size;
                Ball_Y=(ScreenHeight()/2)-HalfSPR_Size;
                
                cout << "Player 1 = " << P1 << "\nPlayer 2 = " << P2 << endl << "-------------------------" << endl;
                
                break;
                
            default:
                break;
        }
        return true;
    }
    
    
    //Moves the ball across the screen depending on the Ball Direction
    void MovesBall(){
        
        ChangeBallDirection();
        
        switch (HorizontalBallDirection) {
            case true:
                Ball_X=Ball_X+HorzBallSpeed;
                break;
                
            case false:
                Ball_X=Ball_X-HorzBallSpeed;
                break;
        }
        
        switch (VerticalBallDirection) {
            case true:
                Ball_Y=Ball_Y+VertBallSpeed;
                break;
                
            case false:
                Ball_Y=Ball_Y-VertBallSpeed;
                break;
        }
        
        
        
    }
    
    void SideChanging(){
        if(Ball_Y2>=LeftPaddle_Y and Ball_Y<=LeftPaddle_Y2){
            if(Ball_X2>=LeftPaddle_X and Ball_X<=LeftPaddle_X2-1){
                AlternateBoolean(VerticalBallDirection);
                VertBallSpeed=2.5
                ;
            }
        }
        if(Ball_Y2>=RightPaddle_Y and Ball_Y<=RightPaddle_Y2){
            if(Ball_X2>=RightPaddle_X+1 and Ball_X<=RightPaddle_X2){
                AlternateBoolean(VerticalBallDirection);
                VertBallSpeed=2.5;
            }
        }
    }
    
    void MovesRightPaddle(){
        if(GetKey(VK_UP).bHeld and RightPaddle_Y>=2){
            cont_2++;
            if(cont_2==1){
                RightPaddle_Y--;
                cont_2=0;
            }
        }
        else if(GetKey(VK_DOWN).bHeld and RightPaddle_Y2<=ScreenHeightGame-2){
            cont_2++;
            if(cont_2==1){
                RightPaddle_Y++;
                cont_2=0;
            }
        }
        
        if (GetKey(VK_UP).bReleased or GetKey(VK_DOWN).bReleased) cont_2=0;
    }
    
    void MovesLeftPaddle(){
        if(GetKey(VK_W).bHeld and LeftPaddle_Y>=2){
            cont_3++;
            if(cont_3==1){
                LeftPaddle_Y--;
                cont_3=0;
            }
        }
        else if(GetKey(VK_S).bHeld and LeftPaddle_Y2<=ScreenHeightGame-2){
            cont_3++;
            if(cont_3==1){
                LeftPaddle_Y++;
                cont_3=0;
            }
        }
        if (GetKey(VK_UP).bReleased or GetKey(VK_DOWN).bReleased) cont_2=0;
    }
    
    void DrawBall(){
        Fill(Ball_X, Ball_Y, Ball_X2, Ball_Y2);
    }
    
    void DrawPaddles(){
        Fill(RightPaddle_X, RightPaddle_Y, RightPaddle_X2, RightPaddle_Y2);
        Fill(LeftPaddle_X, LeftPaddle_Y, LeftPaddle_X2, LeftPaddle_Y2);
    }
    
    //-----------------------------------------------------------
    virtual void GameMethod(){
        Ball_X2=Ball_X+SPR_Size;
        Ball_Y2=Ball_Y+SPR_Size;
        OffSetBall_Y=Ball_Y+(SPR_Size/2);
        
        AlternatePaddleSections();
        
        RightPaddle_Y2=RightPaddle_Y+PaddleLenght;
        LeftPaddle_Y2=LeftPaddle_Y+PaddleLenght;
        
        DrawBall();
        DrawPaddles();
        SideChanging();
        MovesBall();
        MovesRightPaddle();
        MovesLeftPaddle();
        GameOver();
    }
    
    virtual bool OnUserCreate(){
        return true;
    }
    
    virtual bool OnUserUpdate(float FElapsedTime){
        
        Fill(0, 0, ScreenWidth(), ScreenHeight(),FG_BLACK);
        
        GameMethod();
        
        return true;
    }
};

int main() {
    Prueba Demo;
    
    if(Demo.ConstructConsole(200, 150, 4, 4)){
        Demo.Start();
    }
    
}
