//
//  GameBoard.cpp
//  QuimiPop
//
//  Created by Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz on 3/22/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado & Graciela Garcia Diaz. All rights reserved.
//

#include "GameBoard.h"

#define PI 3.14159265358979323846
#define TILE_WIDTH 70.0f
#define TILE_HEIGHT 62.0f
#define MOLECULE_ANIM_FRAMES 90

void MoleculeAnimation::start(int frames) {
    m_currFrames = 0;
    m_animating = true;
    m_totalFrames = frames;
}

void MoleculeAnimation::addTile(int row, int col) {
    m_tiles.emplace_back(row, col);
}

void MoleculeAnimation::update(std::map<int, Sprite>& spriteMap) {
    float angle = 2 * PI * (float)m_currFrames / (float)m_totalFrames;
	ColorRGBA8 color(255 * cos(angle / 7.0f), 255, 255, 255 * cos(angle / 5.0f));
    for (auto& tile : m_tiles) {
        Sprite& sprite = spriteMap.find(tile.row * 8 + tile.col)->second;
        sprite.rotation = angle;
        sprite.color = color;
    }
    m_currFrames++;
    if (m_currFrames == m_totalFrames) {
        m_observer->notifyAnimationFinished();
        m_animating = false;
        m_tiles.clear();
    }
}

void GameBoard::formedMoleculeRow(int row, int col, int size) {
    printf("Formed molecule on a row! Row: %d, Col %d, Size %d\n", row, col, size);
    for (int i = col; i < col + size; i++) {
        m_molAnimation.addTile(row, i);
    }
    m_molAnimation.start(MOLECULE_ANIM_FRAMES);

	m_moleculeSound.play();

	m_score += size * 50;
}

void GameBoard::formedMoleculeCol(int row, int col, int size) {
    printf("Formed molecule on a column! Row: %d, Col %d, Size %d\n", row, col, size);
    for (int i = row; i < row + size; i++) {
        m_molAnimation.addTile(i, col);
    }
    m_molAnimation.start(MOLECULE_ANIM_FRAMES);

	m_moleculeSound.play();

	m_score += size * 50;
}

void GameBoard::notifyAnimationFinished() {
    refreshSpritesFromGrid();
}

GameBoard::GameBoard(glm::vec2 position) : m_boardPosition(position), m_clickingDown(false), m_setMouseCoords(false), m_highlighting(false), m_highlightCol(-1), m_highlightRow(-1) {}

void GameBoard::init() {
    srand(time(NULL));
    
    m_molAnimation.registerObserver(this);
    
    m_boardGrid.init();
    m_boardGrid.setGridObserver((GridObserver*)this);
    
    refreshSpritesFromGrid();
}

void GameBoard::update() {
    // Calcular scrolling con el mouse
    if (m_clickingDown && !m_setMouseCoords) {
        glm::vec2 baseTile = getTileForCoords(m_originMouseCoords);
        glm::vec2 offsetTile = getTileForCoords(m_currMouseCoords);
        m_offset = offsetTile - baseTile;
        if (!m_highlighting && (std::abs((int)m_offset.x) > 0 || std::abs((int)m_offset.y) > 0)) {
            if (std::abs(m_offset.x) > std::abs(m_offset.y)) {
                m_highlightRow = (int)baseTile.y;
                updateRowHighlight(true, m_highlightRow);
                printf("Highlighted row: %d\n", m_highlightRow);
            }
            else {
                m_highlightCol = (int)baseTile.x;
                updateColHighlight(true, m_highlightCol);
                printf("Highlighted col: %d\n", m_highlightCol);
            }
            m_highlighting = true;
        }
        if (m_highlightRow != -1) {
            updateRowOffset(m_highlightRow, (int)m_offset.x);
        }
        else if (m_highlightCol != -1) {
            updateColOffset(m_highlightCol, (int)m_offset.y);
        }
    }
    
    // Animacion transicion de moleculas
    if (m_molAnimation.isAnimating()) {
        m_molAnimation.update(m_spriteMap);
    }

	// Molecula seleccionada con el mouse
	if (!m_clickingDown && isPointInsideBoard(m_currMouseCoords)) {
		glm::vec2 hoverTile = getTileForCoords(m_currMouseCoords);
		Molecule hovering = m_boardGrid.getTileMolecule((int)hoverTile.y, (int)hoverTile.x);
		if (hovering != NONE) {
			m_hoverMolecule = hovering;
		}
	}
}

void GameBoard::draw(SpriteBatch &spriteBatch) {
    static glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
    
    std::map<int, Sprite>::iterator it;
    for (it = m_spriteMap.begin(); it != m_spriteMap.end(); it++) {
        Sprite& sprite = it->second;
        spriteBatch.draw(sprite.rectangle, uv, ResourceManager::getTexture(sprite.texturePath).textureId, 0.0f, sprite.color, sprite.rotation);
    }
}

