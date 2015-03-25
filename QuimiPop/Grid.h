//
//  Grid.h
//  QuimiPop
//
//  Created by Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz on 3/22/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz. All rights reserved.
//

#ifndef __QuimiPop__Grid__
#define __QuimiPop__Grid__

#include <time.h>
#include <stdlib.h>

#include "GLTexture.h"
#include "ResourceManager.h"

// Elements
const int HYDROGEN = 0;
const int OXYGEN = 1;
const int CARBON = 2;
const int SULFUR = 3;
const int NITROGEN = 4;

// Molecules
const int SUGAR = 10;
const int WATER = 11;
const int CARBON_DIOXIDE = 12;
const int METHANE = 13;
const int NITROUS_OXIDE = 14;
const int SULFURIC_ACID = 15;

// Kryptonite
const int KRYPTONITE = 99;

// Molecule Structures
const int arrSugar1[4] = {0,1,2,0};
const int arrSugar2[4] = {0,2,1,0};
const int arrWater[3] = {0,1,0};
const int arrCarbonDioxide[3] = {1,2,1};
const int arrMethane1[4] = {0,2,0,0};
const int arrMethane2[4] = {0,0,2,0};
const int arrNitrousOxide1[3] = {4,4,1};
const int arrNitrousOxide2[3] = {1,4,4};
const int arrSulfuricAcid1[5] = {0,1,3,1,0};
const int arrSulfuricAcid2[5] = {1,0,3,1,0};
const int arrSulfuricAcid3[5] = {1,0,3,0,1};
const int arrSulfuricAcid4[5] = {0,1,3,0,1};

// Constants
const int grid_length = 8;
const int max_struct_length = 5;

// Preset grids
const int grid1[grid_length][grid_length] = {{2,0,4,2,0,4,4,0},{4,3,1,2,3,0,3,2},{3,0,2,1,4,2,1,3},{0,99,3,2,0,1,4,2},{0,4,2,2,0,2,0,2},{3,2,1,99,1,3,0,0},{1,0,0,2,1,99,0,3},{0,99,1,1,0,4,2,1}};

class Grid {
public:
    void init();
    
    void moveGrid(int colOrRen, int index, int offset);
    bool checkMolecule(int colOrRen, int x, int y, const int* arrMolecule, int size);
    void rearrangeMolecule(int colOrRen, int x, int y, int size, int type);
    void deleteMolecule(int colOrRen, int x, int y, int size, int type);
    void checkGrid(int colOrRen, int pos);
    
    GLTexture getTileTexture(int row, int col);
    
private:
    int _gameGrid[grid_length][grid_length];
};

#endif /* defined(__QuimiPop__Grid__) */
