//
//  main.cpp
//  Pong
//
//  Created by Santiago Vera on 25/07/20.
//  Copyright © 2020 Mistic_Lion. All rights reserved.
//
#define OLC_PGE_APPLICATION

#include <iostream>
#include "olcPixelGameEngine.h"
using namespace std;

class Prueba : public olc::PixelGameEngine {
private:

    int ScreenWidthGame = 200;
    int ScreenHeightGame = 150;

    int const SPR_Size = 6;
    int const HalfSPR_Size = SPR_Size;

    int PaddleWidth = SPR_Size * 0.66;
    int PaddleLenght = 20;

    float HorzBallSpeed = 0.5f;
    float VertBallSpeed = 1.0f;

    bool HorizontalBallDirection = rand() % 2;
    bool VerticalBallDirection = rand() % 2;


    int cont_2 = 0;
    int cont_3 = 0;

    int P1 = 0;
    int P2 = 0;

    int const GameOverDelay = 20;

public:

    float OffSetBall_Y = Ball_Y + (SPR_Size / 2);

    float Ball_X = (ScreenWidthGame / 2) - HalfSPR_Size;
    float Ball_X2 = Ball_X + SPR_Size;
    float Ball_Y = (ScreenHeightGame / 2) - HalfSPR_Size;
    float Ball_Y2 = Ball_Y + SPR_Size;

    float RightPaddle_X = ScreenWidthGame - 10;
    float RightPaddle_X2 = RightPaddle_X + PaddleWidth;
    float RightPaddle_Y = ScreenHeightGame / 2 - PaddleLenght / 2;
    float RightPaddle_Y2 = RightPaddle_Y + PaddleLenght;

    float LeftPaddle_X = 10 - PaddleWidth;
    float LeftPaddle_X2 = LeftPaddle_X + PaddleWidth;
    float LeftPaddle_Y = ScreenHeightGame / 2 - PaddleLenght / 2;
    float LeftPaddle_Y2 = LeftPaddle_Y + PaddleLenght;

    //Detects Ball Hitbox
    bool DoesBallTouchHorizontal() {
        if (Ball_Y <= 0) {
            AlternateBoolean(VerticalBallDirection);
            Ball_Y = 0.0001;
            return true;
        }
        if (Ball_Y2 >= ScreenHeight()) {
            AlternateBoolean(VerticalBallDirection);
            Ball_Y = ScreenHeight() - SPR_Size - 0.0001;
            return true;
        }
        return false;
    }

    int DoesBallGetPoint() {
        if (Ball_X2 <= 0 - GameOverDelay) return 0;
        else if (Ball_X > ScreenWidth() + GameOverDelay) return 1;
        else return 2;
    }

    bool AlternateBoolean(bool& Hola) {
        if (Hola == false) Hola = true;
        else if (Hola == true) Hola = false;

        return Hola;
    }

