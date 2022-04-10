#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Sprite.h"



class Emitter;
class Player;
class BulletEmitter;


class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();
    void checkCollisions();

        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void mouseEntered(int x, int y);
        void mouseExited(int x, int y);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
    
    bool checkBoundaries();

        Player player;
    
        bool mouseDrag = false;
        
        glm::vec3 mousePos;
        glm::vec3 distanceToCenter;
        map<int, bool> keymap;
    
    float e;
    
        
    ofxPanel gui;
    ofxIntSlider gameLevel;
    
    ofxFloatSlider playerSpeed;
    ofxToggle useImage;
    ofxToggle showHeading;
    ofxFloatSlider playerScale;
    ofxIntSlider numEnergy;
    ofxIntSlider nAgents;
    ofxIntSlider lifespan;
    ofxIntSlider spriteSpeed;
    ofxFloatSlider rate;
    
    ofxFloatSlider thrust;
    ofxFloatSlider restitution;
    
    bool bHide;
    bool bFullscreen = false;
    
    ofImage playerImage;
    ofImage bulletImage;
    ofImage spriteImage;
    
    ofImage backgroundImage;
    int imageWidth;
    int imageHeight;
    
    Emitter *invaders;
    BulletEmitter  *gun;
    
    
    int score;
    float gameStartTime;
    bool gameOver = false;
    ofVec3f mouseLast;
    float totalGameTime;
    int currentLevel;
    
    ofTrueTypeFont    verdana14;
    
    ofSoundPlayer explodeSound;
    ofSoundPlayer shootingSound;
    ofSoundPlayer collisionSound;
    ofSoundPlayer movementSound;
    
    ParticleEmitter *particleEmitter = new ParticleEmitter();
    
};
