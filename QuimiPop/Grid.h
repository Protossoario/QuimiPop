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

enum Element {
    HYDROGEN = 0,
    OXYGEN = 1,
    CARBON = 2,
    SULFUR = 3,
    NITROGEN = 4,
    KRYPTONITE = 99
};

enum Molecule {
    SUGAR = 10,
    WATER = 11,
    CARBON_DIOXIDE = 12,
    METHANE = 13,
    NITROUS_OXIDE = 14,
    SULFURIC_ACID = 15
};

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
const int GRID_SIZE = 8;
const int MAX_MOLECULE_SIZE = 5;

// Preset grids
const int grid1[GRID_SIZE][GRID_SIZE] = {{2,0,4,2,0,4,4,0},{4,3,1,2,3,0,3,2},{3,0,2,1,4,2,1,3},{0,99,3,2,0,1,4,2},{0,4,2,2,0,2,0,2},{3,2,1,99,1,3,0,0},{1,0,0,2,1,99,0,3},{0,99,1,1,0,4,2,1}};

class Grid {
public:
    void init();
    
    void moveGrid(int colOrRen, int index, int offset);
    bool checkMolecule(int colOrRen, int x, int y, const int* arrMolecule, int size);
    void rearrangeMolecule(int colOrRen, int x, int y, int size, Molecule type);
    void deleteMolecule(int colOrRen, int x, int y, int size, Molecule type);
    void checkGrid(int colOrRen, int pos);
    
    GLTexture getTileTexture(int row, int col);
    
private:
    int m_gameGrid[GRID_SIZE][GRID_SIZE];
};

#endif /* defined(__QuimiPop__Grid__) */
