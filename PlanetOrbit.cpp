/*
	Author: Kevin Ton,
	Project: OpenFrameWorks Projection Mapping
	Filename: PlanetOrbit.cpp
*/

#include "PlanetOrbit.h"

void PlanetOrbit::setup(){
    // Give our source a decent name
    name = "PlanetOrbitSource";

// Allocate our FBO source, decide how big it should be
    allocate(1000, 500);
//Global variables added from header file taken from the sunlocation lab assignment
    totalRays = 50;
    stepSize = 200;
    radius = 150;
    angleStep = 360.0 / totalRays;
    sunLocX = ofGetWidth() / 2;
    sunLocY = ofGetHeight() / 2;
    ofSetCircleResolution(60);
//Perlin Noise variable
    t = 0;

    setupBalls();
}

void PlanetOrbit::setName(string _name){
    name = _name;
}

// Don't do any drawing here
void PlanetOrbit::update(){
    updateBalls();
}

// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void PlanetOrbit::draw(){
    ofClear(0); //clear the buffer
    drawBalls(0,0,fbo->getWidth(), fbo->getHeight()); // Fill FBO with RED balls
}

//================================================================
//Creating balls at random locations with variable speed
void PlanetOrbit::setupBalls() {
    ofSetCircleResolution(50);
    for (int i=0; i<1; i++){
        ofVec2f randomLocation = ofVec2f(ofRandom(150,ofGetWidth()/2),ofRandom(200,ofGetHeight()/2));
        locations.push_back(randomLocation);
        ofVec2f randomSpeed = ofVec2f(ofRandom(5,5),ofRandom(5,5));
        speeds.push_back(randomSpeed);
    }
//This is to create the "noisy" aspect of hte program, it will allow the creation of all outer circles to be alterable and visible
    for (int i = 0; i < totalRays; i++) {
        noiseSeeds.push_back(ofRandom(10000));
    }
}
//Get time of when program begins
void PlanetOrbit::reset() {
    startTime = ofGetElapsedTimeMillis();
}


void PlanetOrbit::updateBalls(){
//This is to move the circles around the balls
    angleStep++;
// Move balls
    for(int i = 0; i < locations.size(); i++){
        locations[i] = locations[i] + speeds[i];
        if (locations[i].x<150 || locations[i].x>fbo->getWidth()-150) speeds[i].x*=-1;
        if (locations[i].y<150 || locations[i].y>fbo->getHeight()-150) speeds[i].y*=-1;
    }
}

void PlanetOrbit::drawBalls(int x, int y, int w, int h){
//Creation of rings around the center, and changing their colors
    ofPushMatrix();
    ofPushStyle();

    ofPoint innerRing, outerRing, planetRing, center, pulsingOutwards, verticalOutwards;
//Path object created to have the outer, less visible ring look fluid in movement
    ofPath path = ofPath();
//Creating the center circle of random color and having every object follow it
    for (int j = 0; j < locations.size(); j++) {

        ofSetColor(ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)));
        ofDrawCircle(locations[j], 10);
        

        if (locations[j].x != 0 || locations[j].y != 0) {
            sunLocX += (locations[j].x - sunLocX) * 1;
            sunLocY += (locations[j].y - sunLocY) * 1;
        }
    }
    ofTranslate(sunLocX, sunLocY);
    ofSetColor(253, 202, 19, 0);

//This is the creation of the rings and other objects moving as it follows the center
    for (int i = 0; i < noiseSeeds.size(); i++) {
        ofBeginShape();
        int c = ofNoise(innerRing.x*0.0005, innerRing.y*0.0005, t) * 150;
        
        innerRing.x = cos(ofDegToRad(angleStep* i)) * c;
        innerRing.y = sin(ofDegToRad(angleStep* i)) * c;
        outerRing.x = cos(ofDegToRad(angleStep* i)) * radius;
        outerRing.y = sin(ofDegToRad(angleStep* i)) * radius;
        planetRing.x = cos(ofDegToRad(angleStep* i) / 50) * radius;
        planetRing.y = sin(ofDegToRad(angleStep* i) / 25) * radius;
        center.x = cos(ofDegToRad(angleStep* i) / 25) * i;
        center.y = sin(ofDegToRad(angleStep* i) / 25) * i;
        
        if (ofGetElapsedTimeMillis() - startTime > 10000){
            
            pulsingOutwards.x = (cos(ofDegToRad(angleStep * i)) * angleStep)/10;
            pulsingOutwards.y = (sin(ofDegToRad(angleStep * i)) * radius)/10;
            ofDrawCircle(pulsingOutwards, 10);
            
        }
        if (ofGetElapsedTimeMillis() - startTime > 20000){
            
            verticalOutwards.x = (cos(ofDegToRad(angleStep * i)) * radius)/10;
            verticalOutwards.y = (sin(ofDegToRad(angleStep * i)) * angleStep)/10;
            ofDrawCircle(verticalOutwards, 10);
            
        }
        ofDrawCircle(center, 5);
        ofDrawCircle(planetRing, 5);
        ofSetColor(ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255), ofRandom(30, 70)));
        ofDrawCircle(innerRing, 10);
        ofSetColor(ofColor(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255)));
        ofDrawCircle(outerRing, 10);
        
        path.curveTo(i, i);
        ofEndShape();
        // i i on all goes crazy
    }
    
    t += 0.01;
    
    ofPopStyle();
    ofPopMatrix();
    }
