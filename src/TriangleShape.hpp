//
//  TriangleShape.hpp
//  Dynamic Pursuit
//
//  Created by Serena Li on 4/4/22.
//

#pragma once
#include "ofMain.h"

class Shape {
public:
    Shape() {}
    virtual void draw() {}
    virtual bool inside(glm::vec3 p) {
        return true;
    }
    void setPosition(ofVec3f);

    glm::vec3 pos;
    float rotation = 0.0;    // degrees
    glm::vec3 scale = glm::vec3(1, 1, 1);
    
    vector<glm::vec3> verts;

    glm::mat4 getMatrix() {
        glm::mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(pos));
        glm::mat4 rot = glm::rotate(glm::mat4(1.0), glm::radians(rotation), glm::vec3(0, 0, 1));
        glm::mat4 scale = glm::scale(glm::mat4(1.0), glm::vec3(this->scale));
        return (trans * rot * scale);
    }
};

class TriangleShape : public Shape {
public:
    TriangleShape() {}
    TriangleShape(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
        verts.push_back(p1);
        verts.push_back(p2);
        verts.push_back(p3);
    }
    bool inside(glm::vec3 p, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
    glm::vec3 heading();
};

class TriShip : public TriangleShape {
public:
    TriShip() {}
    TriShip(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
        verts.push_back(p1);
        verts.push_back(p2);
        verts.push_back(p3);
    }
    
    //  Integrator Function;
    //
    void integrate();

    // Physics data goes here  (for integrate() );
    //
    glm::vec3 velocity = glm::vec3(0, 0, 0);
    glm::vec3 acceleration = glm::vec3(0, 0, 0);
    glm::vec3 force = glm::vec3(0, 0, 0);
    float mass = 1.0;
    float damping = .99;//0.99
    float angulardamping = .95;
    float movingdamping = .99;
    float angularForce = 0;
    float angularVelocity = 0.0;
    float angularAcceleration = 0.0;
    bool bThrust = false;
    float prevDist = 0;
    
};

class Bullet: public Shape {
public:
    Bullet();
    void draw();
    float age();
    void setImage(ofImage);
    float speed;    //   in pixels/sec
    ofVec3f velocity; // in pixels/sec
    ofImage image;
    float birthtime; // elapsed time in ms
    float lifespan;  //  time in ms
    bool haveImage;
    float width, height;
    glm::mat4 matrix;
    
};


//  Base class for any object that needs a transform.
//
class TransformObject {
protected:
    TransformObject();
    ofVec3f position, scale;
    float    rotation;
    bool    bSelected;
    void setPosition(const ofVec3f &);
};
