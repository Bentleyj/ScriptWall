#include "ofApp.h"

#define NUM_LINE_VERTICES 100

//--------------------------------------------------------------
void ofApp::setup(){
	// load the gui settings once we have them.
	string settingsPath = "settings/settings.xml";
	gui.setup(settingsPath);
	gui.loadFromFile(settingsPath);

	for (int i = 0; i < NUM_LINE_VERTICES; i++) {
		line.addVertex(ofVec3f(ofGetWidth()/2, ofGetHeight()/2, 0));
	}

	ofBackground(0);
	line.setMode(OF_PRIMITIVE_LINE_STRIP);

	//ofSetBackgroundAuto(false);
}

//--------------------------------------------------------------
void ofApp::update(){
	line.setVertex(0, ofVec3f(ofGetMouseX(), ofGetMouseY(), 0));
	for (int i = 1; i < NUM_LINE_VERTICES; i++) {
		ofVec3f vertTarget = line.getVertex(i-1);
		ofVec3f vertPos = line.getVertex(i);

		vertPos.x = ofLerp(vertPos.x, vertTarget.x, 0.5);
		vertPos.y = ofLerp(vertPos.y, vertTarget.y, 0.5);

		line.setVertex(i, vertPos);

	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255);
	line.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
