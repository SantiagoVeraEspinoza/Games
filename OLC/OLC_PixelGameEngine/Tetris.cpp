//
//  main.cpp
//  Tetris
//
//  Created by Santiago Vera on 07/07/20.
//  Copyright © 2020 Mistic_Lion. All rights reserved.
//

#define OLC_PGE_APPLICATION
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
//#include "soloud.h"
//#include "soloud_wav.h"
#include "olcPixelGameEngine.h"
using namespace std;

class Juego : public olc::PixelGameEngine {

private:

    int long score;

    int Speed = 30;

    int FieldWidth = 60;
    int FieldHeight = 100;
    int cont = 0;
    int cont_2 = 0;
    int cont_3 = 0;
    int cont_4 = 0;
    int FramesToGoDown = 0;

    int Tetromino_Type = rand() % 7;
    int long UserTetrominoArraySize = 0;
    int long MeshTetrominoArraySize = 0;
    int long MeshIndex = 0;
    int long SavedArraySize = 0;

    int const static Block_Size = 4;

    struct Coord {
        float x, y;
    };

    struct Cubes {
        vector <Coord> Arr;
        olc::Pixel Colour;
    };

    int Saved_Type;
    bool HasBeenPressed = false;
    int Next_Type = 5;

    vector <Cubes> Tetromino;
    vector <Cubes> Tetromino_Mesh;
    vector <Cubes> Next_Tetromino;


    float Pos_X;
    float Pos_Y = 28;
    bool CanSwitch = true;

    int OffSet_X_SavedTetromino = 0;
    int OffSet_Y_SavedTetromino = 0;
    int OffSet_X_NextTetromino = 0;
    int OffSet_Y_NextTetromino = 0;

    float User_Flag = 0;
    float User_Flag2 = 0;
    float KeyHoldFlag = 0;
    float KeyHoldFlag2 = 0;
    float User_Y = 0;

    int nSample = 0;

public:
    Juego() {
        sAppName = "Tetris";
    }
    ~Juego() {}

    //SoLoud::Soloud gSoloud;

    olc::Sprite* sprFondo = nullptr;
    olc::Decal* Fondo = nullptr;

    string Puntaje;

    int Layer1 = 0;
    int Layer2 = 1;

    int PuntajeReal = 0;
    int LineasCompletadas = 0;

    //SoLoud::Wav TitleMusic;

    void DrawField() {
        int BorderField_OOB_X = ((ScreenWidth() - FieldWidth) / 2) - 2;
        int BorderField_OOB_Y = ((ScreenHeight() - FieldHeight) / 2) - 2;

        int x1 = BorderField_OOB_X;
        int y1 = BorderField_OOB_Y;
        int x2 = BorderField_OOB_X + Block_Size;
        int y2 = BorderField_OOB_Y + FieldHeight;
        int x3 = x2;
        int y3 = y2 - Block_Size;
        int x4 = x2 + FieldWidth - Block_Size;
        int y4 = y2 + 1;
        int x5 = x4 - Block_Size;
        int y5 = y1;
        int x6 = x4 + 1;
        int y6 = y4;

        FillRect(x1, y1 - 1, Block_Size, FieldHeight + 1, olc::WHITE);
        FillRect(x3, y3, FieldWidth-3, Block_Size, olc::WHITE);
        FillRect(x5+1, y5 - 1, Block_Size, FieldHeight + 1, olc::WHITE);

        
        auto transpColor = olc::Pixel(0, 0, 0, 150);
        for (int i = y1; i < y2; i = i + 4) {
            DrawLine(x1 + Block_Size, i, x4 - 1 - Block_Size, i, transpColor);
        }
        for (int j = x1 + Block_Size; j < x4 - Block_Size + 1; j = j + 4) {
            DrawLine(j, y1, j, y2 - Block_Size - 1, transpColor);
        }
        Draw({ x4 - Block_Size , y2 - 4 }, transpColor);
        

        DrawLine(x5, y5 - 1, x5, y5, olc::BLACK);

        DrawSquareNextToField(OffSet_X_SavedTetromino, OffSet_Y_SavedTetromino);
        DrawSquareNextToField(OffSet_X_NextTetromino, OffSet_Y_NextTetromino);
        DrawLine(OffSet_X_NextTetromino + (Block_Size * 4) + 1, OffSet_Y_NextTetromino, OffSet_X_NextTetromino + 1 + (Block_Size * 4), OffSet_Y_NextTetromino + (4 * Block_Size));

    }

