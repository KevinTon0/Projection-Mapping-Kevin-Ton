/*
	Author: Kevin Ton,
	Project: OpenFrameWorks Projection Mapping
	Filename: ofApp.h
*/

#pragma once

#include "ofMain.h"
#include "ofxPiMapper.h"
#include "VideoSource.h"
#include "ScanlineSource.h"
#include "magSlideShowSource.h"
#include "MucusCells.h"
#include "CurvedBalls.h"
#include "PlanetOrbit.h"
#include "WebLights.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);

    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseDragged(int x, int y, int button);

    ofxPiMapper piMapper;

    // By using a custom source that is derived from FboSource
    // you will be able to see the source listed in sources editor
    //ScanlineSource customSource;
    
    MucusCells mucusCells;
    CurvedBalls curvedBallsSource;
    PlanetOrbit planetOrbitSource;
    WebLights webLightsSource;
    magSlideShowSource slideShowSource;
    ofImage dummyObjects;

};
