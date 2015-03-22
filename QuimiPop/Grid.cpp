//
//  Grid.cpp
//  QuimiPop
//
//  Created by Eduardo Alberto Sanchez Alvarado on 3/22/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado. All rights reserved.
//

#include "Grid.h"

void Grid::init() {
    for (int row = 0; row < grid_length; row++) {
        for (int col = 0; col < grid_length; col++) {
            _gameGrid[row][col] = grid1[row][col];
        }
    }
}

void Grid::moveGrid(int colOrRen, int index, int offset) {
    if (offset == 0) {
        return;
    }
    int arrOriginal[grid_length];
    
    switch (colOrRen) {
        //caso del cambio de renglon
        case 1:
            for (int a = 0; a < grid_length; a++) {
                arrOriginal[a] = _gameGrid[index][a];
            }
            for (int i = 0; i < grid_length; i++) {
                _gameGrid[index][(i + offset + grid_length) % grid_length] = arrOriginal[i];
            }
            break;
        //caso para el cambio de columna
        case 0:
            for (int a = 0; a < grid_length; a++) {
                arrOriginal[a] = _gameGrid[a][index];
            }
            for (int i = 0; i < grid_length; i++) {
                _gameGrid[(i + offset + grid_length) % grid_length][index] = arrOriginal[i];
            }
            break;
    }
}

bool Grid::checkMolecule(int colOrRen, int x, int y, const int *arrMolecule, int size) {
    switch (colOrRen) {
        case 0:
            for (int i = 0; i < size; i++) {
                if ((y + i) >= grid_length || arrMolecule[i] != _gameGrid[x][y + i] || arrMolecule[size - 1 - i] != _gameGrid[x][y + i]) {
                    return false;
                }
            }
            break;
            
        case 1:
            for (int i = 0; i < size; i++) {
                if ((x + i) >= grid_length || arrMolecule[i] != _gameGrid[x + i][y] || arrMolecule[size - 1 - i] != _gameGrid[x + 1][y]) {
                    return false;
                }
            }
            break;
    }
    return true;
}

void Grid::rearrangeMolecule(int colOrRen, int x, int y, int size, int type) {
    switch(colOrRen) {
        case 0:
            for (int j = y + 1; j < y + size; j++) {
                for (int i = x; i > 1; i--) {
                    _gameGrid[i][j] = _gameGrid[i - 1][j];
                }
                _gameGrid[0][j] = rand() % 5;
            }
            break;
            
        case 1:
            for (int i = 0; i < x; i++) {
                _gameGrid[x + size - 2 - i][y] = _gameGrid[x - 1 - i][y];
            }
            for (int i = 0; i < size - 1; i++) {
                _gameGrid[i][y] = rand() % 5;
            }
            break;
    }
}

void Grid::deleteMolecule(int colOrRen, int x, int y, int size, int type) {
    switch(colOrRen) {
        case 0:
            _gameGrid[x][y] = type;
            for (int i = 1; i < size; i++) {
                _gameGrid[x][y+i] = -1;
            }
            break;
        case 1:
            _gameGrid[x+size-1][y] = type;
            for (int i = x + size - 2; i > x - 1; i--) {
                _gameGrid[i][y] = -1;
            }
            break;
    }
    
    rearrangeMolecule(colOrRen, x, y, size, type);
}

