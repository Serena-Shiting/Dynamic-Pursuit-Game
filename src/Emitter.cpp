#include "ofMain.h"
#include "Emitter.h"

//  Create a new Emitter - needs a SpriteSystem
//
Emitter::Emitter(SpriteSystem *spriteSys) {
	sys = spriteSys;
	lifespan = 3000;    // milliseconds
	started = false;
	lastSpawned = 0;
	rate = 1;    // sprites/sec
	haveChildImage = false;
	haveImage = false;
	childWidth = 10;
	childHeight = 10;
}

//  Draw the Emitter if it is drawable. In many cases you would want a hidden emitter
//
//
void Emitter::draw() {
	// draw sprite system
	//
	sys->draw();
}

//  Update the Emitter. If it has been started, spawn new sprites with
//  initial velocity, lifespan, birthtime.
//
void Emitter::update() {
	if (!started) return;

	float time = ofGetElapsedTimeMillis();
    
	if ((time - lastSpawned) > (1000.0 * rate)) {
		// spawn new sprites
        for(int i = 0; i < numAgents; i++){
            spawn(time);
        }
	}
	sys->update();
}
void Emitter::spawn(float time){
    childPosition.x = ofRandom(0, ofGetWindowWidth());
    childPosition.y = ofRandom(0, ofGetWindowHeight());
    Sprite sprite(glm::vec3(-10, 10, 0), glm::vec3(10, 10, 0), glm::vec3(0, -30, 0));
    if (haveChildImage){
        sprite.scale *= 0.1;
        sprite.setImage(childImage);
    }
    sprite.lifespan = lifespan;
    sprite.setPosition(childPosition);
    sprite.birthtime = time;
    sprite.width = childWidth;
    sprite.height = childHeight;

    sys->add(sprite);
    lastSpawned = time;
}

// Start/Stop the emitter.
//
void Emitter::start() {
    //spawn one sprite when game started
    lastSpawned = ofGetElapsedTimeMillis();
    if(!started){
        spawn(lastSpawned);
    }
	started = true;
}

void Emitter::stop() {
	started = false;
}


void Emitter::setLifespan(float life) {
	lifespan = life;
}

void Emitter::setVelocity(ofVec3f v) {
	velocity = v;
}

void Emitter::setChildImage(ofImage img) {
	childImage = img;
	haveChildImage = true;
	childWidth = img.getWidth();
	childHeight = img.getHeight();
}

void Emitter::setRate(float r) {
	rate = r;
}

float Emitter::maxDistPerFrame() {
	return  velocity.length() / ofGetFrameRate();
}

//  Create a new Emitter - needs a BulletSystem
//
BulletEmitter::BulletEmitter(BulletSystem *bulletSys) {
    sys = bulletSys;
    init();
}

BulletEmitter::BulletEmitter() {
    sys = new BulletSystem();
    init();
}

void BulletEmitter::init() {
    lifespan = 1000;    // milliseconds
    started = false;
    lastSpawned = 0;
    haveChildImage = false;
    haveImage = false;
    velocity = ofVec3f(100, 100, 0);
    drawable = true;
    width = 50;
    height = 50;
}


void BulletEmitter::draw() {
    if (drawable) {

        if (haveImage) {
            image.draw(-image.getWidth() / 2.0 + pos.x, -image.getHeight() / 2.0 + pos.y);
        }
        else {
            ofSetColor(0, 0, 200);
            ofDrawRectangle(-width/2 + pos.x, -height/2 + pos.y, width, height);
        }
    }

    // draw system
    //
    sys->draw();
}


void BulletEmitter::update() {
    if (!started) return;
    sys->update();
}

// Start/Stop the emitter.
//
void BulletEmitter::start() {
    started = true;
    lastSpawned = ofGetElapsedTimeMillis();
}

void BulletEmitter::stop() {
    started = false;
}


void BulletEmitter::setVelocity(ofVec3f v) {
    velocity = v;
}

void BulletEmitter::setChildImage(ofImage img) {
    childImage = img;
    haveChildImage = true;
}

void BulletEmitter::setImage(ofImage img) {
    image = img;
}

void BulletEmitter::spawn(){
    float time = ofGetElapsedTimeMillis();
    Bullet b;
    if (haveChildImage) b.setImage(childImage);
    b.velocity = velocity;
    b.lifespan = lifespan;
    b.scale = glm::vec3(0.1, 0.1, 0.1);//0.1
    b.setPosition(pos);
    b.birthtime = time;
    b.scale = sys->scale;
    b.matrix = sys->matrix;
    sys->add(b);
}
