//
//  Systems.hpp
//  Dynamic Pursuit
//
//  Created by Serena Li on 4/6/22.
//

#include "Sprite.h"
#include "ofApp.h"
#include "TriangleShape.hpp"

//  Manages all Sprites in a system.  You can create multiple systems
//
class SpriteSystem {
public:
    void add(Sprite);
    void remove(int);
    void update();
    int removeNear(Player player);
    ofVec3f removeNear(Bullet bullet);
    void draw();
    vector<Sprite> sprites;
};

class BulletSystem  {
public:
    void add(Bullet);
    void remove(int);
    void update();
    void draw();
    glm::vec3 scale;
    glm::mat4 matrix;
    vector<Bullet> bullets;

};