    void DrawSquareNextToField(int x, int y) {
        DrawLine(x, OffSet_Y_SavedTetromino - 1, x + 1 + (Block_Size * 4), y - 1);
        DrawLine(y + 1 + (Block_Size * 4), OffSet_Y_SavedTetromino, OffSet_X_SavedTetromino + 1 + (Block_Size * 4), y + (Block_Size * 4));
        DrawLine(x + 1 + (Block_Size * 4), y + (Block_Size * 4) + 1, x, y + (4 * Block_Size) + 1);
        DrawLine(x - 1, y + (4 * Block_Size) + 1, x - 1, y - 1);

    }

    void Rotate_Tetromino() {
        int ID[8];
        if (GetKey(olc::SPACE).bPressed and Tetromino_Type != 4 and Tetromino_Type != 1) {

            for (int i = 0; i < UserTetrominoArraySize; i++) {
                int x = (Tetromino[Tetromino_Type].Arr[i].x / 4);
                int y = (Tetromino[Tetromino_Type].Arr[i].y / 4);

                ID[i] = 3 - y + (4 * x);

                y = (ID[i] / 4);
                x = ID[i] - (4 * y);

                x = x * 4;
                y = y * 4;

                Tetromino[Tetromino_Type].Arr[i].x = x;
                Tetromino[Tetromino_Type].Arr[i].y = y;
            }

        }
        else if (GetKey(olc::SPACE).bPressed and Tetromino_Type == 1) {

            if (cont_2 == 0) {
                for (int i = 0; i < UserTetrominoArraySize; i++) {
                    int x = (Tetromino[Tetromino_Type].Arr[i].x / 4);
                    int y = (Tetromino[Tetromino_Type].Arr[i].y / 4);
                    ID[i] = 3 - y + (4 * x);

                    y = (ID[i] / 4);
                    x = ID[i] - (4 * y);

                    Tetromino[Tetromino_Type].Arr[i].x = x * 4;
                    Tetromino[Tetromino_Type].Arr[i].y = y * 4;
                }
                cont_2 = 1;
            }
            else if (cont_2 == 1) {
                for (int i = 0; i < Tetromino[Tetromino_Type].Arr.size(); i++) {
                    int x = (Tetromino[Tetromino_Type].Arr[i].x / 4);
                    int y = (Tetromino[Tetromino_Type].Arr[i].y / 4);

                    ID[i] = 12 + y - (x * 4);

                    y = (ID[i] / 4);
                    x = ID[i] - (4 * y);

                    Tetromino[Tetromino_Type].Arr[i].x = x * 4;
                    Tetromino[Tetromino_Type].Arr[i].y = y * 4;
                }
                cont_2 = 0;
            }
        }
    }

    bool DoesPieceFit() {
        for (int i = 0; i < UserTetrominoArraySize; i++) {
            if ((Tetromino[Tetromino_Type].Arr[i].x + Pos_X) >= (((((ScreenWidth() - FieldWidth) / 2) - 2) + Block_Size) + FieldWidth - (1 * Block_Size)) - Block_Size)return false;
        }

        return true;
    }

    bool DoesPieceFit2() {
        for (int i = 0; i < UserTetrominoArraySize; i++) {
            if ((Tetromino[Tetromino_Type].Arr[i].x + Pos_X) <= (((ScreenWidth() - FieldWidth) / 2) - 2)) return false;
        }
        return true;
    }

    bool DoesPieceFit3() {
        for (int i = 0; i < UserTetrominoArraySize; i++) {
            if ((Tetromino[Tetromino_Type].Arr[i].y + Pos_Y) >= ((((ScreenHeight() - FieldHeight) / 2) - 2) + FieldHeight) - (2 * Block_Size)) return false;
        }
        return true;
    }

    bool DoesPieceFitDown() {
        for (int i = 0; i < UserTetrominoArraySize; i++) {
            for (int j = 0; j <= MeshIndex; j++) {
                MeshTetrominoArraySize = Tetromino_Mesh[MeshIndex].Arr.size();
                for (int k = 0; k < MeshTetrominoArraySize; k++) {
                    if (Tetromino[Tetromino_Type].Arr[i].y + Pos_Y + 4 < Tetromino_Mesh[j].Arr[k].y + 4 and Tetromino[Tetromino_Type].Arr[i].y + Pos_Y + 8 > Tetromino_Mesh[j].Arr[k].y) {
                        if (Tetromino[Tetromino_Type].Arr[i].x + Pos_X<Tetromino_Mesh[j].Arr[k].x + 4 and Tetromino[Tetromino_Type].Arr[i].x + Pos_X + 4>Tetromino_Mesh[j].Arr[k].x) return false;
                    }
                }
            }
        }
        return true;
    }

