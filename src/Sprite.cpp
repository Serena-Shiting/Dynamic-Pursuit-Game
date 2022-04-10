#include "Sprite.h"
#include "ofApp.h"


//Player
//--------------------------------------------------------------

void Player::draw(){
    ofFill();
    ofPushMatrix();
    ofMultMatrix(getMatrix());
    ofDrawTriangle(verts[0], verts[1], verts[2]);
    ofPopMatrix();
    
    if(showHeading){
        ofSetColor(ofColor::whiteSmoke);
        ofDrawLine(pos, pos+ heading() * 75);
    }

    //draw image
    if(bShowSprite){
        ofPushMatrix();
        ofMultMatrix(getMatrix());
        playerImage.draw(-width/2, -height/2);
        ofPopMatrix();
    }
    
}

Sprite::Sprite(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3){
    verts.push_back(p1);
    verts.push_back(p2);
    verts.push_back(p3);
    
    speed = 0;
    velocity = ofVec3f(0, 0, 0);
    lifespan = -1;      // lifespan of -1 => immortal
    birthtime = 0;
    haveImage = false;
    useImage = false;
    moveDir = autoTurn;
    
};

//
// inside - check if point is inside player (can be an image or TriangleShape if no image)
bool Player::inside(const glm::vec3 p) {
    
    glm::vec3 s = glm::inverse(getMatrix()) * glm::vec4(p, 1);
    
    // if there is no sprite image attached, then just use triangle case.
    //
    if (!bShowSprite) {
        return TriangleShape::inside(s, verts[0], verts[1], verts[2]);
    }
    // if sprite image attached, then first check if point is inside bounds of image
    // in object space.  If point is inside bounds, then make sure the point is in
    // opaque part of image.
    int w = width;
    int h = height;
    if (s.x > -w / 2 && s.x < w / 2 && s.y > -h / 2 && s.y < h / 2) {
        int x = s.x + w / 2;
        int y = s.y + h / 2;
        ofColor color = playerImage.getColor(x, y);
        return (color.a != 0);   // check if color is opaque (not the transparent background)
        return true;
    }else return false;
}


//--------------------------------------------------------------
//Sprite
//--------------------------------------------------------------



void Sprite::setVelocity(ofVec3f v) {
    velocity = v;
}


// Return a sprite's age in milliseconds
//
float Sprite::age() {
	return (ofGetElapsedTimeMillis() - birthtime);
}

//  Set an image for the sprite. If you don't set one, a rectangle
//  gets drawn.
//
void Sprite::setImage(ofImage img) {
	image = img;
	haveImage = true;
	width = image.getWidth();
	height = image.getHeight();
}


//  Render the sprite
//
void Sprite::draw() {

	ofSetColor(255, 255, 255, 255);
    
	// draw image centered and add in translation amount
	//
    if (haveImage) {
        ofPushMatrix();
        ofMultMatrix(getMatrix());
		image.draw(-width / 2.0 + pos.x, -height / 2.0 + pos.y);
        ofPopMatrix();
	}
	else {
		// in case no image is supplied, draw something.
		// 
		ofNoFill();
		ofSetColor(224, 77, 176);
        ofPushMatrix();
        ofMultMatrix(getMatrix());
        ofDrawTriangle(verts[0], verts[1], verts[2]);
        ofSetColor(ofColor::white);
        ofPopMatrix();
	}
    
}

bool Sprite::inside(const glm::vec3 p) {  
    
    glm::vec3 s = glm::inverse(getMatrix()) * glm::vec4(p, 1);
    
    // if there is no sprite image attached, then just use triangle case.
    //
    if (!haveImage) {
        return TriangleShape::inside(s, verts[0], verts[1], verts[2]);
    }
    // if sprite image attached, then first check if point is inside bounds of image
    // in object space.  If point is inside bounds, then make sure the point is in
    // opaque part of image.
    int w = width;
    int h = height;
    if (s.x > -w / 2 && s.x < w / 2 && s.y > -h / 2 && s.y < h / 2) {
        int x = s.x + w / 2;
        int y = s.y + h / 2;
        ofColor color = image.getColor(x, y);
        return (color.a != 0);   // check if color is opaque (not the transparent background)
        return true;
    }else return false;
}



