#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	font = new ofTrueTypeFont();

	font->load("fonts/HelveticaNeueBd.ttf", 50, true, true, true);

	string text = "Test";

	ofRectangle rect = font->getStringBoundingBox(text, 0, 0);

	vector<ofTTFCharacter> characters = font->getStringAsPoints(text);

	for (int j = 0; j < characters.size(); j++) {
		// Get the outline of each character
		ofMesh inputMesh = characters[j].getTessellation();

		for (int i = 0; i < inputMesh.getNumVertices(); i++) {
			ofPoint vertex = inputMesh.getVertex(i);
			//inputMesh.setVertex(i, ofPoint(vertex.x - rect.width / 2, -vertex.y + rect.height / 2.0, 0));
			inputMesh.addColor(ofColor(255));
		}

		for (int i = 0; i < inputMesh.getNumVertices()-1; i++) {
			textMesh.addVertex(inputMesh.getVertex(i));
			textMesh.addVertex(inputMesh.getVertex(i+1));

		}
	}

	ofBackground(0);
	
	textMesh.setMode(OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	textMesh.draw();
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
