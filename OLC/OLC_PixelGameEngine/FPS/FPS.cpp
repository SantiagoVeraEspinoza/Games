//
//  main.cpp
//  FPS
//
//  Created by Santiago Vera on 03/08/20.
//  Copyright © 2020 Mistic_Lion. All rights reserved.
//

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

class Demo : public olc::PixelGameEngine {

private:

    wstring Map;

    float fPlayerX = 8.0f;
    float fPlayerY = 8.0f;
    float fPlayerAngle = 0.0f;


    int nMapWidth = 32;
    int nMapHeight = 32;

    float fFOV = M_PI / 5.0f;

    float fDepthDistance = 10.0f;

public:

    Demo() {

    }

    ~Demo() {

    }

    virtual bool OnUserCreate() {

        Map += L"################################";
        Map += L"#..............##..............#";
        Map += L"#..............##..............#";
        Map += L"#..............##..............#";
        Map += L"#..............#...............#";
        Map += L"#.......##.....#.....#####.....#";
        Map += L"#..............#.....#.........#";
        Map += L"#....#...#...........#...#.....#";
        Map += L"#....#...#...............#.....#";
        Map += L"#....#...#...........#...#.....#";
        Map += L"#....#..##...........#####.....#";
        Map += L"#..............................#";
        Map += L"#..............................#";
        Map += L"#......##########..............#";
        Map += L"#..............................#";
        Map += L"#...............#######....#####";
        Map += L"#######..........##.........####";
        Map += L"#..............................#";
        Map += L"#...............#..............#";
        Map += L"#...............#..............#";
        Map += L"#..............................#";
        Map += L"#....##................###.....#";
        Map += L"#....#.........#...............#";
        Map += L"#....#...#...........#...#.....#";
        Map += L"#....#...#...........#...#.....#";
        Map += L"#....#...#...........#...#.....#";
        Map += L"#....#####...........#####.....#";
        Map += L"#..............................#";
        Map += L"#..............................#";
        Map += L"#..............................#";
        Map += L"#..............................#";
        Map += L"################################";

        return true;
    }

    void DrawWall() {

        for (int x = 0; x < ScreenWidth(); x++) {

            float fRayAngle = (fPlayerAngle - fFOV / 2.0f) + (((float)x / (float)ScreenWidth()) * fFOV);

            float fDistanceToWall = 0.0f;
            bool bHitWall = false;

            float fEyeX = sinf(fRayAngle);
            float fEyeY = cosf(fRayAngle);

            while (!bHitWall and fDistanceToWall < fDepthDistance) {

                fDistanceToWall += 0.1f;

                int nTestX = (int)(fPlayerX + fEyeX * fDistanceToWall);
                int nTestY = (int)(fPlayerY + fEyeY * fDistanceToWall);

                if (nTestX < 0 or nTestX >= nMapWidth or nTestY < 0 or nTestY >= nMapHeight) {
                    bHitWall = true;
                    fDistanceToWall = fDepthDistance;
                }
                else {
                    if (Map[nTestY * nMapWidth + nTestX] == '#') {
                        bHitWall = true;
                    }
                }
            }

            int nCeiling = (float)(ScreenHeight() / 2.0) - (ScreenHeight() / ((float)fDistanceToWall));
            int nFloor = ScreenHeight() - nCeiling;

            olc::Pixel nShade = olc::WHITE;

            if (fDistanceToWall < fDepthDistance / 3.0f) nShade = olc::WHITE;
            else if (fDistanceToWall < fDepthDistance / 2.0f) nShade = olc::GREY;
            else if (fDistanceToWall < fDepthDistance) nShade = olc::DARK_GREY;

            for (int y = 0; y < ScreenHeight(); y++) {
                if (y < nCeiling) Draw(x, y, olc::BLACK);
                else if (y >= nCeiling and y <= nFloor) Draw(x, y, nShade);
                else Draw(x, y, olc::BLACK);

            }

        }

    }

    void MovePlayer(float Speed = 1) {
        if (GetKey(olc::W).bHeld) {
            fPlayerX += sinf(fPlayerAngle) * Speed * GetElapsedTime() * 10;
            fPlayerY += cosf(fPlayerAngle) * Speed * GetElapsedTime() * 10;

            if (Map[(int)fPlayerY * nMapWidth + (int)fPlayerX] == '#') {
                fPlayerX -= sinf(fPlayerAngle) * Speed * GetElapsedTime() * 10;
                fPlayerY -= cosf(fPlayerAngle) * Speed * GetElapsedTime() * 10;
            }
        }
        if (GetKey(olc::S).bHeld) {
            fPlayerX -= sinf(fPlayerAngle) * Speed * GetElapsedTime() * 10;
            fPlayerY -= cosf(fPlayerAngle) * Speed * GetElapsedTime() * 10;

            if (Map[(int)fPlayerY * nMapWidth + (int)fPlayerX] == '#') {
                fPlayerX += sinf(fPlayerAngle) * Speed * GetElapsedTime() * 10;
                fPlayerY += cosf(fPlayerAngle) * Speed * GetElapsedTime() * 10;
            }
        }
        if (GetKey(olc::A).bHeld) {
            fPlayerX -= cosf(fPlayerAngle) * Speed * GetElapsedTime() * 5;
            fPlayerY += sinf(fPlayerAngle) * Speed * GetElapsedTime() * 5;

            if (Map[(int)fPlayerY * nMapWidth + (int)fPlayerX] == '#') {
                fPlayerX += cosf(fPlayerAngle) * Speed * GetElapsedTime() * 5;
                fPlayerY -= sinf(fPlayerAngle) * Speed * GetElapsedTime() * 5;
            }
        }
        if (GetKey(olc::D).bHeld) {
            fPlayerX += cosf(fPlayerAngle) * Speed * GetElapsedTime() * 5;
            fPlayerY -= sinf(fPlayerAngle) * Speed * GetElapsedTime() * 5;

            if (Map[(int)fPlayerY * nMapWidth + (int)fPlayerX] == '#') {
                fPlayerX -= cosf(fPlayerAngle) * Speed * GetElapsedTime() * 5;
                fPlayerY += sinf(fPlayerAngle) * Speed * GetElapsedTime() * 5;
            }
        }
        if (GetKey(olc::LEFT).bHeld) {
            fPlayerAngle -= (Speed * GetElapsedTime());
        }
        if (GetKey(olc::RIGHT).bHeld) {
            fPlayerAngle += (Speed * GetElapsedTime());
        }
    }


    void GameMethod() {
        Clear(olc::BLACK);

        DrawWall();
        MovePlayer();

    }

    virtual bool OnUserUpdate(float fElapsedTime) {
        double dExpectedTime = 1.0f / 60.0f;
        if (dExpectedTime >= GetElapsedTime()) Sleep((dExpectedTime - GetElapsedTime()) * 1000);

        GameMethod();

        return true;
    }
};


int main() {

    Demo Juego;

    if (Juego.Construct(320, 240, 4, 4)) {
        Juego.Start();
    }

}