    bool DoesPieceFitRight() {
        for (int i = 0; i < UserTetrominoArraySize; i++) {
            for (int j = 0; j <= MeshIndex; j++) {
                MeshTetrominoArraySize = Tetromino_Mesh[MeshIndex].Arr.size();
                for (int k = 0; k < MeshTetrominoArraySize; k++) {
                    if (Tetromino[Tetromino_Type].Arr[i].y + Pos_Y<Tetromino_Mesh[j].Arr[k].y + 4 and Tetromino[Tetromino_Type].Arr[i].y + Pos_Y + 4>Tetromino_Mesh[j].Arr[k].y) {
                        if (Tetromino[Tetromino_Type].Arr[i].x + Pos_X + 4 < Tetromino_Mesh[j].Arr[k].x + 4 and Tetromino[Tetromino_Type].Arr[i].x + Pos_X + 8 > Tetromino_Mesh[j].Arr[k].x) return false;
                    }
                }
            }
        }
        return true;
    }

    bool DoesPieceFitLeft() {
        for (int i = 0; i < UserTetrominoArraySize; i++) {
            for (int j = 0; j <= MeshIndex; j++) {
                MeshTetrominoArraySize = Tetromino_Mesh[MeshIndex].Arr.size();
                for (int k = 0; k < MeshTetrominoArraySize; k++) {
                    if (Tetromino[Tetromino_Type].Arr[i].y + Pos_Y<Tetromino_Mesh[j].Arr[k].y + 4 and Tetromino[Tetromino_Type].Arr[i].y + Pos_Y + 4>Tetromino_Mesh[j].Arr[k].y) {
                        if (Tetromino[Tetromino_Type].Arr[i].x + Pos_X - 4 < Tetromino_Mesh[j].Arr[k].x + 4 and Tetromino[Tetromino_Type].Arr[i].x + Pos_X > Tetromino_Mesh[j].Arr[k].x) return false;
                    }
                }
            }
        }
        return true;
    }

    bool NextRotationDoesFit() {
        int ID[8];

        if (Tetromino_Type != 4 and Tetromino_Type != 1) {
            for (int i = 0; i < UserTetrominoArraySize; i++) {
                int x = (Tetromino[Tetromino_Type].Arr[i].x / 4);
                int y = (Tetromino[Tetromino_Type].Arr[i].y / 4);

                ID[i] = 3 - y + (4 * x);

                y = (ID[i] / 4);
                x = ID[i] - (4 * y);

                x = x * 4;
                y = y * 4;

                //if ((x + Pos_X) > (((((ScreenWidth() - FieldWidth) / 2) - 2) + Block_Size) + FieldWidth - (3 * Block_Size)) or (x + Pos_X - 1 < (((ScreenWidth() - FieldWidth) / 2) - 2)) or (y + Pos_Y > ((((ScreenHeight() - FieldHeight) / 2) - 2) + FieldHeight) - (2 * Block_Size))) return false;

                for (int j = 0; j <= MeshIndex; j++) {
                    MeshTetrominoArraySize = Tetromino_Mesh[MeshIndex].Arr.size();
                    for (int k = 0; k < MeshTetrominoArraySize; k++) {
                        if (y + Pos_Y + 1 <= Tetromino_Mesh[j].Arr[k].y + 4 and y + Pos_Y + 3 >= Tetromino_Mesh[j].Arr[k].y) {
                            if (x + Pos_X + 1 <= Tetromino_Mesh[j].Arr[k].x + 4 and x + Pos_X + 3 >= Tetromino_Mesh[j].Arr[k].x)
                                return false;
                        }
                    }
                }
            }
        }
        else if (Tetromino_Type == 1) {

            if (cont_2 == 0) {
                for (int i = 0; i < UserTetrominoArraySize; i++) {
                    int x = (Tetromino[Tetromino_Type].Arr[i].x / 4);
                    int y = (Tetromino[Tetromino_Type].Arr[i].y / 4);

                    ID[i] = 3 - y + (4 * x);

                    y = (ID[i] / 4);
                    x = ID[i] - (4 * y);

                    x = x * 4;
                    y = y * 4;

                    /*if ((x + Pos_X) > (((((ScreenWidth() - FieldWidth) / 2) - 2) + Block_Size) + FieldWidth - (3 * Block_Size)) or (x + Pos_X - 1 < (((ScreenWidth() - FieldWidth) / 2) - 2)) or (y + Pos_Y > ((((ScreenHeight() - FieldHeight) / 2) - 2) + FieldHeight) - (2 * Block_Size)))
                        return false;*/

                    for (int j = 0; j <= MeshIndex; j++) {
                        MeshTetrominoArraySize = Tetromino_Mesh[MeshIndex].Arr.size();
                        for (int k = 0; k < MeshTetrominoArraySize; k++) {
                            if (y + Pos_Y + 1 <= Tetromino_Mesh[j].Arr[k].y + 4 and y + Pos_Y + 3 >= Tetromino_Mesh[j].Arr[k].y) {
                                if (x + Pos_X + 1 <= Tetromino_Mesh[j].Arr[k].x + 4 and x + Pos_X + 3 >= Tetromino_Mesh[j].Arr[k].x)return false;
                            }
                        }
                    }
                }
            }
            else if (cont_2 == 1) {
                for (int i = 0; i < Tetromino[Tetromino_Type].Arr.size(); i++) {
                    int x = (Tetromino[Tetromino_Type].Arr[i].x / 4);
                    int y = (Tetromino[Tetromino_Type].Arr[i].y / 4);

                    ID[i] = 12 + y - (x * 4);

                    y = (ID[i] / 4);
                    x = ID[i] - (4 * y);

                    x = x * 4;
                    y = y * 4;

                    //if ((x + Pos_X) > (((((ScreenWidth() - FieldWidth) / 2) - 2) + Block_Size) + FieldWidth - (3 * Block_Size)) or (x + Pos_X - 1 < (((ScreenWidth() - FieldWidth) / 2) - 2)) or (y + Pos_Y > ((((ScreenHeight() - FieldHeight) / 2) - 2) + FieldHeight) - (2 * Block_Size))) return false;

                    for (int j = 0; j <= MeshIndex; j++) {
                        MeshTetrominoArraySize = Tetromino_Mesh[MeshIndex].Arr.size();
                        for (int k = 0; k < MeshTetrominoArraySize; k++) {
                            if (y + Pos_Y + 1 <= Tetromino_Mesh[j].Arr[k].y + 4 and y + Pos_Y + 3 >= Tetromino_Mesh[j].Arr[k].y) {
                                if (x + Pos_X + 1 <= Tetromino_Mesh[j].Arr[k].x + 4 and x + Pos_X + 3 >= Tetromino_Mesh[j].Arr[k].x) return false;
                            }
                        }
                    }
                }
            }
        }
        return true;
    }

