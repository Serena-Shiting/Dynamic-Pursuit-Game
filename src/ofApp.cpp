#include "ofApp.h"
#include "Emitter.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofBackground(0, 0, 0);
    
    // Record the time when the game starts
    gameStartTime = ofGetElapsedTimeMillis();
    
    ofTrueTypeFont::setGlobalDpi(250);
    verdana14.load("verdana.ttf", 14, true, true);

    
    if(!backgroundImage.load("images/backgroundImag.png")){
        cout << "Can't load image 'backgroundImage.jpeg'" << endl;
        exit();
    }
    
    if (!bulletImage.load("images/bullet.png")){
        cout << "Can't load image 'bullet.png'" << endl;
        exit();
    }
    if (!playerImage.load("images/airplane.png")){
        cout << "Can't load image 'airplane.png'" << endl;
        exit();
    }
    if (!explodeSound.load("sound/explode.mp3")){
        cout << "Can't load sound 'explode.mp3'" << endl;
        exit();
    }
    explodeSound.setVolume(0.8);
    if (!shootingSound.load("sound/shooting.mp3")){
        cout << "Can't load sound 'shooting.mp3'" << endl;
        exit();
    }
    if (!collisionSound.load("sound/Collision.mp3")){
        cout << "Can't load sound 'Collision.mp3'" << endl;
        exit();
    }
    if (!movementSound.load("sound/movement.mp3")){
        cout << "Can't load sound 'movement.mp3'" << endl;
        exit();
    }
    
    //set up player
    player = Player(glm::vec3(-30, 50, 1), glm::vec3(30, 50, 1), glm::vec3(0, -100, 1));
    player.pos = glm::vec3(ofGetWindowWidth()/2.0, ofGetWindowHeight()/2.0, 0);
    player.rotation = 45;
    player.playerImage = playerImage;
    player.width = playerImage.getWidth();
    player.height =playerImage.getHeight();
    

    gui.setup();
    gui.add(useImage.setup("Use image", true));
    gui.add(showHeading.setup("Draw Heading", true));
    gui.add(playerScale.setup("Scale of player", 0.1, 0.05, 0.4));
    gui.add(gameLevel.setup("Game Level", 2, 0, 3));
    
    gui.add(numEnergy.setup("Life", 5, 1, 10));
    gui.add(playerSpeed.setup("player Speed", 3, 0, 10));
    gui.add(spriteSpeed.setup("Enemy Speed", 1, 0, 3));
    gui.add(nAgents.setup("# of enemis per spawn", 2, 1, 8));
    gui.add(rate.setup("Spawn rate", 3, 0.5, 20));
    gui.add(lifespan.setup("Lifespan of enemy", 10000, 6000, 20000));
    gui.add(thrust.setup("Thrust", 500, 100, 1000));
    gui.add(restitution.setup("Restitution", .85, 0.0, 1.0));
    
    bHide = false;
    
    
    // Create and setup emitters
    invaders = new Emitter(new SpriteSystem());
    gun = new BulletEmitter();

    //setup image for invaders
    if (!(spriteImage.load("images/rocket.png"))){
        cout << "Can't load image 'rocket.png'" << endl;
        exit();
    }

    invaders->setChildImage(spriteImage);
    gun->setPosition(player.pos + player.offSet * player.scale);
    gun->setPosition(player.pos);
    gun->drawable = false;
    gun->setChildImage(bulletImage);
    gun->start();
    

    particleEmitter->setPosition(ofVec3f(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2,100));
   
}

