//
//  Animation.h
//  QuimiPop
//
//  Created by Eduardo Alberto Sanchez Alvarado on 4/4/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado. All rights reserved.
//

#ifndef __QuimiPop__Animation__
#define __QuimiPop__Animation__

#include <vector>
#include "glm/glm.hpp"
#include "Sprite.h"

class Animation {
public:
    virtual void update() = 0;
    long getRemainingFrames();
    void incrFrameCount();
    
    static Animation* createRotateTo(float degrees, long duration, bool repeat);
    static Animation* createRotateBy(float degrees, long duration, bool repeat);
    
    static Animation* createScaleTo(float scale, long duration, bool repeat);
    static Animation* createScaleBy(float scale, long duration, bool repeat);
    
    static Animation* createMoveTo(glm::vec2 point, long duration, bool repeat);
    static Animation* createMoveBy(glm::vec2 point, long duration, bool repeat);
    
    void setSprite(Sprite* sprite) { m_sprite = sprite; }
    void setDuration(long duration) { m_duration = duration; }
    void setFrameCount(long frameCount) { m_frameCount = frameCount; }
    void setRepeat(bool repeat) { m_repeat = repeat; }
    void setAnimateBy(bool animateBy) { m_animateBy = animateBy; }
    
    Sprite* getSprite() { return m_sprite; }
    long getDuration() { return m_duration; }
    long getFrameCount() { return m_frameCount; }
    bool getRepeat() { return m_repeat; }
    bool getAnimateBy() { return m_animateBy; }
    
private:
    Sprite* m_sprite;
    long m_duration;
    long m_frameCount;
    bool m_repeat;
    bool m_animateBy;
};

class RotateAnimation : public Animation {
public:
    void update();
    
    void setDegrees(float degrees) { m_degrees = degrees; }
    void setOriginalDegrees(float originalDegrees) { m_originalDegrees = originalDegrees; }
    
private:
    float m_degrees;
    float m_originalDegrees;
};

class ScaleAnimation : public Animation {
public:
    void update();
    
    void setScale(float scale) { m_scale = scale; }
    void setOriginalScale(float originalScale) { m_originalScale = originalScale; }
    
private:
    float m_scale;
    float m_originalScale;
};

class TranslateAnimation : public Animation {
public:
    void update();
    
    void setCoord(glm::vec2 coord) { m_coord = coord; }
    void setOriginalCoord(glm::vec2 originalCoord) { m_originalCoord = originalCoord; }
    
private:
    glm::vec2 m_coord;
    glm::vec2 m_originalCoord;
};

class AnimationNode {
public:
    void update();
    bool isAnimationDone() { return m_animationsDone; }
    void setSprite(Sprite* sprite);
    
    void setRotation(Animation* rotation);
    void setScaling(Animation* scaling);
    void setTranslation(Animation* translation);
    
private:
    RotateAnimation* m_rotation;
    ScaleAnimation* m_scaling;
    TranslateAnimation* m_translation;
    bool m_hasRotation = false;
    bool m_hasScaling = false;
    bool m_hasTranslation = false;
    bool m_animationsDone = false;
};

class AnimationSequence {
public:
    void update();
    void setAnimationNodes(std::vector<AnimationNode> nodes) { m_nodes = nodes; }
    void addNode(AnimationNode node);
    void setSprite(Sprite* sprite);
    
private:
    std::vector<AnimationNode> m_nodes;
};

#endif /* defined(__QuimiPop__Animation__) */
