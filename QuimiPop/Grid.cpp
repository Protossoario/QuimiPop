//
//  Grid.cpp
//  QuimiPop
//
//  Created by Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz on 3/22/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz. All rights reserved.
//

#include "Grid.h"

void Grid::init() {
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            m_gameGrid[row][col] = grid1[row][col];
        }
    }
}

void Grid::moveGrid(int colOrRen, int index, int offset) {
    if (offset == 0) {
        return;
    }
    int arrOriginal[GRID_SIZE];
    
    switch (colOrRen) {
        //caso del cambio de renglon
        case 1:
            for (int a = 0; a < GRID_SIZE; a++) {
                arrOriginal[a] = m_gameGrid[index][a];
            }
            for (int i = 0; i < GRID_SIZE; i++) {
                m_gameGrid[index][(i + offset + GRID_SIZE) % GRID_SIZE] = arrOriginal[i];
            }
            break;
        //caso para el cambio de columna
        case 0:
            for (int a = 0; a < GRID_SIZE; a++) {
                arrOriginal[a] = m_gameGrid[a][index];
            }
            for (int i = 0; i < GRID_SIZE; i++) {
                m_gameGrid[(i + offset + GRID_SIZE) % GRID_SIZE][index] = arrOriginal[i];
            }
            break;
    }
}

bool Grid::checkMolecule(int colOrRen, int x, int y, const int *arrMolecule, int size) {
    switch (colOrRen) {
        case 0:
            for (int i = 0; i < size; i++) {
                if ((y + i) >= GRID_SIZE || arrMolecule[i] != m_gameGrid[x][y + i]) {
                    return false;
                }
            }
            break;
            
        case 1:
            for (int i = 0; i < size; i++) {
                if ((x + i) >= GRID_SIZE || arrMolecule[i] != m_gameGrid[x + i][y]) {
                    return false;
                }
            }
            break;
    }
    return true;
}

void Grid::rearrangeMolecule(int colOrRen, int x, int y, int size, Molecule type) {
    switch(colOrRen) {
        case 0:
            for (int j = y + 1; j < y + size; j++) {
                for (int i = x; i > 1; i--) {
                    m_gameGrid[i][j] = m_gameGrid[i - 1][j];
                }
                m_gameGrid[0][j] = rand() % 5;
            }
            break;
            
        case 1:
            for (int i = 0; i < x; i++) {
                m_gameGrid[x + size - 2 - i][y] = m_gameGrid[x - 1 - i][y];
            }
            for (int i = 0; i < size - 1; i++) {
                m_gameGrid[i][y] = rand() % 5;
            }
            break;
    }
}

void Grid::deleteMolecule(int colOrRen, int x, int y, int size, Molecule type) {
    switch(colOrRen) {
        case 0:
            m_gridObserver->formedMoleculeRow(x, y, size);
            m_gameGrid[x][y] = type;
            for (int i = 1; i < size; i++) {
                m_gameGrid[x][y+i] = EMPTY;
            }
            break;
        case 1:
            m_gridObserver->formedMoleculeCol(x, y, size);
            m_gameGrid[x+size-1][y] = type;
            for (int i = x + size - 2; i > x - 1; i--) {
                m_gameGrid[i][y] = EMPTY;
            }
            break;
    }
    
    rearrangeMolecule(colOrRen, x, y, size, type);
}

