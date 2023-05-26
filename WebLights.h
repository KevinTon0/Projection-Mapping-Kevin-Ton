/*
	Author: Kevin Ton,
	Project: OpenFrameWorks Projection Mapping
	Filename: WebLights.h
*/

#ifndef WebLights_h
#define WebLights_h

#include "ofMain.h"
#include "FboSource.h"

class WebLights : public ofx::piMapper::FboSource {
    public:
//Default
        void setup();
        void update();
        void draw();
        void reset();
        void setName(string);
        void keyPressed(int key);
        void keyReleased(int key);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
//Global variables and functions I added
        ofPath path = ofPath();
        int startTime;
        void perlinNoise();
//Default for balls
        vector <ofVec2f> locations;
        vector <ofVec2f> speeds;
        void drawBalls(int x, int y, int w, int h);
        void updateBalls();
        void setupBalls();
};

#endif /* WebLights_h */