    bool SavedTypeDoesFit() {
        if (HasBeenPressed) {
            for (int i = 0; i < Next_Tetromino[Saved_Type].Arr.size(); i++) {
                int x = Tetromino[Saved_Type].Arr[i].x;
                int y = Tetromino[Saved_Type].Arr[i].y;

                if ((x + Pos_X) > (((((ScreenWidth() - FieldWidth) / 2) - 2) + Block_Size) + FieldWidth - (3 * Block_Size)) or (x + Pos_X - 1 < (((ScreenWidth() - FieldWidth) / 2) - 2)) or (y + Pos_Y > ((((ScreenHeight() - FieldHeight) / 2) - 2) + FieldHeight) - (2 * Block_Size)))
                    return false;

                for (int j = 0; j <= MeshIndex; j++) {
                    MeshTetrominoArraySize = Tetromino_Mesh[MeshIndex].Arr.size();
                    for (int k = 0; k < MeshTetrominoArraySize; k++) {
                        if (y + Pos_Y + 1 <= Tetromino_Mesh[j].Arr[k].y + 4 and y + Pos_Y + 3 >= Tetromino_Mesh[j].Arr[k].y) {
                            if (x + Pos_X + 1 <= Tetromino_Mesh[j].Arr[k].x + 4 and x + Pos_X + 3 >= Tetromino_Mesh[j].Arr[k].x) return false;
                        }
                    }
                }
            }
        }
        return true;
    }

