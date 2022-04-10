#pragma once
//----------------------------------------------------------------------------------
//
// Basic Sprite Emitter Class
//
//
//  Kevin M. Smith - CS 134 SJSU

#include "Sprite.h"
#include "Systems.hpp"
#include "TriangleShape.hpp"


//  General purpose Emitter class for emitting sprites
//  This works similar to a Particle emitter
//
class Emitter{
public:
    Emitter(){} ;
	Emitter(SpriteSystem *);
	void draw();
	void start();
	void stop();
	void setLifespan(float);    // in milliseconds
	void setVelocity(ofVec3f);  // pixel/sec
	void setChildImage(ofImage);
	void setChildSize(float w, float h) { childWidth = w; childHeight = h; }
	void setImage(ofImage);
	void setRate(float);
	float maxDistPerFrame();
	void update();
    void spawn(float time);
	SpriteSystem *sys;
    int numAgents;
	float rate;
	ofVec3f velocity;
	float lifespan;
	bool started;
	float lastSpawned;
	ofImage childImage;
	bool haveChildImage;
	bool haveImage;
	float width, height;
	float childWidth, childHeight;
    ofPoint childPosition;
    
    ofVec3f position;
};

class BulletEmitter: public Shape {
public:
    BulletEmitter(BulletSystem *);
    BulletEmitter();
    void init();
    void draw();
    void start();
    void stop();
    void setLifespan(float);
    void setVelocity(ofVec3f);
    void setChildImage(ofImage);
    void setImage(ofImage);
    void setRate(float);
    void update();
    void spawn();
    BulletSystem *sys;
    ofVec3f velocity;
    float lifespan;
    bool started;
    float lastSpawned;
    ofImage childImage;
    ofImage image;
    bool drawable;
    bool haveChildImage;
    bool haveImage;
    float width, height;
};