void Grid::checkGrid(int colOrRen, int pos) {
    switch (colOrRen) {
    //caso si se movio la columna
    case 0:
        for (int i = 0; i < grid_length; i++) {
            int inf_limit = (pos - max_struct_length < 0)? 0 : pos - max_struct_length;
            int top_limit = (pos + max_struct_length > grid_length)? grid_length : pos + max_struct_length;
            for (int j = inf_limit; j < top_limit; j++) {
                if (checkMolecule(colOrRen, i, j, arrSulfuricAcid1, 5)) {
                    deleteMolecule(colOrRen, i, j, 5, 15);
                }
                if (checkMolecule(colOrRen, i, j, arrSulfuricAcid2, 5)) {
                    deleteMolecule(colOrRen, i, j, 5, 15);
                }
                if (checkMolecule(colOrRen, i, j, arrSulfuricAcid3, 5)) {
                    deleteMolecule(colOrRen, i, j, 5, 15);
                }
                if (checkMolecule(colOrRen, i, j, arrSugar, 4)) {
                    deleteMolecule(colOrRen, i, j, 4, 10);
                }
                if (checkMolecule(colOrRen, i, j, arrMethane, 4)) {
                    deleteMolecule(colOrRen, i, j, 4, 13);
                }
                if (checkMolecule(colOrRen, i, j, arrCarbonDioxide, 3)) {
                    deleteMolecule(colOrRen, i, j, 3, 12);
                }
                if (checkMolecule(colOrRen, i, j, arrNitrousOxide, 3)) {
                    deleteMolecule(colOrRen, i, j, 3, 14);
                }
                if (checkMolecule(colOrRen, i, j, arrWater, 3)) {
                    deleteMolecule(colOrRen, i, j, 3, 11);
                }
            
            }
        }
        break;
    //caso si se movio el renglon
    case 1:
        for (int i = 0; i < grid_length; i++) {
            int inf_limit = (pos - max_struct_length <= 0)? 0 : pos - max_struct_length;
            int top_limit = (pos + max_struct_length > max_struct_length)? max_struct_length : pos + max_struct_length;
            for (int j = inf_limit; j < top_limit; j++) {
                if (checkMolecule(colOrRen, i, j, arrSulfuricAcid1, 5)) {
                    deleteMolecule(colOrRen, i, j, 5, 15);
                }
                if (checkMolecule(colOrRen, i, j, arrSulfuricAcid2, 5)) {
                    deleteMolecule(colOrRen, i, j, 5, 15);
                }
                if (checkMolecule(colOrRen, i, j, arrSulfuricAcid3, 5)) {
                    deleteMolecule(colOrRen, i, j, 5, 15);
                }
                if (checkMolecule(colOrRen, i, j, arrSugar, 4)) {
                    deleteMolecule(colOrRen, i, j, 4, 10);
                }
                if (checkMolecule(colOrRen, i, j, arrMethane, 4)) {
                    deleteMolecule(colOrRen, i, j, 4, 13);
                }
                if (checkMolecule(colOrRen, i, j, arrCarbonDioxide, 3)) {
                    deleteMolecule(colOrRen, i, j, 3, 12);
                }
                if (checkMolecule(colOrRen, i, j, arrNitrousOxide, 3)) {
                    deleteMolecule(colOrRen, i, j, 3, 14);
                }
                if (checkMolecule(colOrRen, i, j, arrWater, 3)) {
                    deleteMolecule(colOrRen, i, j, 3, 11);
                }
            }
        }
        break;
    }
}

GLTexture Grid::getTileTexture(int row, int col) {
    std::string filePath = "/Users/EduardoS/Documents/Programacion/XCode Projects/QuimiPop/QuimiPop/Textures/";
    switch (_gameGrid[row][col]) {
        case 0:
            filePath += "Hydrogen.png";
            break;
            
        case 1:
            filePath += "Oxygen.png";
            break;
            
        case 2:
            filePath += "Carbon.png";
            break;
            
        case 3:
            filePath += "Azufre.png";
            break;
            
        case 4:
            filePath += "Nitrogen.png";
            break;
            
        case 10:
            filePath += "Azucar.png";
            break;
            
        case 11:
            filePath += "Agua.png";
            break;
            
        case 12:
            filePath += "Carbon dioxide.png";
            break;
            
        case 13:
            filePath += "Methane.png";
            break;
            
        case 14:
            filePath += "Nitrous oxide.png";
            break;
            
        case 15:
            filePath += "Acido.png";
            break;
            
        case 9:
            filePath += "Kriptonita.png";
            break;
            
        default:
            filePath += "Kriptonita.png";
            break;
    }
    return ResourceManager::getTexture(filePath);
}