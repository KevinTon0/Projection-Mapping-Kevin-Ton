/*
	Author: Kevin Ton,
	Project: OpenFrameWorks Projection Mapping
	Filename: MucusCells.h
*/

#ifndef MucusCells_h
#define MucusCells_h

#include "ofMain.h"
#include "FboSource.h"

class MucusCells : public ofx::piMapper::FboSource {
    public:
//Default functions
        void setup();
        void update();
        void draw();
        void setName(string);
        void reset();
//Global variables and functions I created
        void ring(float r, float p);
        void perlinNoise();
        int phase;
        float t;
        int startTime;
        ofColor ballColor;
//Default Ball Functions
        vector <ofVec2f> locations;
        vector <ofVec2f> speeds;
        void setupBalls();
        void updateBalls();
        void drawBalls(int x, int y, int w, int h);
};

#endif /* MucusCells_h */