    bool AlternatePaddleSections() {
        int n = 0;

        if (OffSetBall_Y<RightPaddle_Y2 + HalfSPR_Size and OffSetBall_Y>RightPaddle_Y - HalfSPR_Size) {
            if (Ball_X2 >= RightPaddle_X and Ball_X <= RightPaddle_X2) {
                AlternateBoolean(HorizontalBallDirection);
                Ball_X = RightPaddle_X - SPR_Size;

                n = RightPaddle_Y2 + HalfSPR_Size - OffSetBall_Y;

                switch (n) {
                case 0:
                    VertBallSpeed = 2;
                    VerticalBallDirection = true;
                    break;
                case 1:
                    VertBallSpeed = 1.9;
                    VerticalBallDirection = true;
                    break;
                case 2:
                    VertBallSpeed = 1.8;
                    VerticalBallDirection = true;
                    break;
                case 3:
                    VertBallSpeed = 1.7;
                    VerticalBallDirection = true;
                    break;
                case 4:
                    VertBallSpeed = 1.6;
                    VerticalBallDirection = true;
                    break;
                case 5:
                    VertBallSpeed = 1.5;
                    VerticalBallDirection = true;
                    break;
                case 6:
                    VertBallSpeed = 1.45;
                    VerticalBallDirection = true;
                    break;
                case 7:
                    VertBallSpeed = 1.4;
                    VerticalBallDirection = true;
                    break;
                case 8:
                    VertBallSpeed = 1.35;
                    VerticalBallDirection = true;
                    break;
                case 9:
                    VertBallSpeed = 1.3;
                    VerticalBallDirection = true;
                    break;
                case 10:
                    VertBallSpeed = 1.25;
                    VerticalBallDirection = true;
                    break;
                case 11:
                    VertBallSpeed = 1.2;
                    VerticalBallDirection = true;
                    break;
                case 12:
                    VertBallSpeed = 1.15;
                    VerticalBallDirection = true;
                    break;
                case 13:
                    VertBallSpeed = 1.1;
                    VerticalBallDirection = true;
                    break;
                case 14:
                    VertBallSpeed = 1;
                    VerticalBallDirection = true;
                    break;
                case 15:
                    VertBallSpeed = 0.7;
                    VerticalBallDirection = true;
                    break;
                case 16:
                    VertBallSpeed = 0.5;
                    VerticalBallDirection = true;
                    break;
                case 17:
                    VertBallSpeed = 0.7;
                    VerticalBallDirection = false;
                    break;
                case 18:
                    VertBallSpeed = 1;
                    VerticalBallDirection = false;
                    break;
                case 19:
                    VertBallSpeed = 1.1;
                    VerticalBallDirection = false;
                    break;
                case 20:
                    VertBallSpeed = 1.15;
                    VerticalBallDirection = false;
                    break;
                case 21:
                    VertBallSpeed = 1.2;
                    VerticalBallDirection = false;
                    break;
                case 22:
                    VertBallSpeed = 1.25;
                    VerticalBallDirection = false;
                    break;
                case 23:
                    VertBallSpeed = 1.3;
                    VerticalBallDirection = false;
                    break;
                case 24:
                    VertBallSpeed = 1.35;
                    VerticalBallDirection = false;
                    break;
                case 25:
                    VertBallSpeed = 1.4;
                    VerticalBallDirection = false;
                    break;
                case 26:
                    VertBallSpeed = 1.45;
                    VerticalBallDirection = false;
                    break;
                case 27:
                    VertBallSpeed = 1.5;
                    VerticalBallDirection = false;
                    break;
                case 28:
                    VertBallSpeed = 1.6;
                    VerticalBallDirection = false;
                    break;
                case 29:
                    VertBallSpeed = 1.7;
                    VerticalBallDirection = false;
                    break;
                case 30:
                    VertBallSpeed = 2;
                    VerticalBallDirection = false;
                    break;
                case 31:
                    VertBallSpeed = 1;
                    VerticalBallDirection = false;
                    break;
                case 32:
                    VertBallSpeed = 2;
                    VerticalBallDirection = false;
                    break;

                }


            }
        }

        if (OffSetBall_Y<LeftPaddle_Y2 + HalfSPR_Size and OffSetBall_Y>LeftPaddle_Y - HalfSPR_Size) {
            if (Ball_X <= LeftPaddle_X2 and Ball_X2 >= LeftPaddle_X) {
                AlternateBoolean(HorizontalBallDirection);
                Ball_X = LeftPaddle_X2;

                n = LeftPaddle_Y2 + HalfSPR_Size - OffSetBall_Y;

                switch (n) {
                case 0:
                    VertBallSpeed = 2;
                    VerticalBallDirection = true;
                    break;
                case 1:
                    VertBallSpeed = 1.9;
                    VerticalBallDirection = true;
                    break;
                case 2:
                    VertBallSpeed = 1.8;
                    VerticalBallDirection = true;
                    break;
                case 3:
                    VertBallSpeed = 1.7;
                    VerticalBallDirection = true;
                    break;
                case 4:
                    VertBallSpeed = 1.6;
                    VerticalBallDirection = true;
                    break;
                case 5:
                    VertBallSpeed = 1.5;
                    VerticalBallDirection = true;
                    break;
                case 6:
                    VertBallSpeed = 1.45;
                    VerticalBallDirection = true;
                    break;
                case 7:
                    VertBallSpeed = 1.4;
                    VerticalBallDirection = true;
                    break;
                case 8:
                    VertBallSpeed = 1.35;
                    VerticalBallDirection = true;
                    break;
                case 9:
                    VertBallSpeed = 1.3;
                    VerticalBallDirection = true;
                    break;
                case 10:
                    VertBallSpeed = 1.25;
                    VerticalBallDirection = true;
                    break;
                case 11:
                    VertBallSpeed = 1.2;
                    VerticalBallDirection = true;
                    break;
                case 12:
                    VertBallSpeed = 1.15;
                    VerticalBallDirection = true;
                    break;
                case 13:
                    VertBallSpeed = 1.1;
                    VerticalBallDirection = true;
                    break;
                case 14:
                    VertBallSpeed = 1;
                    VerticalBallDirection = true;
                    break;
                case 15:
                    VertBallSpeed = 0.7;
                    VerticalBallDirection = true;
                    break;
                case 16:
                    VertBallSpeed = 0.5;
                    VerticalBallDirection = true;
                    break;
                case 17:
                    VertBallSpeed = 0.7;
                    VerticalBallDirection = false;
                    break;
                case 18:
                    VertBallSpeed = 1;
                    VerticalBallDirection = false;
                    break;
                case 19:
                    VertBallSpeed = 1.1;
                    VerticalBallDirection = false;
                    break;
                case 20:
                    VertBallSpeed = 1.15;
                    VerticalBallDirection = false;
                    break;
                case 21:
                    VertBallSpeed = 1.2;
                    VerticalBallDirection = false;
                    break;
                case 22:
                    VertBallSpeed = 1.25;
                    VerticalBallDirection = false;
                    break;
                case 23:
                    VertBallSpeed = 1.3;
                    VerticalBallDirection = false;
                    break;
                case 24:
                    VertBallSpeed = 1.35;
                    VerticalBallDirection = false;
                    break;
                case 25:
                    VertBallSpeed = 1.4;
                    VerticalBallDirection = false;
                    break;
                case 26:
                    VertBallSpeed = 1.45;
                    VerticalBallDirection = false;
                    break;
                case 27:
                    VertBallSpeed = 1.5;
                    VerticalBallDirection = false;
                    break;
                case 28:
                    VertBallSpeed = 1.6;
                    VerticalBallDirection = false;
                    break;
                case 29:
                    VertBallSpeed = 1.7;
                    VerticalBallDirection = false;
                    break;
                case 30:
                    VertBallSpeed = 2;
                    VerticalBallDirection = false;
                    break;
                case 31:
                    VertBallSpeed = 1;
                    VerticalBallDirection = false;
                    break;
                case 32:
                    VertBallSpeed = 2;
                    VerticalBallDirection = false;
                    break;

                }


            }
        }

        return true;
    }


