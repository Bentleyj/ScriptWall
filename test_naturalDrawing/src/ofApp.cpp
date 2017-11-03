#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	points.push_back(ofVec2f(100, 110));
	points.push_back(ofVec2f(150, 200));
	points.push_back(ofVec2f(200, 200));
	points.push_back(ofVec2f(240, 110));

	gui.setup("Settings", "settings/settings.xml");
	gui.add(range.set("Range", 1, 1, 50));
	gui.add(dampening.set("Dampening", 0.5, 0.0, 1.0));
	gui.add(attraction.set("Attraction", 0.5, 0.0, 2.0));
	gui.loadFromFile("settings/settings.xml");

	pos.set(points[0]);
	index = 1;


	for (int i = 0; i < 5; i++) {
		path.arc(i * 50 + 20, i * 50 + 20, i * 40 + 10, i * 40 + 10, 0, 360); // creates a new ofSubPath
		path.close();
	}

	ofBackground(ofColor(25));

	ofSetBackgroundAuto(false);

}

//--------------------------------------------------------------
void ofApp::update(){
	pos.attraction = attraction;
	pos.damping = dampening;
	pos.update();
	pos.target(points[index]);
	ofVec2f diff = pos.val - points[index];
	float dist = diff.length();
	if (dist < 10) {
		index++;
		if (index >= points.size()) {
			index = 0;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	for (int i = 0; i < points.size(); i++) {
		ofFill();
		ofSetColor(255);
		ofDrawCircle(points[i], 2);
		ofNoFill();
		ofSetColor(255, 0, 0);
		ofDrawCircle(points[i], range);
	}

	ofSetColor(255, 255, 0);
	ofDrawCircle(pos.val, 2);

	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == ' ')
		ofClear(0);
	else if (key == 'r') {
		points.clear();
		int numPoints = ofRandom(100);
		for (int i = 0; i < numPoints; i++) {
			points.push_back(ofVec2f(ofRandom(range, ofGetWidth() - range), ofRandom(range, ofGetHeight() - range)));
		}
		index = 0;
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
