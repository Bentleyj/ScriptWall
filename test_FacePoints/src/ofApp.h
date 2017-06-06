#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
	struct contourKeyPoint {
		int index;
		ofVec2f start;
		ofVec2f end;
		int nearestIndex = -1;
	};
	public:
		void setup();
		void update();
		void draw();
		int findNearestNext(int index, vector<contourKeyPoint>* contours);

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

		ofVideoGrabber cam;
		ofxCv::ObjectFinder objectFinder;
		ofxCv::ContourFinder contourFinder;

		ofxPanel gui;
		ofParameter<float> minArea, maxArea, threshold, thresh1, thresh2;
		ofParameter<int> step, zoom;
		ofParameter<bool> holes;

		ofImage cropped, gray, edge, sobel;

		vector<vector<cv::Point>> contours;

		ofMesh mesh;

		ofVec2f lastPoint;
		ofVec2f point;
		ofVec2f target;

		float col;

		int targetIndex;

		bool finding;
		bool clearDrawing;
		int yOffset;
};
