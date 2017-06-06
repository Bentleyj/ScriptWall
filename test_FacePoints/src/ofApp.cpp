#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void ofApp::setup(){
	mesh.setMode(OF_PRIMITIVE_LINES);
	cam.setup(640, 480);
	gui.setup();
	gui.add(minArea.set("Min area", 10, 1, 100));
	gui.add(maxArea.set("Max area", 200, 1, 500));
	gui.add(threshold.set("Threshold", 128, 0, 255));
	gui.add(thresh1.set("Canny Thresh 1", 128, 0, ofGetWidth()));
	gui.add(thresh2.set("Canny Thresh 2", 128, 0, ofGetHeight()));

	ofBackground(0);
	gui.add(holes.set("Holes", false));
}

//--------------------------------------------------------------
void ofApp::update(){
	cam.update();
	if (cam.isFrameNew()) {
		convertColor(cam, gray, CV_RGB2GRAY);
		Canny(gray, edge, thresh1, thresh2, 3);
		Sobel(gray, sobel);
		gray.update();
		sobel.update();
		edge.update();


		contourFinder.setMinAreaRadius(minArea);
		contourFinder.setMaxAreaRadius(maxArea);
		contourFinder.setThreshold(threshold);
		contourFinder.findContours(edge);
		contourFinder.setFindHoles(holes);


	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	//cam.draw(0, 0);
	ofSetColor(255);
	edge.draw(0, 0);
	//contourFinder.draw();
	ofSetColor(255, 255, 0);
	mesh.draw();
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	mesh.clear();
	contours = contourFinder.getContours();
	for (int i = 0; i < contours.size(); i++) {
		for (int j = 0; j < contours[i].size()-1; j++) {
			float x1 = contours[i][j].x;
			float y1 = contours[i][j].y;

			float x2 = contours[i][j+1].x;
			float y2 = contours[i][j+1].y;

			mesh.addVertex(ofVec3f(x1, y1, 0));
			mesh.addVertex(ofVec3f(x2, y2, 0));

		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