void GameBoard::setClickingDown(bool clickingDown) {
    if (clickingDown && !m_clickingDown) {
        m_setMouseCoords = true;
    }
    else {
        m_setMouseCoords = false;
    }
    m_clickingDown = clickingDown;
    if (!m_clickingDown && m_highlighting) {
        glm::vec2 offset = m_currMouseCoords - m_originMouseCoords;
        if (m_highlightRow > -1) {
            m_boardGrid.moveGrid(1, m_highlightRow, (int)m_offset.x);
            refreshRowFromGrid(m_highlightRow);
			while (m_boardGrid.checkGrid(1, m_highlightRow)) {}
        }
        else if (m_highlightCol > -1) {
            m_boardGrid.moveGrid(0, m_highlightCol, (int)m_offset.y);
            refreshColFromGrid(m_highlightCol);
			while (m_boardGrid.checkGrid(0, m_highlightCol)) {}
        }
        m_highlighting = false;
        m_highlightRow = -1;
        m_highlightCol = -1;
		
		m_remainingTurns--;
    }
}

void GameBoard::updateMouseCoords(glm::vec2 mouseCoords) {
    if (m_setMouseCoords) {
        m_originMouseCoords = mouseCoords;
    }
    else {
        m_currMouseCoords = mouseCoords;
    }
}

Molecule GameBoard::getHoverMolecule() {
	return m_hoverMolecule;
}

void GameBoard::resetHoverMolecule() {
	m_hoverMolecule = NONE;
}

void GameBoard::setMoleculeSound(SoundEffect moleculeSound) {
	m_moleculeSound = moleculeSound;
}

int GameBoard::getScore() {
	return m_score;
}

void GameBoard::resetScore() {
	m_score = 0;
}

int GameBoard::getRemainingTurns() {
	return m_remainingTurns;
}

void GameBoard::resetRemainingTurns() {
	m_remainingTurns = 15;
}

bool GameBoard::isPointInsideBoard(glm::vec2 point) {
    return point.x >= m_boardPosition.x && point.x <= m_boardPosition.x + TILE_WIDTH * 8 && point.y >= m_boardPosition.y && point.y <= m_boardPosition.y + TILE_HEIGHT * 8;
}

glm::vec4 GameBoard::getTileRectangle(int row, int col) {
    return glm::vec4(
        TILE_WIDTH * col + m_boardPosition.x,
        TILE_HEIGHT * row + m_boardPosition.y,
        TILE_WIDTH,
        TILE_HEIGHT
    );
}

glm::vec2 GameBoard::getTileForCoords(glm::vec2 coords) {
    return glm::vec2((coords.x - m_boardPosition.x) / TILE_WIDTH, (coords.y - m_boardPosition.y) / TILE_HEIGHT);
}

int GameBoard::getRowForY(int y) {
    return (y - m_boardPosition.y) / TILE_HEIGHT;
}

int GameBoard::getColForX(int x) {
    return (x - m_boardPosition.x) / TILE_WIDTH;
}

void GameBoard::rescaleTile(Tile tile, float scale) {
    Sprite& sprite = m_spriteMap.find(tile.row * 8 + tile.col)->second;
    float oldWidth = sprite.rectangle.z;
    sprite.rectangle.z = scale * TILE_WIDTH;
    sprite.rectangle.x = sprite.rectangle.x - (sprite.rectangle.z - oldWidth) / 2;
    
    float oldHeight = sprite.rectangle.w;
    sprite.rectangle.w = scale * TILE_HEIGHT;
    sprite.rectangle.y = sprite.rectangle.y - (sprite.rectangle.w - oldHeight) / 2;
}

void GameBoard::updateColHighlight(bool highlight, int col) {
    for (int row = 0; row < 8; row++) {
        if (highlight) {
            rescaleTile(Tile(row, col), 1.25);
        }
        else {
            rescaleTile(Tile(row, col), 1);
        }
    }
}

void GameBoard::updateRowHighlight(bool highlight, int row) {
    for (int col = 0; col < 8; col++) {
        if (highlight) {
            rescaleTile(Tile(row, col), 1.25);
        }
        else {
            rescaleTile(Tile(row, col), 1);
        }
    }
}

void GameBoard::updateColOffset(int col, int offset) {
    for (int row = 0; row < 8; row++) {
        Sprite& sprite = m_spriteMap.find(row * 8 + col)->second;
        sprite.rectangle.y = TILE_HEIGHT * ((row + offset + 8) % 8) + m_boardPosition.y - TILE_HEIGHT / 8;
    }
}

void GameBoard::updateRowOffset(int row, int offset) {
    for (int col = 0; col < 8; col++) {
        Sprite& sprite = m_spriteMap.find(row * 8 + col)->second;
        sprite.rectangle.x = TILE_WIDTH * ((col + offset + 8) % 8) + m_boardPosition.x - TILE_WIDTH / 8;
    }
}

void GameBoard::refreshSpritesFromGrid() {
    if (m_spriteMap.size() > 0) {
        m_spriteMap.clear();
    }
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            m_spriteMap.insert(std::make_pair(row * 8 + col, Sprite(m_boardGrid.getTileTexturePath(row, col), getTileRectangle(row, col))));
        }
    }
}

void GameBoard::refreshRowFromGrid(int row) {
    for (int col = 0; col < 8; col++) {
        Sprite& sprite = m_spriteMap.find(row * 8 + col)->second;
        sprite.texturePath = m_boardGrid.getTileTexturePath(row, col);
        sprite.rectangle = getTileRectangle(row, col);
    }
}

void GameBoard::refreshColFromGrid(int col) {
    for (int row = 0; row < 8; row++) {
        Sprite& sprite = m_spriteMap.find(row * 8 + col)->second;
        sprite.texturePath = m_boardGrid.getTileTexturePath(row, col);
        sprite.rectangle = getTileRectangle(row, col);
    }
}