    //Changes Ball Direction depending on the hitbox detection
    void ChangeBallDirection() {
        DoesBallTouchHorizontal();
    }

    bool GameOver() {
        switch (DoesBallGetPoint()) {
        case 0:
            P2++;
            HorizontalBallDirection = rand() % 2;
            VerticalBallDirection = rand() % 2;
            Ball_X = (ScreenWidth() / 2) - HalfSPR_Size;
            Ball_Y = (ScreenHeight() / 2) - HalfSPR_Size;

            cout << "Player 1 = " << P1 << "\nPlayer 2 = " << P2 << endl << "-------------------------" << endl;

            break;

        case 1:
            P1++;
            HorizontalBallDirection = rand() % 2;
            VerticalBallDirection = rand() % 2;
            Ball_X = (ScreenWidth() / 2) - HalfSPR_Size;
            Ball_Y = (ScreenHeight() / 2) - HalfSPR_Size;

            cout << "Player 1 = " << P1 << "\nPlayer 2 = " << P2 << endl << "-------------------------" << endl;

            break;

        default:
            break;
        }
        return true;
    }


    //Moves the ball across the screen depending on the Ball Direction
    void MovesBall() {

        ChangeBallDirection();

        switch (HorizontalBallDirection) {
        case true:
            Ball_X = Ball_X + HorzBallSpeed * GetElapsedTime() * 100;
            break;

        case false:
            Ball_X = Ball_X - HorzBallSpeed * GetElapsedTime() * 100;
            break;
        }

        switch (VerticalBallDirection) {
        case true:
            Ball_Y = Ball_Y + VertBallSpeed * GetElapsedTime() * 100;
            break;

        case false:
            Ball_Y = Ball_Y - VertBallSpeed * GetElapsedTime() * 100;
            break;
        }



    }

