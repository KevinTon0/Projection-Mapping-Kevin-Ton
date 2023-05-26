/*
	Author: Kevin Ton,
	Project: OpenFrameWorks Projection Mapping
	Filename: MucusCells.cpp
*/

#include "MucusCells.h"

void MucusCells::setup(){
    // Give our source a decent name
    name = "MucusCellsSource";

    // Allocate our FBO source, decide how big it should be
    allocate(1000, 500);

    setupBalls();
}

void MucusCells::setName(string _name){
    name = _name;
}

// Don't do any drawing here
void MucusCells::update(){
    updateBalls();
}

// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void MucusCells::draw(){
    ofClear(0); //clear the buffer
    drawBalls(0,0,fbo->getWidth(), fbo->getHeight()); // Fill FBO with RED balls
}

//================================================================
//Create balls at random location with variable speed, and make sure they are not created inside the edge
void MucusCells::setupBalls() {
    ofSetCircleResolution(50);
    for (int i=0; i<50; i++){
        ofVec2f randomLocation = ofVec2f(ofRandom(150,ofGetWidth()/2),ofRandom(150,ofGetHeight()/2));
        locations.push_back(randomLocation);
        ofVec2f randomSpeed = ofVec2f(ofRandom(-5,5),ofRandom(-5,5));
        speeds.push_back(randomSpeed);
    }
}

void MucusCells::reset() {
    startTime = ofGetElapsedTimeMillis();
}
//This noise creation is for the background as well as changing the color of the circles when a certain time passes
void MucusCells::perlinNoise(){
    
    int stepSize = 10;
    for (int x = 0; x < ofGetWidth(); x += stepSize) {
        for (int y = 0; y < ofGetHeight(); y += stepSize) {
            int c = ofNoise(x*0.005, y*0.005, t) * 150;
            ofSetColor(c);
            ofDrawRectangle(x, y, stepSize, stepSize);
        }
    }
    t += 0.01;
}
//Have the balls turn around when the edge of them hits the screen
void MucusCells::updateBalls(){
    // Move balls
    for(int i = 0; i < locations.size(); i++){
        locations[i] = locations[i] + speeds[i];
        if (locations[i].x<100 || locations[i].x>fbo->getWidth()-100) speeds[i].x*=-1;
        if (locations[i].y<100 || locations[i].y>fbo->getHeight()-100) speeds[i].y*=-1;
    }
}
//Using the ring lab, create a generative piece where the rings are moving inside the circles, as well as changing the colors over a set amount of time
void MucusCells::drawBalls(int x, int y, int w, int h){
    int timeRan = ofGetElapsedTimeMillis() - startTime;
//This is the code to lerp colors and mix them all consistently
    ofColor red = ofColor(255, 0, 0);
    ofColor green = ofColor(0, 255, 0);
    ofColor blue = ofColor(0, 0, 255);
    float colorPercent1 = ofMap(timeRan, 0, 11250, 0, 1, true);
    float colorPercent2 = ofMap(timeRan, 11250, 22500, 0, 1, true);
    float colorPercent3 = ofMap(timeRan, 22500, 33750, 0, 1, true);
    ofColor mix1 = red.getLerped(green, colorPercent1);
    ofColor mix2 = green.getLerped(blue, colorPercent2);
    ofColor mix3 = blue.getLerped(red, colorPercent3);
    int ringSpacing = 10;
    int circleNums = 10;
    float phasingSpace = 720 / circleNums;
//This is set here so that the perlin noise isn't affected by the color changing
    perlinNoise();
//Creating the circle rings and ensuring there's enough spacing between them all
    for (int j = circleNums; j > 0; j--) {
        if (ofGetElapsedTimeMillis() - startTime < 11250) ofSetColor(mix1);
        else if (ofGetElapsedTimeMillis() - startTime < 22500) ofSetColor(mix2);
        else if (ofGetElapsedTimeMillis() - startTime < 33750) ofSetColor(mix3);
        ring(j*ringSpacing, phase + phasingSpace * j);
    }
}

void MucusCells::ring(float r, float p) {
    ofPushMatrix();
    ofPushStyle();
    ofSetCircleResolution(100);
    
//This is to make the rings at the locations of the circles
        for (int i = 0; i < locations.size(); i++) {
        
        
        ofDrawCircle(locations[i], r);
        

    }
    ofSetColor(0);
//This for loop is to create spacing between each ring
    float radDiff = ofMap(sin(ofDegToRad(p)), -1, 1, 1, 5);
    //ofDrawCircle(0, 0, r - radDiff);
    for (int i = 0; i < locations.size(); i++) {

        ofDrawCircle(locations[i], r - radDiff);

    }
    ofPopStyle();
    ofPopMatrix();
}

