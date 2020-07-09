//
//  main.cpp
//  Tetris
//
//  Created by Santiago Vera on 07/07/20.
//  Copyright © 2020 Mistic_Lion. All rights reserved.
//

#include <iostream>
#include <vector>
#include <math.h>
#include "olcConsoleGameEngineSDL.h"
using namespace std;

class Juego : public olcConsoleGameEngine{
private:
    
    int FieldWidth=60;
    int FieldHeight=100;
    int cont=0;
    int Tetromino_Type=2;
    
    int const static Block_Size=4;
    
    struct Coord{
        float x,y;
        int x1=x+Block_Size;
        int y1=y+Block_Size;
    };
    
    struct Cubes{
        vector <Coord> Arr;
        short Colour;
    };
    
    vector <Cubes> Tetromino;
    vector <Cubes> Tetromino_Mesh;
    
public:
    Juego(){}
    ~Juego(){}
    
    void DrawField(){
        int BorderField_OOB_X = (ScreenWidth()-FieldWidth)/2;
        int BorderField_OOB_Y = (ScreenHeight()-FieldHeight)/2;
        
        int x1=BorderField_OOB_X;
        int y1=BorderField_OOB_Y;
        int x2=BorderField_OOB_X+Block_Size;
        int y2=BorderField_OOB_Y+FieldHeight;
        int x3=x2;
        int y3=y2-Block_Size;
        int x4=x2+FieldWidth-Block_Size;
        int y4=y2;
        int x5=x4-Block_Size;
        int y5=y1;
        int x6=x4;
        int y6=y4;
        
        Fill(x1,y1,x2,y2,PIXEL_SOLID,FG_WHITE);
        Fill(x3,y3,x4,y4,PIXEL_SOLID,FG_WHITE);
        Fill(x5,y5,x6,y6,PIXEL_SOLID,FG_WHITE);
    }
    
    void Rotate_Tetromino(){
        if(GetKey(VK_SPACE).bPressed){
                    for(int i=0; i<Tetromino[Tetromino_Type].Arr.size(); i++){
                        int x=Tetromino[Tetromino_Type].Arr[i].x;
                        int y=Tetromino[Tetromino_Type].Arr[i].y;
                        
                        float cx=6, cy=6;
                        
                        float PM_AC_X=(x+cx)/2, PM_AC_Y=(y+cy)/2;
                        
                        float m=-1*(pow(((y-cy)/(x-cx)),-1));
                        
                        float DM_AC=pow((pow(((pow((x-cx),2)+pow((y-cy),2))),0.5)/2),2);
                        
                        float PP_Y_INCOG=m;
                        float PP_Y_INDEP=(m*PM_AC_X*-1)+PM_AC_Y;
                        
                        float a=1+pow(PP_Y_INCOG, 2);
                        float b=((PM_AC_X*-2)+((PM_AC_Y-PP_Y_INDEP)*(-2*PP_Y_INCOG)));
                        float c=(pow(PM_AC_X,2)+pow((PM_AC_Y-PP_Y_INDEP),2))-DM_AC;
                        
                        float x1=(((-1*b)+pow((pow(b,2)-(4*a*c)),0.5))/(2*a));
                        float y1=((PP_Y_INCOG*x1)+PP_Y_INDEP);
                        x1=x1+(x1-x);
                        y1=y1+(y1-y);
                        
                        
                        
                        Tetromino[Tetromino_Type].Arr[i].x=round(x1);
                        Tetromino[Tetromino_Type].Arr[i].y=round(y1);
                        cout << x1 << "--------------------" << endl << Tetromino[Tetromino_Type].Arr[i].x << endl << Tetromino[Tetromino_Type].Arr[i].y << endl << endl;
            }
        }
        
        
    }
    
    void DrawTetromino(){
            for(int j=0;j<Tetromino[Tetromino_Type].Arr.size();j++){
                Fill(Tetromino[Tetromino_Type].Arr[j].x,Tetromino[Tetromino_Type].Arr[j].y, Tetromino[Tetromino_Type].Arr[j].x1, Tetromino[Tetromino_Type].Arr[j].y1, PIXEL_SOLID, Tetromino[Tetromino_Type].Colour);
            }
    }
    
    
    virtual bool OnUserCreate(){
        
        Tetromino.push_back({});
        Tetromino.push_back({});
        Tetromino.push_back({});
        Tetromino.push_back({});
        Tetromino.push_back({});
        Tetromino.push_back({});
        Tetromino.push_back({});
        
        
        
        Tetromino[0].Arr.push_back({8, 0});
        Tetromino[0].Arr.push_back({8, 4});
        Tetromino[0].Arr.push_back({12, 4});
        Tetromino[0].Arr.push_back({8, 8});
        Tetromino[0].Colour=FG_MAGENTA;
        
        Tetromino[1].Arr.push_back({0, 0});
        Tetromino[1].Arr.push_back({4, 0});
        Tetromino[1].Arr.push_back({8, 0});
        Tetromino[1].Arr.push_back({12, 0});
        Tetromino[1].Colour=FG_BLUE;
        
        Tetromino[2].Arr.push_back({0,0});
        Tetromino[2].Arr.push_back({4,0});
        Tetromino[2].Arr.push_back({8,0});
        Tetromino[2].Arr.push_back({0,4});
        Tetromino[2].Colour=FG_DARK_BLUE;
        
        Tetromino[3].Arr.push_back({4, 4});
        Tetromino[3].Arr.push_back({8, 4});
        Tetromino[3].Arr.push_back({12, 4});
        Tetromino[3].Arr.push_back({12, 0});
        Tetromino[3].Colour=FG_CYAN;
        
        Tetromino[4].Arr.push_back({8, 0});
        Tetromino[4].Arr.push_back({8, 4});
        Tetromino[4].Arr.push_back({12, 0});
        Tetromino[4].Arr.push_back({12, 4});
        Tetromino[4].Colour=FG_YELLOW;
        
        Tetromino[5].Arr.push_back({4, 4});
        Tetromino[5].Arr.push_back({8, 4});
        Tetromino[5].Arr.push_back({8, 0});
        Tetromino[5].Arr.push_back({12, 0});
        Tetromino[5].Colour=FG_GREEN;
        
        Tetromino[6].Arr.push_back({4, 0});
        Tetromino[6].Arr.push_back({8, 0});
        Tetromino[6].Arr.push_back({8, 4});
        Tetromino[6].Arr.push_back({12, 4});
        Tetromino[6].Colour=FG_RED;
        
        return true;
    }
    
    virtual bool OnUserUpdate(float fElapsedTime){
        
        Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);
        
        DrawField();
        
        Rotate_Tetromino();
        
        DrawTetromino();
        
        cont++;
        return true;
    }
    
};


int main() {
    
    Juego Demo;
    
    if(Demo.ConstructConsole(160, 160, 4, 4)){
        Demo.Start();
    }
    
    else cout << "Construct Failed";
}
