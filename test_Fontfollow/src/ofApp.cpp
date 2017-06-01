#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	font = new ofTrueTypeFont();

	font->load("fonts/peach-sundress/peach-sundress.ttf", 100, true, true, true);

	string text = "James Bentley\nMathilde Steen\nPete Hellicar\nNaho Matsuda";

	ofRectangle rect = font->getStringBoundingBox(text, 0, 0);

	vector<ofTTFCharacter> characters = font->getStringAsPoints(text);

	for (int j = 0; j < characters.size(); j++) {
		// Get the outline of each character
		vector<ofPolyline> lines = characters[j].getOutline();

		for (int k = 0; k < lines.size(); k++) {

			// Get the vertices of all the points in each of the lines
			vector<ofPoint> points = lines[k].getVertices();

			//Go through all the points and add them to the meshes
			for (int i = 0; i < points.size(); i++) {
				textMesh.addVertex(ofVec3f(points[i].x, points[i].y, 0));
				textMesh.addColor(ofColor(255));
				textMesh.addVertex(ofVec3f(points[(i + 1) % points.size()].x, points[(i + 1) % points.size()].y, 0));
				textMesh.addColor(ofColor(255));
			}
		}
	}

	ofBackground(0);
	ofSetBackgroundAuto(false);
	
	textMesh.setMode(OF_PRIMITIVE_LINES);

	target = textMesh.getVertex(0);
	lastPoint = point;
	point = ofVec2f(0, 0);
	targetIndex = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
	lastPoint = point;
	point.x = ofLerp(point.x, target.x, 0.1);
	point.y = ofLerp(point.y, target.y, 0.1);

	if ((point - target).length() < 0.5) {
		targetIndex++;
		if (targetIndex >= textMesh.getNumVertices())
		{
			target = ofVec2f(ofGetWidth(), ofGetHeight());
		} 
		else {
			target = textMesh.getVertex(targetIndex);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofTranslate(0, ofGetHeight());
	ofDrawLine(lastPoint, point);
	//textMesh.draw();
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