//--------------------------------------------------------------
void ofApp::update(){
    


    if(gameLevel == 1){
        playerSpeed = 2;
        numEnergy = 2;
        spriteSpeed = 1;
        nAgents = 1;
        lifespan = 9000;
        rate = 10;
    }else if(gameLevel == 2){
        playerSpeed = 5;
        numEnergy = 5;
        spriteSpeed = 1;
        nAgents = 1;
        lifespan = 12000;
        rate = 20;
    }else if(gameLevel == 3){
        playerSpeed = 10;
        numEnergy = 7;
        spriteSpeed = 3;
        nAgents = 3;
        lifespan = 15000;
        rate = 3;
    }
    
        
    //Control from the GUI: scale
    float s = playerScale;
    player.scale = glm::vec3(s, s, s);
    gun->sys->scale = glm::vec3(s, s, s);
    
    //Control from the GUI: use image or not
    player.bShowSprite = useImage;
    player.showHeading = showHeading;
    
    //Control from the GUI: speed
    float moveSpeed = playerSpeed;
    
    //Control from the GUI: nEnergy
    if(invaders->started == false){
        int energy = numEnergy;
        player.nEnergy = energy;
        currentLevel = energy;
    }
    //Control from the GUI: nAgents
    int numOfAgents = nAgents;
    invaders->numAgents = numOfAgents;
    
    //Control from the GUI: lifeSpan
    int lifeSpan = lifespan;
    invaders->setLifespan(lifeSpan);
    
    //Control from the GUI: rate
//    int r = rate;
//    invaders->setRate(r);
    
//    //Control from the GUI:
    float triThrust = thrust;
    e = restitution;
    
    
    // zero out forces
    //
    player.force = glm::vec3(0, 0, 0);
    
    
    //key
    //
    if (keymap[OF_KEY_LEFT] ){
        player.angularForce -= moveSpeed;
        player.integrate();
        player.damping = player.angulardamping;
     }
    if (keymap[OF_KEY_RIGHT] ){
        player.angularForce += moveSpeed;
        player.integrate();
        player.damping = player.angulardamping;
    }
    if (keymap[OF_KEY_UP] ){
        player.force += player.heading() * triThrust;
        player.integrate();
    }
    if (keymap[OF_KEY_DOWN] ){
        player.force -= player.heading() * triThrust;
        player.integrate();
    }
    if(keymap[' ']){
        // start the game
        gameOver = false;
        invaders->start();
    }
    if(keymap['F'] || keymap['f']){
        bFullscreen = !bFullscreen;
        ofSetFullscreen(bFullscreen);
    }
    if(keymap['B'] || keymap['b']){
        
    }
    
    
//====== SPRITES update: =========
    
//      for sprite in invaders->sys->sprites{
//      update each sprites' direction and velocity
    for(int i=0; i < invaders->sys->sprites.size();i++){
        
        // zero out sprites forces
        //
        invaders->sys->sprites[i].force = glm::vec3(0, 0, 0);
        
        ofVec3f direction = glm::vec3(player.pos.x, player.pos.y, 0) - glm::vec3(invaders->sys->sprites[i].pos.x, invaders->sys->sprites[i].pos.y, 0);
        
        ofVec3f orientation = glm::normalize(glm::vec3(direction));
        invaders->sys->sprites[i].movingOrientation = orientation;

        ofVec3f sHeading = invaders->sys->sprites[i].heading();
        
        float dot_product = sHeading.x * orientation.x + sHeading.y * orientation.y;
        float cross_product = sHeading.x * orientation.y - sHeading.y * orientation.x;
        float rotationAmount = atan2(cross_product, dot_product) * (180.0/3.141592653589793238463);
        
        invaders->sys->sprites[i].rotation += rotationAmount/ofGetFrameRate();
        
        //---autoTurn state---
        if(invaders->sys->sprites[i].moveDir == autoTurn){
            
            if(rotationAmount < 1){
                invaders->sys->sprites[i].moveDir = Moveing;
                invaders->sys->sprites[i].speed = spriteSpeed;
            }
        }else{
            ofVec3f f = direction * invaders->sys->sprites[i].speed;
            invaders->sys->sprites[i].force += f;
        }
    }
    
    
    //if player lose all the energy, game over
    if(currentLevel <= 0){
        gameOver = true;
        invaders->stop();
        
        setup();
    }
    
    
    //handle game time:
    float t = ofGetElapsedTimeMillis();
    //Only when game started, total game time starts to accumulate
    if(invaders->started == true){
        totalGameTime = t - gameStartTime;
    }else{
        gameStartTime = t;
    }
    
    //update gun
    ofVec3f velocity = player.heading();
    gun->setVelocity(ofVec3f(velocity.x, velocity.y, velocity.z));
    gun->setPosition(player.pos);
    gun->update();
    
    ofSeedRandom();
    particleEmitter->update();
    
    invaders->update();
    
    
    // update player's position
    checkBoundaries();
    // check for collisions between player and invaders
    checkCollisions();

    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    backgroundImage.draw(0,0,ofGetWindowWidth(), ofGetWindowHeight());
    
    player.draw();
    gun->draw();
    
    if(!bHide){
        gui.draw();
    }
    
    // ---------Display Text----------
    //
    string scoreText;
    int realTime = totalGameTime/1000;
    scoreText += "Press space to start the game!\n";
    ofSetColor(224, 77, 176);
    ofDrawBitmapString(scoreText, ofPoint(250, 20));
    ofSetColor(ofColor::white);
    
    if (gameOver) {
        ofSetColor(255, 250, 77);
        verdana14.drawString("GAME OVER!", (ofGetWindowWidth() / 2)-150, (ofGetWindowHeight() / 2));
        ofSetColor(ofColor::white);
    }
    else {
        invaders->draw();
    }
    

    ofPushMatrix();
    particleEmitter->sys->draw();
    ofPopMatrix();
    ofSetColor(ofColor::white);
    
    
    string gameInfo;
    if(gameOver){
        gameInfo += "Player life: 0\n";
    }else{
        gameInfo += "player life: " + std::to_string(currentLevel) + "/" + std::to_string(player.nEnergy) + "\n";
    }
    gameInfo += "Total elapsed time: " + std::to_string(realTime) + " s\n";
    gameInfo += "Frame rate: " + std::to_string(ofGetFrameRate());
    ofDrawBitmapString(gameInfo, ofPoint(ofGetWindowWidth()-250, 20));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    keymap[key] = true;

    switch (key) {
    case OF_KEY_LEFT:   // turn left
        break;
    case OF_KEY_RIGHT:  // turn right
        break;
    case OF_KEY_UP:     // go forward
            movementSound.play();
        break;
    case OF_KEY_DOWN:   // go backward
            movementSound.play();
        break;
    case 'q':
    case 'Q':
        gun->spawn();
        shootingSound.play();
        break;
    case 'h':
    case 'H':
        bHide = !bHide;
        break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    keymap[key] = false;
    switch (key) {
    case OF_KEY_CONTROL:
//        bCtrlKeyDown = false;
        break;
    case OF_KEY_LEFT:   // turn left
            player.angularForce = 0;
            player.damping = player.movingdamping;
        break;
    case OF_KEY_RIGHT:  // turn right
            player.angularForce = 0;
            player.damping = player.movingdamping;
        break;
    case OF_KEY_UP:     // go forward
        break;
    case OF_KEY_DOWN:   // go backward

        break;
    case 'A':
    case 'a':
        particleEmitter->sys->reset();
        particleEmitter->start();
            
        break;
    default:
        break;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    //when mouse draging inside the triangle, the trianle should
    //change its pos to where the mouse position is
    if(mouseDrag){
        player.pos = glm::vec3(ofGetMouseX(), ofGetMouseY(), 1.0);
        player.pos -= distanceToCenter;
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    mousePos = glm::vec3(ofGetMouseX(), ofGetMouseY(), 1.0);

    mouseDrag = player.inside(mousePos);
    if(mouseDrag){
        distanceToCenter = mousePos - player.pos;
    }
    if (!invaders->started) {
        gameStartTime = ofGetElapsedTimeMillis();
        gameOver = false;
        invaders->start();
        totalGameTime = 0;
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    mouseDrag = false;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}


bool ofApp::checkBoundaries(){

    for(int i = 0; i < player.verts.size(); i++){

        int d = 0;
        glm::vec3 f;
        glm::vec3 p = player.getMatrix() * glm::vec4(player.verts[i], 1);

        if(p.x > ofGetWindowWidth()){

            player.pos.x -= (player.velocity.x * (1/ofGetFrameRate()) + d);
            f = (1 + e) * (glm::dot(-player.velocity, glm::vec3(-1, 0, 0)) * glm::vec3(-1, 0, 0));

            player.velocity.x += f.x;
            player.force += f * 30;
            return true;
        }
        else if(p.x < 0){
            player.pos.x -= (player.velocity.x * (1/ofGetFrameRate()) - d) ;
            f = (1 + e) * (glm::dot(-player.velocity, glm::vec3(1, 0, 0)) * glm::vec3(1, 0, 0));

            player.velocity.x += f.x;
            player.force += f * 30;
            return true;
        }

        if(p.y > ofGetWindowHeight()){

            player.pos.y  -= (player.velocity.y * (1/ofGetFrameRate()) + d);
//            f  =  (1 + e) * (( -v.dot.n) * n);
            f = (1 + e) * (glm::dot(-player.velocity, glm::vec3(0, -1, 0)) * glm::vec3(0, -1, 0));

            player.velocity.y += f.y;
            player.force += f * 30;
            return true;
        }
        else if(p.y < 0){

            player.pos.y -= (player.velocity.y * (1/ofGetFrameRate()) - d);
            f = (1 + e) * (glm::dot(-player.velocity, glm::vec3(0, 1, 0)) * glm::vec3(0, 1, 0));

            player.velocity.y += f.y;
            player.force += f * 30;
            return true;
        }

    }
    return false;
}

void ofApp::checkCollisions() {
    
    // the removeNear() function returns the number of missiles removed.
    //
    for (int i = 0; i < invaders->sys->sprites.size(); i++){
        
        //check player collicions
        //
        int removeNum;
        removeNum = invaders->sys->removeNear(player);
        if(removeNum){
            currentLevel -= 1;
            collisionSound.play();
        }
        
        //check bullet collisions
        //
        for (int j = 0; j < gun->sys->bullets.size(); j++){
            ofVec3f removeNum2;
            removeNum2 = invaders->sys->removeNear(gun->sys->bullets[j]);
            if(removeNum2.x != -1){
                explodeSound.play();
                currentLevel += 1;
                particleEmitter->setPosition(removeNum2);
                particleEmitter->sys->reset();
                particleEmitter->start();
            }
        
        }
    }
}
