#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	string settingsPath = "settings/settings.xml";
	gui.setup(settingsPath);

	gui.add(noiseStep.set("Wander Step", 0.0001, 0.0, 0.01));
	gui.add(noiseMagnitude.set("Wander Speed", 1.0, 0.0, 100.0));
	gui.add(col.set("Color", ofColor(255)));

	gui.loadFromFile(settingsPath);

	drawingArea.allocate(ofGetWidth(), ofGetHeight());

	font = new ofTrueTypeFont();

	font->load("fonts/peach-sundress/peach-sundress.ttf", 100, true, true, true);
	
	xOffset = 0;
	updateText('_');

	ofBackground(0);
	//ofSetBackgroundAuto(false);
	ofSetFrameRate(120);
	
	textMesh.setMode(OF_PRIMITIVE_LINES);

	target = ofVec2f(0, 0);
	lastPoint = point;
	point = ofVec2f(ofGetWidth()/2, ofGetHeight()/2);
	targetIndex = 0;
}

void ofApp::updateText(char val) {
	string text = "";
	text += val;

	updateText(text);
}

void ofApp::updateText(string val) {
	string text = val;

	vector<ofTTFCharacter> characters = font->getStringAsPoints(text);

	for (int j = 0; j < characters.size(); j++) {
		// Get the outline of each character
		vector<ofPolyline> lines = characters[j].getOutline();

		for (int k = 0; k < lines.size(); k++) {

			// Get the vertices of all the points in each of the lines
			vector<ofPoint> points = lines[k].getVertices();

			//Go through all the points and add them to the meshes
			for (int i = 0; i < points.size(); i++) {
				textMesh.addVertex(ofVec3f(point.x + points[i].x, point.y + points[i].y, 0));
				textMesh.addColor(ofColor(255));
				textMesh.addVertex(ofVec3f(point.x + points[(i + 1) % points.size()].x, point.y + points[(i + 1) % points.size()].y, 0));
				textMesh.addColor(ofColor(255));
			}
		}
	}
	lastCharBoundingBox = font->getStringBoundingBox(text, 0, 0);
	xOffset += lastCharBoundingBox.width;
}

//--------------------------------------------------------------
void ofApp::update(){

	if (targetIndex >= textMesh.getNumVertices() - 1)
	{
		col = ofColor(127);
		targetIndex = textMesh.getNumVertices() + 1;
		//cout << ofNoise(noise) << endl;
		target.x += ofMap(ofNoise(noise, noise + 100), 0.0, 1.0, -1.0, 1.0) * noiseMagnitude;
		//cout<<point.x<<endl;
		target.y += ofMap(ofNoise(noise + 20000, noise + 500), 0.0, 1.0, -1.0, 1.0) * noiseMagnitude;
		noise += noiseStep;
	}
	else {
		col = ofColor(255);
	}

	lastPoint = point;
	//cout << "Vertex List Size: " << textMesh.getNumVertices() << endl;
	//cout << "targetIndex: " << targetIndex << endl;

	point.x = target.x;
	point.y = target.y;
	if (targetIndex < textMesh.getNumVertices())
	{
		target = textMesh.getVertex(targetIndex);
		targetIndex += 10;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	drawingArea.begin();
	ofSetColor(col);
	ofDrawLine(lastPoint, point);
	drawingArea.end();

	ofSetColor(255);
	drawingArea.draw(0, 0);

	ofSetColor(255, 0, 0);
	ofNoFill();
	ofDrawCircle(target, 20);

	gui.draw();

	ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), ofGetWidth() - 100, ofGetHeight() - 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	text += key;
	if (key == OF_KEY_RETURN) {
		updateText(text);
		text = "";
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
