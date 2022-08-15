//
//  main.cpp
//  Snake
//
//  Created by Santiago Vera on 04/07/20.
//  Copyright © 2020 Mistic_Lion. All rights reserved.
//

#define OLC_PGE_APPLICATION
#define OLC_PGEX_TTF
#include <iostream>
#include <vector>
#include "olcPGEX_TTF.h"
#include "olcPixelGameEngine.h"
using namespace std;

class Game : public olc::PixelGameEngine {
    //olc::Font font;
    //----------------------------------------------------------------------------------------------------------
private:

    float SecondsPassed = 0;
    const float FPS_Limit = 60;
    const int ChecksPerFrame = 2;
    bool Pause = false;
    bool GameOver = false;
    bool TitleScreen = true;
    string Puntos = "0";

    //Control integers
    int cont = 0;
    int cont_2 = 0;
    int cont_3 = 0;
    int dirn=3;
    int Puntaje = 0;
    int animcont = 0;
    bool animswitch = false;

    int const SquareSize = 4;

    //Establish default direction
    int n = 3;

    //Structure of y and x positions among with it's speed
    struct Coord {

        float x = 40;
        float y = 40;

        int Speed = 40;
    };

    //Vector of Coord structures
    vector <Coord> Body;
    //Principal cordinates of the apple and the head of the snake
    Coord XY;
    Coord AppleXY;

    //Default snake lenght
    int Snake_lenght = 5;
    //Control integer to verify if the lenght has increased
    int templenght = Snake_lenght;
    //----------------------------------------------------------------------------------------------------------
public:
    //Constructor and destructor
    Game() {
    
        sAppName = "Snake";

    }

    

    ~Game() {}

    //----------------------------------------------------------------------------------------------------------
    //Changes the direction of the player avoiding changing it towards any body of the snake behind
    int Goes() {

        if (GetKey(olc::DOWN).bPressed and Body[1].x != Body[0].x) n = 0;
        else if (GetKey(olc::LEFT).bPressed and Body[1].y != Body[0].y) n = 1;
        else if (GetKey(olc::UP).bPressed and Body[1].x != Body[0].x) n = 2;
        else if (GetKey(olc::RIGHT).bPressed and Body[1].y != Body[0].y) n = 3;

        return n;
    }

    bool AppleEaten() {
        if (Body[0].x<(AppleXY.x + SquareSize) and (Body[0].x + SquareSize)>AppleXY.x) {
            if (Body[0].y<(AppleXY.y + SquareSize) and (Body[0].y + SquareSize)>AppleXY.y) {
                return true;
            }
        }
        return false;
    }

    void Apple() {
        if (AppleEaten()) {
            AppleXY.x = (int)((rand() % ScreenWidth() / 4) * 4);
            AppleXY.y = (int)(((rand() % (ScreenHeight()-12) / 4) * 4)+12);

            Puntaje++;

            Snake_lenght++;
        }

        FillRect(AppleXY.x, AppleXY.y, SquareSize, SquareSize, olc::RED);
    }

