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
    int cont_2=0;
    int Tetromino_Type=1;
    
    int const static Block_Size=4;
    
    struct Coord{
        float x,y;
    };
    
    struct Cubes{
        vector <Coord> Arr;
        short Colour;
    };
    
    vector <Cubes> Tetromino;
    vector <Cubes> Tetromino_Mesh;
    
    
    float Pos_X=ScreenWidth()-8;
    float Pos_Y=28;
    
public:
    Juego(){}
    ~Juego(){}
    
    void DrawField(){
        int BorderField_OOB_X = ((ScreenWidth()-FieldWidth)/2)-2;
        int BorderField_OOB_Y = ((ScreenHeight()-FieldHeight)/2)-2;
        
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
        int ID[8];
        if(GetKey(VK_SPACE).bPressed and Tetromino_Type!=4 and Tetromino_Type!=1){
            
                    for(int i=0; i<Tetromino[Tetromino_Type].Arr.size(); i++){
                        int x=(Tetromino[Tetromino_Type].Arr[i].x/4);
                        int y=(Tetromino[Tetromino_Type].Arr[i].y/4);
                        
                        ID[i]=3-y+(4*x);
                        
                        y=(ID[i]/4);
                        x=ID[i]-(4*y);
                        
                        Tetromino[Tetromino_Type].Arr[i].x=x*4;
                        Tetromino[Tetromino_Type].Arr[i].y=y*4;
                        }
        
        }
        else if (GetKey(VK_SPACE).bPressed and Tetromino_Type==1){
            
            if(cont_2==0){
                for(int i=0; i<Tetromino[Tetromino_Type].Arr.size(); i++){
                    int x=(Tetromino[Tetromino_Type].Arr[i].x/4);
                    int y=(Tetromino[Tetromino_Type].Arr[i].y/4);
                    ID[i]=3-y+(4*x);
                    
                    y=(ID[i]/4);
                    x=ID[i]-(4*y);
                    
                    Tetromino[Tetromino_Type].Arr[i].x=x*4;
                    Tetromino[Tetromino_Type].Arr[i].y=y*4;
                }
                cont_2=1;
            }
            else if(cont_2==1){
                for(int i=0; i<Tetromino[Tetromino_Type].Arr.size(); i++){
                    int x=(Tetromino[Tetromino_Type].Arr[i].x/4);
                    int y=(Tetromino[Tetromino_Type].Arr[i].y/4);
                    
                    ID[i]=12+y-(x*4);
                    
                    y=(ID[i]/4);
                    x=ID[i]-(4*y);
                    
                    Tetromino[Tetromino_Type].Arr[i].x=x*4;
                    Tetromino[Tetromino_Type].Arr[i].y=y*4;
                }
                cont_2=0;
            }
        }
    }
    
    bool DoesPieceFit(){
        for (int i=0; i<Tetromino[Tetromino_Type].Arr.size(); i++){
            if((Tetromino[Tetromino_Type].Arr[i].x+Pos_X)>=(((((ScreenWidth()-FieldWidth)/2)-2)+Block_Size)+FieldWidth-(2*Block_Size))-Block_Size)return false;
        }
        
        return true;
    }
    
    bool DoesPieceFit2(){
        for (int i=0; i<Tetromino[Tetromino_Type].Arr.size(); i++){
            if((Tetromino[Tetromino_Type].Arr[i].x+Pos_X)<=(((ScreenWidth()-FieldWidth)/2)-2)+Block_Size) return false;
        }
        return true;
    }
    
    bool DoesPieceFit3(){
        for (int i=0; i<Tetromino[Tetromino_Type].Arr.size(); i++){
            if((Tetromino[Tetromino_Type].Arr[i].y+Pos_Y)>=((((ScreenHeight()-FieldHeight)/2)-2)+FieldHeight)-(2*Block_Size)) return false;
        }
        return true;
    }
    
    void MoveTetromino(){
        if(GetKey(VK_RIGHT).bPressed and DoesPieceFit()){
            Pos_X=Pos_X+Block_Size;
            cout << "X= " << Pos_X << endl;
        }
        
        if(GetKey(VK_LEFT).bPressed and DoesPieceFit2()){
            Pos_X=Pos_X-Block_Size;
            cout << "X= " << Pos_X << endl;
        }
        
        if(GetKey(VK_DOWN).bPressed and DoesPieceFit3()){
            Pos_Y=Pos_Y+Block_Size;
            cout << "Y= " << Pos_Y << endl;
        }
    }
    
    void DrawTetromino(){
        if(cont<1){
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
        }
        
            for(int j=0;j<Tetromino[Tetromino_Type].Arr.size();j++){
                int x=Tetromino[Tetromino_Type].Arr[j].x+Pos_X;
                int y=Tetromino[Tetromino_Type].Arr[j].y+Pos_Y;
                int x1=x+Block_Size;
                int y1=y+Block_Size;
                short Colour=Tetromino[Tetromino_Type].Colour;
                
                Fill(x,y,x1,y1, PIXEL_SOLID, Colour);
            }
    }
    
    
    virtual bool OnUserCreate(){
        
        return true;
    }
    
    virtual bool OnUserUpdate(float fElapsedTime){
        
        Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);
        
        DrawField();
        
        if(Pos_X>(((ScreenWidth()-FieldWidth)/2)-2) and Pos_X+(3*Block_Size)<(((((ScreenWidth()-FieldWidth)/2)-2)+Block_Size)+FieldWidth-(2*Block_Size)) and Pos_Y+(Block_Size*4)<((((ScreenHeight()-FieldHeight)/2)-2)+FieldHeight)){
        Rotate_Tetromino();
        }
        
        MoveTetromino();
        
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
