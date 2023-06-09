/*
	Author: Kevin Ton,
	Project: OpenFrameWorks Projection Mapping
	Filename: ofApp.cpp
*/

#include "ofApp.h"

void ofApp::setup(){
	ofBackground(0);

	// Enable or disable audio for video sources globally
	// Set this to false to save resources on the Raspberry Pi
	ofx::piMapper::VideoSource::enableAudio = true;
	ofx::piMapper::VideoSource::useHDMIForAudio = false;

	// Register our sources.
	// This should be done before mapper.setup().
	//piMapper.registerFboSource(customSource);
	//
    piMapper.registerFboSource(mucusCells);
    piMapper.registerFboSource(curvedBallsSource);
    piMapper.registerFboSource(planetOrbitSource);
    piMapper.registerFboSource(webLightsSource);
    piMapper.registerFboSource(slideShowSource);
	piMapper.setup();
    
    dummyObjects.load("DummyObject3.png");

	// This will set the app fullscreen if compiled on Raspberry Pi.
	#ifdef TARGET_RASPBERRY_PI
		ofSetFullscreen(true);
	#endif

	// Start slideshow.
    slideShowSource.play();
}

void ofApp::update(){
	piMapper.update();
}

void ofApp::draw(){
    dummyObjects.draw(0,0, ofGetWidth(), ofGetHeight());
	piMapper.draw();
}

void ofApp::keyPressed(int key){
	piMapper.keyPressed(key);
}

void ofApp::keyReleased(int key){
	piMapper.keyReleased(key);
}

void ofApp::mousePressed(int x, int y, int button){
	piMapper.mousePressed(x, y, button);
}

void ofApp::mouseReleased(int x, int y, int button){
	piMapper.mouseReleased(x, y, button);
}

void ofApp::mouseDragged(int x, int y, int button){
	piMapper.mouseDragged(x, y, button);
}