    void MoveTetromino(float vel = 1) {

        if (GetKey(olc::RIGHT).bPressed and DoesPieceFit() and DoesPieceFitRight()) {
            Pos_X = Pos_X + 4;
        }

        else if (GetKey(olc::RIGHT).bHeld and DoesPieceFit() and DoesPieceFitRight()) {
            KeyHoldFlag++;
            if (KeyHoldFlag > (5 / (GetElapsedTime() * 20))) {
                User_Flag = User_Flag + vel * GetElapsedTime() * 20;

                if (User_Flag >= 1) {
                    Pos_X = Pos_X + 4;
                    User_Flag = 0;
                }
            }
        }

        else if (GetKey(olc::RIGHT).bReleased and !GetKey(olc::LEFT).bHeld) KeyHoldFlag = 0;



        else if (GetKey(olc::LEFT).bPressed and DoesPieceFit2() and DoesPieceFitLeft()) {
            Pos_X = Pos_X - 4;
        }

        else if (GetKey(olc::LEFT).bHeld and DoesPieceFit2() and DoesPieceFitLeft()) {
            KeyHoldFlag++;
            if (KeyHoldFlag > (5 / (GetElapsedTime() * 20))) {
                User_Flag = User_Flag + vel * GetElapsedTime() * 20;

                if (User_Flag >= 1) {
                    Pos_X = Pos_X - 4;
                    User_Flag = 0;
                }
            }
        }

        else if (GetKey(olc::LEFT).bReleased and !GetKey(olc::RIGHT).bHeld) KeyHoldFlag = 0;



        if (GetKey(olc::DOWN).bPressed and DoesPieceFit3() and DoesPieceFitDown()) {
            Pos_Y = Pos_Y + 4;
        }

        /*else if (GetKey(olc::DOWN).bHeld and DoesPieceFit3() and DoesPieceFitDown()) {
            KeyHoldFlag2++;
            if (KeyHoldFlag2 > (1 / (GetElapsedTime() * 10))) {
                User_Flag2 = User_Flag2 + vel * GetElapsedTime() * 20;

                if (User_Flag2 >= 1 and DoesPieceFitDown()) {
                    Pos_Y = Pos_Y + 4;
                    User_Flag2 = 0;
                }
            }
        }*/

        else if (GetKey(olc::DOWN).bReleased) KeyHoldFlag2 = 0;



        if (GetKey(olc::UP).bPressed) {
            while (DoesPieceFit3() and DoesPieceFitDown()) {
                Pos_Y = Pos_Y + 4;
            }
            cont_3 = (20 / (GetElapsedTime() * 10));
        }
    }


    void MeshTetrominos() {
        if (!DoesPieceFit3() or !DoesPieceFitDown()) {
            cont_3++;

            if (cont_3 > (20 / (GetElapsedTime()*10) ) ) {
                Tetromino_Mesh.push_back({});
                CanSwitch = true;
                for (int j = 0; j < Tetromino[Tetromino_Type].Arr.size(); j++) {
                    MeshIndex = Tetromino_Mesh.size() - 1;

                    float x = (Tetromino[Tetromino_Type].Arr[j].x + Pos_X);
                    float y = (Tetromino[Tetromino_Type].Arr[j].y + Pos_Y);
                    Tetromino_Mesh[MeshIndex].Arr.push_back({ x, y });
                    Tetromino_Mesh[MeshIndex].Colour = Tetromino[Tetromino_Type].Colour;
                }

                Pos_X = ScreenWidth() / 2;
                Pos_Y = 28;
                Tetromino_Type = Next_Type;

                Next_Type = rand() % 7;

                if (!CheckToEraseCompleteLine()) cout << "";

                cont_3 = 0;

                if (GameOver()) {

                    cout << "Score= " << score << endl;

                    Tetromino_Mesh.clear();
                    Tetromino.clear();
                    Next_Tetromino.clear();
                    HasBeenPressed = false;
                    cont = 0;
                    Speed = 60;
                    score = 0;
                    CanSwitch = true;
                    LineasCompletadas = 0;
                }
            }
        }

    }

    void SaveTetromino() {
        if (HasBeenPressed and GetKey(olc::SHIFT).bPressed and SavedTypeDoesFit() and CanSwitch) {
            int n = Saved_Type;
            Saved_Type = Tetromino_Type;
            Tetromino_Type = n;
            CanSwitch = false;
        }

        if (!HasBeenPressed) {
            if (GetKey(olc::SHIFT).bPressed and CanSwitch) {

                HasBeenPressed = true;

                Saved_Type = Tetromino_Type;
                Tetromino_Type = Next_Type;
                Next_Type = rand() % 7;
                CanSwitch = false;
            }
        }

    }

