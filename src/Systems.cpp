//
//  Systems.cpp
//  Dynamic Pursuit
//
//  Created by Serena Li on 4/6/22.
//

#include "Systems.hpp"


//  Add a Sprite to the Sprite System
//
void SpriteSystem::add(Sprite s) {
    sprites.push_back(s);
}

// Remove a sprite from the sprite system. Note that this function is not currently
// used. The typical case is that sprites automatically get removed when the reach
// their lifespan.
//
void SpriteSystem::remove(int i) {
    sprites.erase(sprites.begin() + i);
}


//  Update the SpriteSystem by checking which sprites have exceeded their
//  lifespan (and deleting).  Also the sprite is moved to it's next
//  location based on velocity and direction.
//
void SpriteSystem::update() {

    if (sprites.size() == 0) return;
    vector<Sprite>::iterator s = sprites.begin();
    vector<Sprite>::iterator tmp;

    // check which sprites have exceed their lifespan and delete
    // from list.  When deleting multiple objects from a vector while
    // traversing at the same time, use an iterator.
    //
    while (s != sprites.end()) {
        if (s->lifespan != -1 && s->age() > s->lifespan) {
            tmp = sprites.erase(s);
            s = tmp;
        }
        else s++;
    }

    //  Move enemy
    //
    for (int i = 0; i < sprites.size(); i++) {
        if(sprites[i].moveDir == Moveing){
//            sprites[i].pos += sprites[i].movingOrientation *  sprites[i].speed;
            sprites[i].integrate();
        }else{
            sprites[i].pos += sprites[i].velocity / ofGetFrameRate();
        }
    }
}

//  Render all the sprites
//
void SpriteSystem::draw() {
    for (int i = 0; i < sprites.size(); i++) {
        sprites[i].draw();
    }
}

// remove all sprites within a given dist of point, return number removed
//
int SpriteSystem::removeNear(Player player) {
    vector<Sprite>::iterator s = sprites.begin();
    vector<Sprite>::iterator tmp;
    int count = 0;

    while (s != sprites.end()) {

        if (player.inside(glm::vec3(s->pos.x, s->pos.y, 1))) {
            tmp = sprites.erase(s);
            count++;
            s = tmp;
        }
        else s++;
    }
    return count;
}

ofVec3f SpriteSystem::removeNear(Bullet bullet) {
    ofVec3f positions = ofVec3f(-1,-1,-1);
    vector<Sprite>::iterator s = sprites.begin();
    vector<Sprite>::iterator tmp;
    int count = 0;
    int i = 0;
    while (s != sprites.end()) {

        if (s->inside(glm::vec3(bullet.pos.x, bullet.pos.y, 1))) {
            positions = s->pos;
            tmp = sprites.erase(s);
            count++;
            i++;
            s = tmp;
        }
        else s++;
    }
    return positions;
}

void BulletSystem::add(Bullet s) {
    bullets.push_back(s);
}

void BulletSystem::remove(int i) {
    bullets.erase(bullets.begin() + i);
}

void BulletSystem::update() {

    if (bullets.size() == 0) return;
    vector<Bullet>::iterator s = bullets.begin();
    vector<Bullet>::iterator tmp;

    // check which bullet have exceed their lifespan and delete
    // from list.  When deleting multiple objects from a vector while
    // traversing at the same time, use an iterator.
    //
    while (s != bullets.end()) {
        if (s->lifespan != -1 && s->age() > s->lifespan) {
            tmp = bullets.erase(s);
            s = tmp;
        }
        else s++;
    }

    //  Move bullet
    //
    for (int i = 0; i < bullets.size(); i++) {
        bullets[i].pos += (bullets[i].velocity / ofGetFrameRate())*bullets[i].speed;
    }
}

void BulletSystem::draw() {
    for (int i = 0; i < bullets.size(); i++) {
        bullets[i].draw();
    }
}
