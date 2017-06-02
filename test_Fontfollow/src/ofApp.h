#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxFontStash.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void updateText(char val);
		void updateText(string val);


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

		ofxPanel gui;
		ofParameter<float> noiseStep;
		ofParameter<float> noiseMagnitude;
		ofParameter<ofColor> col;

		ofFbo drawingArea;

		ofTrueTypeFont* font;

		ofMesh textMesh;

		string text = "";

		ofVec2f lastPoint;
		ofVec2f point;
		ofVec2f target;
		ofRectangle lastCharBoundingBox;
		float xOffset;
		int targetIndex;


		float noise;
		
};