    void DrawTetromino() {
        if (cont < 1) {

            Tetromino.push_back({});
            Tetromino.push_back({});
            Tetromino.push_back({});
            Tetromino.push_back({});
            Tetromino.push_back({});
            Tetromino.push_back({});
            Tetromino.push_back({});



            Tetromino[0].Arr.push_back({ 8, 0 });
            Tetromino[0].Arr.push_back({ 8, 4 });
            Tetromino[0].Arr.push_back({ 12, 4 });
            Tetromino[0].Arr.push_back({ 8, 8 });
            Tetromino[0].Colour = olc::MAGENTA;

            Tetromino[1].Arr.push_back({ 0, 0 });
            Tetromino[1].Arr.push_back({ 4, 0 });
            Tetromino[1].Arr.push_back({ 8, 0 });
            Tetromino[1].Arr.push_back({ 12, 0 });
            Tetromino[1].Colour = olc::BLUE;

            Tetromino[2].Arr.push_back({ 0,0 });
            Tetromino[2].Arr.push_back({ 4,0 });
            Tetromino[2].Arr.push_back({ 8,0 });
            Tetromino[2].Arr.push_back({ 0,4 });
            Tetromino[2].Colour = olc::DARK_BLUE;

            Tetromino[3].Arr.push_back({ 4, 0 });
            Tetromino[3].Arr.push_back({ 8, 0 });
            Tetromino[3].Arr.push_back({ 12, 0 });
            Tetromino[3].Arr.push_back({ 12, 4 });
            Tetromino[3].Colour = olc::CYAN;

            Tetromino[4].Arr.push_back({ 8, 0 });
            Tetromino[4].Arr.push_back({ 8, 4 });
            Tetromino[4].Arr.push_back({ 12, 0 });
            Tetromino[4].Arr.push_back({ 12, 4 });
            Tetromino[4].Colour = olc::YELLOW;

            Tetromino[5].Arr.push_back({ 4, 4 });
            Tetromino[5].Arr.push_back({ 8, 4 });
            Tetromino[5].Arr.push_back({ 8, 0 });
            Tetromino[5].Arr.push_back({ 12, 0 });
            Tetromino[5].Colour = olc::GREEN;

            Tetromino[6].Arr.push_back({ 4, 0 });
            Tetromino[6].Arr.push_back({ 8, 0 });
            Tetromino[6].Arr.push_back({ 8, 4 });
            Tetromino[6].Arr.push_back({ 12, 4 });
            Tetromino[6].Colour = olc::RED;


            //----------------------------------

            Next_Tetromino.push_back({});
            Next_Tetromino.push_back({});
            Next_Tetromino.push_back({});
            Next_Tetromino.push_back({});
            Next_Tetromino.push_back({});
            Next_Tetromino.push_back({});
            Next_Tetromino.push_back({});



            Next_Tetromino[0].Arr.push_back({ 8, 0 });
            Next_Tetromino[0].Arr.push_back({ 8, 4 });
            Next_Tetromino[0].Arr.push_back({ 12, 4 });
            Next_Tetromino[0].Arr.push_back({ 8, 8 });
            Next_Tetromino[0].Colour = olc::MAGENTA;

            Next_Tetromino[1].Arr.push_back({ 0, 0 });
            Next_Tetromino[1].Arr.push_back({ 4, 0 });
            Next_Tetromino[1].Arr.push_back({ 8, 0 });
            Next_Tetromino[1].Arr.push_back({ 12, 0 });
            Next_Tetromino[1].Colour = olc::BLUE;

            Next_Tetromino[2].Arr.push_back({ 0,0 });
            Next_Tetromino[2].Arr.push_back({ 4,0 });
            Next_Tetromino[2].Arr.push_back({ 8,0 });
            Next_Tetromino[2].Arr.push_back({ 0,4 });
            Next_Tetromino[2].Colour = olc::DARK_BLUE;

            Next_Tetromino[3].Arr.push_back({ 4, 0 });
            Next_Tetromino[3].Arr.push_back({ 8, 0 });
            Next_Tetromino[3].Arr.push_back({ 12, 0 });
            Next_Tetromino[3].Arr.push_back({ 12, 4 });
            Next_Tetromino[3].Colour = olc::CYAN;

            Next_Tetromino[4].Arr.push_back({ 8, 0 });
            Next_Tetromino[4].Arr.push_back({ 8, 4 });
            Next_Tetromino[4].Arr.push_back({ 12, 0 });
            Next_Tetromino[4].Arr.push_back({ 12, 4 });
            Next_Tetromino[4].Colour = olc::YELLOW;

            Next_Tetromino[5].Arr.push_back({ 4, 4 });
            Next_Tetromino[5].Arr.push_back({ 8, 4 });
            Next_Tetromino[5].Arr.push_back({ 8, 0 });
            Next_Tetromino[5].Arr.push_back({ 12, 0 });
            Next_Tetromino[5].Colour = olc::GREEN;

            Next_Tetromino[6].Arr.push_back({ 4, 0 });
            Next_Tetromino[6].Arr.push_back({ 8, 0 });
            Next_Tetromino[6].Arr.push_back({ 8, 4 });
            Next_Tetromino[6].Arr.push_back({ 12, 4 });
            Next_Tetromino[6].Colour = olc::RED;

            OffSet_X_NextTetromino = ((((ScreenWidth() - FieldWidth) / 2) - 2) + FieldWidth + Block_Size) + 1;
            OffSet_Y_NextTetromino = ((ScreenHeight() - FieldHeight) / 2) - 2;

            OffSet_X_SavedTetromino = (((ScreenWidth() - FieldWidth) / 2) - 2) - (5 * Block_Size);
            OffSet_Y_SavedTetromino = ((ScreenHeight() - FieldHeight) / 2) - 2;
        }

        for (int j = 0; j < Tetromino[Tetromino_Type].Arr.size(); j++) {
            int x = Tetromino[Tetromino_Type].Arr[j].x + Pos_X;
            int y = Tetromino[Tetromino_Type].Arr[j].y + Pos_Y;
            olc::Pixel Colour = Tetromino[Tetromino_Type].Colour;

            FillRect(x, y, Block_Size, Block_Size, Colour);
        }

        for (int i = 0; i < Tetromino_Mesh.size(); i++) {
            for (int j = 0; j < Tetromino_Mesh[i].Arr.size(); j++) {
                int x = Tetromino_Mesh[i].Arr[j].x;
                int y = Tetromino_Mesh[i].Arr[j].y;
                olc::Pixel Colour = Tetromino_Mesh[i].Colour;

                FillRect(x, y, Block_Size, Block_Size, Colour);
            }
        }

        for (int j = 0; j < Next_Tetromino[Next_Type].Arr.size(); j++) {
            int x = Next_Tetromino[Next_Type].Arr[j].x + OffSet_X_NextTetromino;
            int y = Next_Tetromino[Next_Type].Arr[j].y + OffSet_Y_NextTetromino;
            int x1 = x + Block_Size;
            int y1 = y + Block_Size;
            olc::Pixel Colour = Next_Tetromino[Next_Type].Colour;

            FillRect(x, y, Block_Size, Block_Size, Colour);
        }

        if (HasBeenPressed == true) {

            for (int j = 0; j < Next_Tetromino[Saved_Type].Arr.size(); j++) {
                int x = Next_Tetromino[Saved_Type].Arr[j].x + OffSet_X_SavedTetromino;
                int y = Next_Tetromino[Saved_Type].Arr[j].y + OffSet_Y_SavedTetromino;
                int x1 = x + Block_Size;
                int y1 = y + Block_Size;
                olc::Pixel Colour = Next_Tetromino[Saved_Type].Colour;

                FillRect(x, y, Block_Size, Block_Size, Colour);
            }

            

        }

        auto transpColor = olc::Pixel(0, 0, 0, 150);
        for (int i = OffSet_Y_SavedTetromino; i < OffSet_Y_SavedTetromino + (4 * Block_Size) + 1; i = i + 4) {
            DrawLine(OffSet_X_SavedTetromino, i, OffSet_X_SavedTetromino + (4 * Block_Size), i, transpColor);
        }
        for (int i = OffSet_X_SavedTetromino; i < OffSet_X_SavedTetromino + (4 * Block_Size) + 1; i = i + 4) {
            DrawLine(i, OffSet_Y_SavedTetromino, i, OffSet_Y_SavedTetromino + (4 * Block_Size), transpColor);
        }

        for (int i = OffSet_Y_NextTetromino; i < OffSet_Y_NextTetromino + (4 * Block_Size) + 1; i = i + 4) {
            DrawLine(OffSet_X_NextTetromino, i, OffSet_X_NextTetromino + (4 * Block_Size), i, transpColor);
        }
        for (int i = OffSet_X_NextTetromino; i < OffSet_X_NextTetromino + (4 * Block_Size) + 1; i = i + 4) {
            DrawLine(i, OffSet_Y_NextTetromino, i, OffSet_Y_NextTetromino + (4 * Block_Size), transpColor);
        }
    }