    void SideChanging() {
        if (Ball_Y2 >= LeftPaddle_Y and Ball_Y <= LeftPaddle_Y2) {
            if (Ball_X2 >= LeftPaddle_X and Ball_X <= LeftPaddle_X2 - 1) {
                AlternateBoolean(VerticalBallDirection);
                VertBallSpeed = 2.5
                    ;
            }
        }
        if (Ball_Y2 >= RightPaddle_Y and Ball_Y <= RightPaddle_Y2) {
            if (Ball_X2 >= RightPaddle_X + 1 and Ball_X <= RightPaddle_X2) {
                AlternateBoolean(VerticalBallDirection);
                VertBallSpeed = 2.5;
            }
        }
    }

    void MovesRightPaddle( float Speed = 1) {
        if (GetKey(olc::UP).bHeld) {
            RightPaddle_Y -= Speed * GetElapsedTime() * 100;
        }
        else if (GetKey(olc::DOWN).bHeld) {
            RightPaddle_Y += Speed * GetElapsedTime() * 100;
        }
        if (RightPaddle_Y <= 2) RightPaddle_Y = 2;
        if (RightPaddle_Y >= ScreenHeightGame - PaddleLenght - 2) RightPaddle_Y = ScreenHeightGame - PaddleLenght - 2;
    }

    void MovesLeftPaddle(float Speed = 1) {
        if (GetKey(olc::W).bHeld) {
            LeftPaddle_Y -= Speed * GetElapsedTime() * 100;
        }
        else if (GetKey(olc::S).bHeld) {
            LeftPaddle_Y += Speed * GetElapsedTime() * 100;
        }
        if (LeftPaddle_Y <= 2) LeftPaddle_Y = 2;
        if (LeftPaddle_Y >= ScreenHeightGame - PaddleLenght - 2) LeftPaddle_Y = ScreenHeightGame - PaddleLenght - 2;
    }

    void DrawBall() {
        FillRect(Ball_X, Ball_Y, SPR_Size, SPR_Size);
    }

    void DrawPaddles() {
        FillRect(RightPaddle_X, RightPaddle_Y, PaddleWidth, PaddleLenght);
        FillRect(LeftPaddle_X, LeftPaddle_Y, PaddleWidth, PaddleLenght);
    }

    //-----------------------------------------------------------
    virtual void GameMethod() {
        Ball_X2 = Ball_X + SPR_Size;
        Ball_Y2 = Ball_Y + SPR_Size;
        OffSetBall_Y = Ball_Y + (SPR_Size / 2);

        AlternatePaddleSections();

        RightPaddle_Y2 = RightPaddle_Y + PaddleLenght;
        LeftPaddle_Y2 = LeftPaddle_Y + PaddleLenght;

        DrawBall();
        DrawPaddles();
        SideChanging();
        MovesBall();
        MovesRightPaddle();
        MovesLeftPaddle();
        GameOver();
    }

    virtual bool OnUserCreate() {
        return true;
    }

    virtual bool OnUserUpdate(float FElapsedTime) {
        double dExpectedTime = 1.0f / 60.0f;
        if (dExpectedTime >= GetElapsedTime()) Sleep((dExpectedTime - GetElapsedTime()) * 1000);

        Clear(olc::BLACK);

        GameMethod();

        return true;
    }
};

int main() {
    Prueba Demo;

    if (Demo.Construct(200, 150, 4, 4)) {
        Demo.Start();
    }

}