void Grid::checkGrid(int colOrRen, int pos) {
    switch (colOrRen) {
    //caso si se movio la columna
    case 0:
        for (int i = 0; i < GRID_SIZE; i++) {
            int inf_limit = (pos - MAX_MOLECULE_SIZE < 0)? 0 : pos - MAX_MOLECULE_SIZE;
            int top_limit = (pos + MAX_MOLECULE_SIZE > GRID_SIZE)? GRID_SIZE : pos + MAX_MOLECULE_SIZE;
            for (int j = inf_limit; j < top_limit; j++) {
                if (checkMolecule(colOrRen, i, j, arrSulfuricAcid1, 5)) {
                    deleteMolecule(colOrRen, i, j, 5, SULFURIC_ACID);
                }
                if (checkMolecule(colOrRen, i, j, arrSulfuricAcid2, 5)) {
                    deleteMolecule(colOrRen, i, j, 5, SULFURIC_ACID);
                }
                if (checkMolecule(colOrRen, i, j, arrSulfuricAcid3, 5)) {
                    deleteMolecule(colOrRen, i, j, 5, SULFURIC_ACID);
                }
                if (checkMolecule(colOrRen, i, j, arrSulfuricAcid4, 5)) {
                    deleteMolecule(colOrRen, i, j, 5, SULFURIC_ACID);
                }
                if (checkMolecule(colOrRen, i, j, arrSugar1, 4)) {
                    deleteMolecule(colOrRen, i, j, 4, SUGAR);
                }
                if (checkMolecule(colOrRen, i, j, arrSugar2, 4)) {
                    deleteMolecule(colOrRen, i, j, 4, SUGAR);
                }
                if (checkMolecule(colOrRen, i, j, arrMethane1, 4)) {
                    deleteMolecule(colOrRen, i, j, 4, METHANE);
                }
                if (checkMolecule(colOrRen, i, j, arrMethane2, 4)) {
                    deleteMolecule(colOrRen, i, j, 4, METHANE);
                }
                if (checkMolecule(colOrRen, i, j, arrCarbonDioxide, 3)) {
                    deleteMolecule(colOrRen, i, j, 3, CARBON_DIOXIDE);
                }
                if (checkMolecule(colOrRen, i, j, arrNitrousOxide1, 3)) {
                    deleteMolecule(colOrRen, i, j, 3, NITROUS_OXIDE);
                }
                if (checkMolecule(colOrRen, i, j, arrNitrousOxide2, 3)) {
                    deleteMolecule(colOrRen, i, j, 3, NITROUS_OXIDE);
                }
                if (checkMolecule(colOrRen, i, j, arrWater, 3)) {
                    deleteMolecule(colOrRen, i, j, 3, WATER);
                }
            
            }
        }
        break;
    //caso si se movio el renglon
    case 1:
        for (int i = 0; i < GRID_SIZE; i++) {
            int inf_limit = (pos - MAX_MOLECULE_SIZE <= 0)? 0 : pos - MAX_MOLECULE_SIZE;
            int top_limit = (pos + MAX_MOLECULE_SIZE > MAX_MOLECULE_SIZE)? MAX_MOLECULE_SIZE : pos + MAX_MOLECULE_SIZE;
            for (int j = inf_limit; j < top_limit; j++) {
                if (checkMolecule(colOrRen, i, j, arrSulfuricAcid1, 5)) {
                    deleteMolecule(colOrRen, i, j, 5, SULFURIC_ACID);
                }
                if (checkMolecule(colOrRen, i, j, arrSulfuricAcid2, 5)) {
                    deleteMolecule(colOrRen, i, j, 5, SULFURIC_ACID);
                }
                if (checkMolecule(colOrRen, i, j, arrSulfuricAcid3, 5)) {
                    deleteMolecule(colOrRen, i, j, 5, SULFURIC_ACID);
                }
                if (checkMolecule(colOrRen, i, j, arrSulfuricAcid4, 5)) {
                    deleteMolecule(colOrRen, i, j, 5, SULFURIC_ACID);
                }
                if (checkMolecule(colOrRen, i, j, arrSugar1, 4)) {
                    deleteMolecule(colOrRen, i, j, 4, SUGAR);
                }
                if (checkMolecule(colOrRen, i, j, arrSugar2, 4)) {
                    deleteMolecule(colOrRen, i, j, 4, SUGAR);
                }
                if (checkMolecule(colOrRen, i, j, arrMethane1, 4)) {
                    deleteMolecule(colOrRen, i, j, 4, METHANE);
                }
                if (checkMolecule(colOrRen, i, j, arrMethane2, 4)) {
                    deleteMolecule(colOrRen, i, j, 4, METHANE);
                }
                if (checkMolecule(colOrRen, i, j, arrCarbonDioxide, 3)) {
                    deleteMolecule(colOrRen, i, j, 3, CARBON_DIOXIDE);
                }
                if (checkMolecule(colOrRen, i, j, arrNitrousOxide1, 3)) {
                    deleteMolecule(colOrRen, i, j, 3, NITROUS_OXIDE);
                }
                if (checkMolecule(colOrRen, i, j, arrNitrousOxide2, 3)) {
                    deleteMolecule(colOrRen, i, j, 3, NITROUS_OXIDE);
                }
                if (checkMolecule(colOrRen, i, j, arrWater, 3)) {
                    deleteMolecule(colOrRen, i, j, 3, WATER);
                }
            }
        }
        break;
    }
}

std::string Grid::getTileTexturePath(int row, int col) {
    std::string filePath = "Textures/";
    switch (m_gameGrid[row][col]) {
        case HYDROGEN:
            filePath += "Hydrogen2.png";
            break;
            
        case OXYGEN:
            filePath += "Oxygen3.png";
            break;
            
        case CARBON:
            filePath += "Carbon2.png";
            break;
            
        case SULFUR:
            filePath += "Azufre2.png";
            break;
            
        case NITROGEN:
            filePath += "Nitrogen2.png";
            break;
            
        case SUGAR:
            filePath += "Azucar2.png";
            break;
            
        case WATER:
            filePath += "Agua.png";
            break;
            
        case CARBON_DIOXIDE:
            filePath += "Carbon dioxide.png";
            break;
            
        case METHANE:
            filePath += "Methane.png";
            break;
            
        case NITROUS_OXIDE:
            filePath += "Nitrous oxide.png";
            break;
            
        case SULFURIC_ACID:
            filePath += "Acido.png";
            break;
            
        case KRYPTONITE:
            filePath += "Kriptonita.png";
            break;
            
        default:
            filePath += "glow_particle.png";
            break;
    }
    return filePath;
}

Molecule Grid::getTileMolecule(int row, int col) {
	int tile = m_gameGrid[row][col];
	if (tile == SUGAR || tile == WATER || tile == CARBON_DIOXIDE || tile == METHANE || tile == NITROUS_OXIDE || tile == SULFURIC_ACID) {
		return (Molecule)tile;
	}
	return NONE;
}

void Grid::setGridObserver(GridObserver* observer) {
    m_gridObserver = observer;
}