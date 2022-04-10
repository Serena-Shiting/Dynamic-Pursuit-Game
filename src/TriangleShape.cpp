//
//  TriangleShape.cpp
//  Dynamic Pursuit
//
//  Created by Serena Li on 4/4/22.
//

#include "TriangleShape.hpp"
#include "ofApp.h"

void Shape::setPosition(ofVec3f p) {
    pos = p;
}

bool TriangleShape::inside(glm::vec3 p, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
    glm::vec3 v1 = glm::normalize(p1 - p);
    glm::vec3 v2 = glm::normalize(p2 - p);
    glm::vec3 v3 = glm::normalize(p3 - p);
    float a1 = glm::orientedAngle(v1, v2, glm::vec3(0, 0, 1));
    float a2 = glm::orientedAngle(v2, v3, glm::vec3(0, 0, 1));
    float a3 = glm::orientedAngle(v3, v1, glm::vec3(0, 0, 1));
    if (a1 < 0 && a2 < 0 && a3 < 0) return true;
    else return false;
}

glm::vec3 TriangleShape::heading(){
    float angle = glm::radians(rotation);
    glm::vec3 heading = glm::normalize(glm::vec3(glm::sin(angle), -glm::cos(angle), 0));
    return heading;
}

void TriShip::integrate() {

    // init current framerate (or you can use ofGetLastFrameTime())
    //
    float framerate = ofGetFrameRate();
    float dt = 1.0 / framerate;

    // linear motion
    //
    pos += (velocity * dt);
    glm::vec3 accel = acceleration;
    accel += (force * 1.0 / mass);
    velocity += accel * dt;
    velocity *= damping;

    // angular motion
    //
    rotation += (angularVelocity * dt);
    float a = angularAcceleration;;
    a += (angularForce * 1.0 / mass);
    angularVelocity += a * dt;
    angularVelocity *= angulardamping;
}


Bullet::Bullet() {
    speed = 800;
    velocity = ofVec3f(0, 0, 0);
    lifespan = 1000;      // lifespan of -1 => immortal
    birthtime = 0;
    haveImage = false;
    width = 60;
    height = 80;
}

float Bullet::age() {
    return (ofGetElapsedTimeMillis() - birthtime);
}

void Bullet::setImage(ofImage img) {
    image = img;
    haveImage = true;
    width = image.getWidth();
    height = image.getHeight();
}


//  Render the bullet
//
void Bullet::draw() {

    ofSetColor(255, 250, 77, 255);
    ofPushMatrix();
    ofMultMatrix(getMatrix());
    if (haveImage) {
        image.draw(-width / 2.0, -height / 2.0 );
    }
    else {
        // in case no image is supplied, draw something.
        //
        ofDrawCircle(-width / 2.0, -height / 2.0, 30);
    }
    ofPopMatrix();
}


//  Base class for any object that needs a transform.
//
TransformObject::TransformObject() {
    position = ofVec3f(0, 0, 0);
    scale = ofVec3f(1, 1, 1);
    rotation = 0;
}

void TransformObject::setPosition(const ofVec3f & pos) {
    position = pos;
}
