/*
	Author: Kevin Ton,
	Project: OpenFrameWorks Projection Mapping
	Filename: PlanetOrbit.h
*/

#ifndef PlanetOrbit_h
#define PlanetOrbit_h

#include "ofMain.h"
#include "FboSource.h"

class PlanetOrbit : public ofx::piMapper::FboSource {
    public:
//Default functions
        void setup();
        void update();
        void draw();
        void setName(string);
        void reset();
//Global variables I added
        float startTime;
        vector<float> noiseSeeds;
        float angleStep, stepSize, radius;
        int sunLocX, sunLocY;
        float t;
        int totalRays;
//Default ball functions
        void setupBalls();
        void updateBalls();
        void drawBalls(int x, int y, int w, int h);
        vector <ofVec2f> locations;
        vector <ofVec2f> speeds;
};

#endif /* PlanetOrbit_h */
