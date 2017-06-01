#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	font = new ofTrueTypeFont();

	font->load("fonts/peach-sundress/peach-sundress.ttf", 100, true, true, true);

	updateText('_');
	xOffset = 0;

	ofBackground(0);
	ofSetBackgroundAuto(false);
	
	textMesh.setMode(OF_PRIMITIVE_LINES);

	target = ofVec2f(0, 0);
	//target = textMesh.getVertex(0);
	lastPoint = point;
	point = ofVec2f(0, 0);
	targetIndex = 0;
}

void ofApp::updateText(char val) {
	string text = ""; 
	text += val;

	vector<ofTTFCharacter> characters = font->getStringAsPoints(text);

	for (int j = 0; j < characters.size(); j++) {
		// Get the outline of each character
		vector<ofPolyline> lines = characters[j].getOutline();

		for (int k = 0; k < lines.size(); k++) {

			// Get the vertices of all the points in each of the lines
			vector<ofPoint> points = lines[k].getVertices();

			//Go through all the points and add them to the meshes
			for (int i = 0; i < points.size(); i++) {
				textMesh.addVertex(ofVec3f(xOffset+points[i].x, points[i].y, 0));
				textMesh.addColor(ofColor(255));
				textMesh.addVertex(ofVec3f(xOffset+points[(i + 1) % points.size()].x, points[(i + 1) % points.size()].y, 0));
				textMesh.addColor(ofColor(255));
			}
		}
	}
	lastCharBoundingBox = font->getStringBoundingBox(text, 0, 0);
	xOffset += lastCharBoundingBox.width;
}

//--------------------------------------------------------------
void ofApp::update(){
	lastPoint = point;
	point.x = ofLerp(point.x, target.x, 0.2);
	point.y = ofLerp(point.y, target.y, 0.2);

	if ((point - target).length() < 0.5) {
		if (targetIndex >= textMesh.getNumVertices()-1)
		{
			//target = ofVec2f(ofGetWidth(), ofGetHeight());
		} 
		else {
			targetIndex++;
			target = textMesh.getVertex(targetIndex);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofTranslate(100, ofGetHeight()-100);
	float diff = (point - lastPoint).length();
	float col = ofMap(diff, 0, 10, 255, 0);
	ofSetColor(col);
	ofDrawLine(lastPoint, point);
	//textMesh.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	updateText(key);
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