    bool CheckToEraseCompleteLine() {
        int multiplication = 0;
        int cont = 0;
        for (int h = 28; h <= ((((ScreenHeight() - FieldHeight) / 2) - 2) + FieldHeight) - (2 * Block_Size); h = h + 4) {
            cont = 0;

            for (int a = (((ScreenWidth() - FieldWidth) / 2) - 2); a <= (((((ScreenWidth() - FieldWidth) / 2) - 2) + Block_Size) + FieldWidth - (3 * Block_Size)); a = a + 4) {

                for (int j = 0; j <= MeshIndex; j++) {
                    MeshTetrominoArraySize = Tetromino_Mesh[MeshIndex].Arr.size();
                    for (int k = 0; k < MeshTetrominoArraySize; k++) {

                        if (a == Tetromino_Mesh[j].Arr[k].x and h == Tetromino_Mesh[j].Arr[k].y) {
                            cont++;
                        }
                    }
                }
            }
            if (cont >= 13) {
                multiplication++;
                LineasCompletadas++;
                for (int j = 0; j <= MeshIndex; j++) {
                    score = score + (10 * multiplication);

                    MeshTetrominoArraySize = Tetromino_Mesh[MeshIndex].Arr.size();
                    for (int k = 0; k < MeshTetrominoArraySize; k++) {
                        float y = Tetromino_Mesh[j].Arr[k].y;
                        y = y + Block_Size;
                        if (Tetromino_Mesh[j].Arr[k].y < h) Tetromino_Mesh[j].Arr[k].y = y;
                        else if (Tetromino_Mesh[j].Arr[k].y == h) Tetromino_Mesh[j].Arr[k].y = ((((ScreenHeight() - FieldHeight) / 2) - 2) + FieldHeight) - Block_Size;
                    }
                }
            }
        }
        return false;
    }

