#pragma once
#include "ofMain.h"
#include "TriangleShape.hpp"
#include "Particle.h"
#include "ParticleEmitter.h"

//----------------------------------------------------------------------------------
//
// Basic Sprite Class
//
//
//  Kevin M. Smith - CS 134 SJSU



// This is a base object that all drawable object inherit from
// It is possible this will be replaced by ofNode when we move to 3D
//
typedef enum { autoTurn, Moveing } MoveState;




class Player : public TriShip {
public:
    Player() {} 
    Player(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3): TriShip(p1, p2, p3){
        nEnergy = 5;
    }
    void draw();
    virtual bool inside(glm::vec3 p);
    bool bShowSprite;
    ofImage playerImage;
    int nEnergy;
    bool useImage;
    bool showHeading;
    float width, height;
    glm::vec3 offSet = glm::vec3(0, 50, 0);


};
//+++++++++++++++++++++++++++++++++


//  General Sprite class  (similar to a Particle)
//
class Sprite : public TriShip {
public:
    Sprite(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
	
	void draw();
	float age();
    void updata();
	void setImage(ofImage);
    void setVelocity(ofVec3f);
    bool inside(glm::vec3 p);
    bool useImage;
	int speed;    //   in pixels/sec
	ofVec3f velocity; // in pixels/sec
    ofVec3f movingOrientation;
	ofImage image;
	float birthtime; // elapsed time in ms
	float lifespan;  //  time in ms
	bool haveImage;
	float width, height;
    MoveState moveDir;
    
};
