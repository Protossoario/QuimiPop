//
//  Animation.cpp
//  QuimiPop
//
//  Created by Eduardo Alberto Sanchez Alvarado on 4/4/15.
//  Copyright (c) 2015 Eduardo Alberto Sanchez Alvarado. All rights reserved.
//

#include "Animation.h"

long Animation::getRemainingFrames() {
    return m_duration - m_frameCount;
}

void Animation::incrFrameCount() {
    m_frameCount++;
    if (m_repeat && m_frameCount == m_duration) {
        m_frameCount = 0;
    }
}

Animation* Animation::createRotateTo(float degrees, long duration, bool repeat) {
    RotateAnimation* anim = new RotateAnimation;
    anim->setDuration(duration);
    anim->setRepeat(repeat);
    anim->setAnimateBy(false);
    anim->setDegrees(degrees);
    return anim;
}

Animation* Animation::createRotateBy(float degrees, long duration, bool repeat) {
    RotateAnimation* anim = new RotateAnimation;
    anim->setDuration(duration);
    anim->setRepeat(repeat);
    anim->setAnimateBy(true);
    anim->setDegrees(degrees);
    return anim;
}

Animation* Animation::createScaleTo(float scale, long duration, bool repeat) {
    ScaleAnimation* anim = new ScaleAnimation;
    anim->setDuration(duration);
    anim->setRepeat(repeat);
    anim->setAnimateBy(false);
    anim->setScale(scale);
    return anim;
}

Animation* Animation::createScaleBy(float scale, long duration, bool repeat) {
    ScaleAnimation* anim = new ScaleAnimation;
    anim->setDuration(duration);
    anim->setRepeat(repeat);
    anim->setAnimateBy(true);
    anim->setScale(scale);
    return anim;
}

Animation* Animation::createMoveTo(glm::vec2 point, long duration, bool repeat) {
    TranslateAnimation* anim = new TranslateAnimation;
    anim->setDuration(duration);
    anim->setRepeat(repeat);
    anim->setAnimateBy(false);
    anim->setCoord(point);
    return anim;
}

Animation* Animation::createMoveBy(glm::vec2 point, long duration, bool repeat) {
    TranslateAnimation* anim = new TranslateAnimation;
    anim->setDuration(duration);
    anim->setRepeat(repeat);
    anim->setAnimateBy(false);
    anim->setCoord(point);
    return anim;
}

void RotateAnimation::update() {
    Sprite* sprite = getSprite();
    long frameCount = getFrameCount();
    long duration = getDuration();
    int angle = sprite->getAngle();
    
    if (getAnimateBy()) {
        sprite->setAngle(angle + m_degrees * frameCount / duration);
    }
    else {
        sprite->setAngle(angle + (m_degrees - m_originalDegrees) * frameCount / duration);
    }
    
    incrFrameCount();
}

void ScaleAnimation::update() {
    Sprite* sprite = getSprite();
    long frameCount = getFrameCount();
    long duration = getDuration();
    float scale = sprite->getScale();
    
    if (getAnimateBy()) {
        sprite->setScale(scale + m_scale * frameCount / duration);
    }
    else {
        sprite->setScale(scale + (m_scale - m_originalScale) * frameCount / duration);
    }
    
    incrFrameCount();
}

void TranslateAnimation::update() {
    Sprite* sprite = getSprite();
    long frameCount = getFrameCount();
    long duration = getDuration();
    glm::vec4 dimensions = sprite->getDimensions();
    
    if (getAnimateBy()) {
        dimensions.x += m_coord.x * frameCount / duration;
        dimensions.y += m_coord.y * frameCount / duration;
    }
    else {
        dimensions.x += (m_coord.x - m_originalCoord.x) * frameCount / duration;
        dimensions.y += (m_coord.y - m_originalCoord.y) * frameCount / duration;
    }
    
    sprite->setDimensions(dimensions);
    
    incrFrameCount();
}

void AnimationNode::update() {
    if (m_hasRotation) {
        m_rotation->update();
        if (m_rotation->getRemainingFrames() == 0) {
            m_animationsDone = true;
            delete m_rotation;
            m_hasRotation = false;
        }
        else {
            m_animationsDone = false;
        }
    }
    if (m_hasScaling) {
        m_scaling->update();
        if (m_scaling->getRemainingFrames() == 0) {
            m_animationsDone = true;
            delete m_scaling;
            m_hasScaling = false;
        }
        else {
            m_animationsDone = false;
        }
    }
    if (m_hasTranslation) {
        m_translation->update();
        if (m_translation->getRemainingFrames() == 0) {
            m_animationsDone = true;
            delete m_translation;
            m_hasTranslation = false;
        }
        else {
            m_animationsDone = false;
        }
    }
}

void AnimationNode::setRotation(Animation* rotation) {
    m_rotation = (RotateAnimation*)rotation;
    m_hasRotation = true;
}

void AnimationNode::setScaling(Animation* scaling) {
    m_scaling = (ScaleAnimation*)scaling;
    m_hasScaling = true;
}

void AnimationNode::setTranslation(Animation* translation) {
    m_translation = (TranslateAnimation*)translation;
    m_hasTranslation = true;
}

void AnimationNode::setSprite(Sprite *sprite) {
    if (m_hasRotation) {
        m_rotation->setSprite(sprite);
    }
    if (m_hasScaling) {
        m_scaling->setSprite(sprite);
    }
    if (m_hasTranslation) {
        m_translation->setSprite(sprite);
    }
}

void AnimationSequence::update() {
    std::vector<AnimationNode>::iterator iter;
    for (iter = m_nodes.begin(); iter != m_nodes.end(); ) {
        iter->update();
        if (iter->isAnimationDone()) {
            m_nodes.erase(iter);
        }
        else {
            iter++;
        }
    }
}

void AnimationSequence::addNode(AnimationNode node) {
    m_nodes.push_back(node);
}

void AnimationSequence::setSprite(Sprite *sprite) {
    for (auto& node : m_nodes) {
        node.setSprite(sprite);
    }
}