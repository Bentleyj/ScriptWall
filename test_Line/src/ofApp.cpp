#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// load the gui settings once we have them.
	string settingsPath = "settings/settings.xml";
	gui.setup(settingsPath);
	gui.loadFromFile(settingsPath);

	path.addVertex(200, 400);
	path.bezierTo(100, 100, 800, 100, 700, 400);

	ofBackground(0);

	targetVertIndex = 0;

	//ofSetBackgroundAuto(false);
}

//--------------------------------------------------------------
void ofApp::update(){
	line.setTarget(ofGetMouseX(), ofGetMouseY());
	line.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255);
	line.draw();
	//ofSetColor(255, 0, 0);
	//path.draw();
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