    void Snake() {
        cont++;

        Goes();

        float x = XY.x;
        float y = XY.y;

        if (cont_2 < 1) {
            AppleXY.x = (int)((rand() % ScreenWidth() / 4) * 4);
            AppleXY.y = (int)(((rand() % (ScreenHeight()-12) / 4) * 4)+12);

            for (int i = 0; i < Snake_lenght; i++) {
                Body.push_back({ x, y });
                x = x - SquareSize;
            }
        }

        cont_2++;

        if (cont >= (XY.Speed*GetElapsedTime())*100) {

            switch (dirn) {
            case 0:
                XY.y = XY.y + SquareSize;
                break;
            case 1:
                XY.x = XY.x - SquareSize;
                break;
            case 2:
                XY.y = XY.y - SquareSize;
                break;
            case 3:
                XY.x = XY.x + SquareSize;
                break;
            }

            if (cont_2 >= 1) {

                for (int i = Snake_lenght - 1; i > 0; i--) {
                    Body[i].x = Body[i - 1].x;
                    Body[i].y = Body[i - 1].y;
                }

                Body[0].x = XY.x;
                Body[0].y = XY.y;


                cont = 0;
            }


            //Handle hitboxes
            if (XY.x + SquareSize > ScreenWidth() or XY.x<0 or XY.y + SquareSize>ScreenHeight() or XY.y< 12) {
                Body.clear();

                XY.x = 40;
                XY.y = 40;
                Snake_lenght = 5;
                XY.Speed = 40;
                AppleXY.x = (int)((rand() % ScreenWidth() / 4) * 4);
                AppleXY.y = (int)(((rand() % (ScreenHeight() - 12) / 4) * 4) + 12);
                Puntaje = 0;
                GameOver = true;
                n = 3;

                x = XY.x;
                y = XY.y;
                for (int i = 0; i < 5; i++) {
                    Body.push_back({ x, y });
                    x = x - SquareSize;
                }

                
            }
            
            for (int i = 1; i < Snake_lenght; ++i) {
                if (Body[0].x<(Body[i].x + SquareSize) and (Body[0].x + SquareSize)>Body[i].x) {
                    if (Body[0].y<(Body[i].y + SquareSize) and (Body[0].y + SquareSize)>Body[i].y) {
                        Body.clear();

                        XY.x = 40;
                        XY.y = 40;
                        Snake_lenght = 5;
                        XY.Speed = 40;
                        AppleXY.x = (int)((rand() % ScreenWidth() / 4) * 4);
                        AppleXY.y = (int)(((rand() % (ScreenHeight() - 12) / 4) * 4) + 12);
                        Puntaje = 0;
                        GameOver = true;
                        n = 3;

                        x = XY.x;
                        y = XY.y;
                        for (int i = 0; i < 5; i++) {
                            Body.push_back({ x, y });
                            x = x - SquareSize;
                        }
                    }
                }
            }

        }

        //Render squares
        for (int i = 0; i < Body.size(); i++) {

            if (i == 0) FillRect(int(Body[0].x), int(Body[0].y), SquareSize, SquareSize,olc::GREEN);

            else FillRect(int(Body[i].x), int(Body[i].y), SquareSize, SquareSize, olc::WHITE);
        }

        if (Snake_lenght > templenght) {
            Body.push_back({ XY.x, XY.y });
        }

        templenght = Snake_lenght;
    }
    //----------------------------------------------------------------------------------------------------------
    virtual bool OnUserCreate() {
        //olc::Font::init();

        //font = olc::Font("Freshman (2).ttf", 20);

        return true;
    }
    //----------------------------------------------------------------------------------------------------------
    virtual bool OnUserUpdate(float fElapsedTime) {
        //Some positions
        olc::vf2d PauseTextPos = { float(ScreenWidth() / 2) - 20, float(ScreenHeight() / 2) - 10 };
        olc::vf2d ScoreTextPos = { 2.0f, 2.0f };
        olc::vf2d GameOverPos = { float(ScreenWidth() / 2) - 55, float(ScreenHeight() / 2) - 10 };
        olc::vf2d TextoadGameOver = { 2.0f, float(ScreenHeight() - 10.0f) };
        olc::vf2d PuntosPos = { 65.0f, 2.0f };
        olc::vf2d TituloSnake = { float(ScreenWidth() / 2) - 40, float(ScreenHeight() / 2) - 10 };


        FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::BLACK);

        double dExpectedTime = 1.0 / FPS_Limit;

        SecondsPassed = SecondsPassed + GetElapsedTime();

        if (dExpectedTime >= GetElapsedTime()) Sleep((dExpectedTime-GetElapsedTime())*1000);



        Puntos.clear();
        Puntos += to_string(Puntaje);

        if (!TitleScreen) {
            if (!GameOver) {

                if (cont_3 > 30) dirn = Goes();

                if (GetKey(olc::P).bPressed and !Pause) Pause = true;
                else if (GetKey(olc::P).bPressed and Pause) Pause = false;

                if (!Pause and !GameOver) {
                    int prevSnakeLength = Snake_lenght;

                    Snake();

                    //if (GetKey(olc::SPACE).bPressed) Snake_lenght++;

                    Apple();

                    //cout << AppleXY.x << endl << AppleXY.y << endl << endl;

                    if (Snake_lenght > prevSnakeLength and XY.Speed > 10) XY.Speed--;

                }
            }
            else if (GameOver) {
                if (GetKey(olc::ENTER).bPressed) GameOver = false;
                if (GetKey(olc::ESCAPE).bPressed) {
                    GameOver = false;
                    TitleScreen = true;
                }
            }
        }
        else if (TitleScreen) {
            DrawString(TituloSnake, "Snake", olc::GREEN, 2);
            DrawString(TextoadGameOver.x, TextoadGameOver.y-20, "Presiona enter\npara jugar", olc::WHITE, 1);
            if (GetKey(olc::ENTER).bPressed) TitleScreen = false;
        }



        if (GameOver) {
            DrawString(GameOverPos, "   Perdiste,\npresiona enter\npara reiniciar");
            DrawString(TextoadGameOver, "O esc para ir al lobby");
        }
        else if (Pause and !GameOver) {
            DrawString(PauseTextPos, "Pausa");
        }
        else if (!TitleScreen){
            DrawString(ScoreTextPos, "Puntaje:", olc::WHITE, 1);
            DrawString(PuntosPos, Puntos, olc::WHITE, 1);
            DrawLine(0, 12, ScreenWidth(), 12);
        }

        if (cont_3 > 30) dirn = Goes();

        cont_3++;
        return true;
    }
    //----------------------------------------------------------------------------------------------------------
};

int main() {
    Game Demo;
    if (Demo.Construct(200, 120, 4, 4)) Demo.Start();
    else cout << "Could not Construct Console\n";
}