    bool GameOver() {
        for (int j = 0; j <= MeshIndex; j++) {
            MeshTetrominoArraySize = Tetromino_Mesh[MeshIndex].Arr.size();
            for (int k = 0; k < MeshTetrominoArraySize; k++) {
                if (Tetromino_Mesh[j].Arr[k].y <= 32) return true;
            }
        }


        return false;
    }

    void GainSpeed() {
        switch (score) {
        case 5:
            Speed = 25;
            break;

        case 10:
            Speed = 20;
            break;

        case 20:
            Speed = 15;
            break;

        case 30:
            Speed = 10;
            break;

        case 40:
            Speed = 5;
            break;
        }
    }


    virtual bool OnUserCreate() {

        //gSoloud.init();

        Pos_X = (float(ScreenWidth()) / 2);

        sprFondo = new olc::Sprite("Sprites/senku.jpg");
        Fondo = new olc::Decal(sprFondo);

        Layer1 = CreateLayer();
        SetDrawTarget(Layer1);
        EnableLayer(Layer1, true);
        SetDrawTarget(nullptr);

        Layer2 = CreateLayer();
        SetDrawTarget(Layer2);
        EnableLayer(Layer2, true);
        SetDrawTarget(nullptr);

        //TitleMusic.load("Audio/TetrisTheme.wav");

        //gSoloud.play(TitleMusic);

        return true;
    }

    virtual bool OnUserUpdate(float fElapsedTime) {

        double dExpectedTime = 1.0f / 60.0f;
        if (dExpectedTime >= GetElapsedTime()) Sleep((dExpectedTime - GetElapsedTime()) * 1000);

        //PlaySample(nSample);

        Clear(olc::BLANK);
        Puntaje.clear();

        SetDrawTarget(Layer1);
        Clear(olc::BLANK);
        auto transpColor = olc::Pixel(255, 255, 255, 30);
        FillRect({ (((ScreenWidth() - FieldWidth) / 2) - 2) + Block_Size , (((ScreenHeight() - FieldHeight) / 2) - 2) }, { 53, 97 }, transpColor);
        FillRect({ OffSet_X_SavedTetromino, OffSet_Y_SavedTetromino }, { (4 * Block_Size) , (4 * Block_Size) }, transpColor);
        FillRect({ OffSet_X_NextTetromino, OffSet_Y_NextTetromino }, { (4 * Block_Size) , (4 * Block_Size) }, transpColor);
        FillRect({ 43, 135 }, { 70 , 30 }, transpColor);
        SetDrawTarget(nullptr);

        SetDrawTarget(Layer2);
        SetPixelMode(olc::Pixel::ALPHA);
        DrawDecal({ -60,0 }, Fondo, { 0.08,0.08 });
        SetPixelMode(olc::Pixel::NORMAL);
        SetDrawTarget(nullptr);

        SaveTetromino();

        if (cont_4 > (Speed/(GetElapsedTime()*25)) and DoesPieceFitDown() and DoesPieceFit3()) {
            Pos_Y = Pos_Y + 4;
            cont_4 = 0;
        }

        if (NextRotationDoesFit()) {
            Rotate_Tetromino();
        }

        MoveTetromino();

        while (!DoesPieceFit()) {
            Pos_X -= 4;
        }
        while (!DoesPieceFit2()) {
            Pos_X += 4;
        }

        MeshTetrominos();

        DrawTetromino();

        DrawField();

        GainSpeed();


        UserTetrominoArraySize = Tetromino[Tetromino_Type].Arr.size();
        MeshIndex = Tetromino_Mesh.size() - 1;

        if (HasBeenPressed) SavedArraySize = Next_Tetromino[Saved_Type].Arr.size();

        score = Tetromino_Mesh.size();
        PuntajeReal = LineasCompletadas*1000 + score * 100;
        
        Puntaje += to_string(PuntajeReal);

        DrawString({ 48, 140 }, "Puntaje:", olc::BLACK);
        DrawString({ 50, 150 }, Puntaje, olc::BLACK);

        cont++;
        cont_4++;
        return true;
    }

    virtual bool OnUserDestroy()
    {
        //DestroyAudio();
        return true;
    }

};


int main() {

    Juego Demo;

    if (Demo.Construct(160, 160, 4, 4))
        Demo.Start();

    else cout << "Construct Failed";
}
