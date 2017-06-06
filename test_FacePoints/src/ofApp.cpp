#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);

	objectFinder.setup(ofToDataPath("haarcascade_frontalface_default.xml"));
	objectFinder.setPreset(ObjectFinder::Fast);

	cropped.allocate(512, 512, OF_IMAGE_COLOR);

	mesh.setMode(OF_PRIMITIVE_LINES);
	cam.setup(640, 480);
	gui.setup();
	gui.add(minArea.set("Min area", 10, 1, 100));
	gui.add(maxArea.set("Max area", 200, 1, 500));
	gui.add(threshold.set("Threshold", 128, 0, 255));
	gui.add(thresh1.set("Canny Thresh 1", 128, 0, ofGetWidth()));
	gui.add(thresh2.set("Canny Thresh 2", 128, 0, ofGetHeight()));
	gui.add(holes.set("Holes", false));
	gui.loadFromFile("settings.xml");

	ofBackground(0);

	target = ofVec2f(0, 0);
	lastPoint = point;
	point = ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2);
	targetIndex = 0;

	ofSetBackgroundAuto(false);

	finding = true;
	clearDrawing = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	if (finding) {
		cam.update();
		if (cam.isFrameNew()) {
			objectFinder.update(cam);
			if (objectFinder.size() > 0) {
				cv::Rect roi = toCv(objectFinder.getObject(0));
				Mat camMat = toCv(cam);
				Mat croppedCamMat(camMat, roi);
				resize(croppedCamMat, cropped);
				cropped.update();
			}
			convertColor(cropped, gray, CV_RGB2GRAY);
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
	else {
		lastPoint = point;

		point.x = target.x;
		point.y = target.y;
		if (targetIndex < mesh.getNumVertices())
		{
			target = mesh.getVertex(targetIndex);
			targetIndex++;
		}
		else {
			finding = true;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (clearDrawing) {
		ofSetColor(0);
		ofDrawRectangle(edge.getWidth(), 0, edge.getWidth(), edge.getHeight());
		clearDrawing = false;
	}
	ofSetColor(255);
	edge.draw(0, 0);
	float dist = (point - lastPoint).length();
	col = ofMap(dist, 100, 15, 0, 255, true);
	ofSetColor(col, col, 0);
	ofPushMatrix();
	ofTranslate(edge.getWidth(), 0);
	ofDrawLine(lastPoint, point);
	ofPopMatrix();
	//mesh.draw();
	gui.draw();

	ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), ofGetWidth() - 100, ofGetHeight() - 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	point = ofVec2f(0, 0);
	target = ofVec2f(0, 0);
	targetIndex = 0;
	finding = false;
	clearDrawing = true;
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
	cout << mesh.getNumVertices()<<endl;
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
