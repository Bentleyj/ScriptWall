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

	ofSetLineWidth(1);
	cam.setup(640, 480);
	gui.setup();
	gui.add(minArea.set("Min area", 10, 1, 100));
	gui.add(maxArea.set("Max area", 200, 1, 500));
	gui.add(threshold.set("Threshold", 128, 0, 255));
	gui.add(thresh1.set("Canny Thresh 1", 128, 0, ofGetWidth()));
	gui.add(thresh2.set("Canny Thresh 2", 128, 0, ofGetHeight()));
	gui.add(zoom.set("Inverse Zoom", 0, 0, 100));
	gui.add(holes.set("Holes", false));
	gui.add(step.set("Step", 1, 1, 30));
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
				ofRectangle rect = objectFinder.getObject(0);
				rect.width += zoom * 2;
				rect.height += zoom * 2;
				rect.x -= zoom; 
				rect.y -= zoom;
				cv::Rect roi = toCv(rect);
				cv::Rect BiggerROI = roi;


				Mat camMat = toCv(cam);
				if ((BiggerROI.x + BiggerROI.width) > camMat.cols - 1) {
					BiggerROI.width = camMat.cols - 1 - BiggerROI.x;
					BiggerROI.height = BiggerROI.width;
				}
				if ((BiggerROI.y + BiggerROI.height) > camMat.rows - 1) {
					BiggerROI.height = camMat.rows - 1 - BiggerROI.y;
					BiggerROI.width = BiggerROI.height;
				}
				if (BiggerROI.x > cam.getWidth() - 1) {
					BiggerROI.x = cam.getWidth() - 1;
				}
				if (BiggerROI.y > cam.getHeight() - 1) {
					BiggerROI.y = cam.getHeight() - 1;
				}
				if (BiggerROI.x < 1) {
					BiggerROI.x = 1;
				}
				if (BiggerROI.y < 1) {
					BiggerROI.y = 1;
				}

				Mat croppedCamMat(camMat, BiggerROI);
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
			targetIndex += step;
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
	if (!finding) {
		if (targetIndex < mesh.getNumColors()) {
			ofSetColor(mesh.getColor(targetIndex));
		}
		else {
			ofSetColor(255, 0, 0);
		}
		ofPushMatrix();
		ofTranslate(edge.getWidth(), 0);
		ofDrawLine(lastPoint, point);
		ofPopMatrix();
	}
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
	// store the first and last point of each centroid
	vector<contourKeyPoint> contourDefs;
	for (int i = 0; i < contours.size(); i++) {
		contourKeyPoint keyPoint;
		int lastIndex = contours[i].size() - 1;
		keyPoint.index = i;
		keyPoint.start = ofVec2f(contours[i][0].x, contours[i][0].y);
		keyPoint.end = ofVec2f(contours[i][lastIndex].x, contours[i][lastIndex].y);
		contourDefs.push_back(keyPoint);
	}

	int i = 0;
	while (1) {
		int nearestIndex = findNearestNext(i, &contourDefs);
		if (nearestIndex == -1) {
			contourDefs[i].nearestIndex = -1;
			break;
		}
		contourDefs[i].nearestIndex = nearestIndex;
		i = nearestIndex;
	}

	for (int i = 0; i != -1; i = contourDefs[i].nearestIndex) {
		for (int j = 0; j < contours[i].size()-1; j++) {
			float x = contours[i][j].x;
			float y = contours[i][j].y;

			mesh.addVertex(ofVec3f(x, y, 0));
			ofColor col = (j < 3) ? ofColor(0) : ofColor(255);
			mesh.addColor(col);
		}
	}
}

int ofApp::findNearestNext(int index, vector<contourKeyPoint>* contours) {
	int nearestIndex = -1;
	float minDist = 10000;
	for (int i = 0; i < contours->size(); i++) {
		if (i == index || (*contours)[i].nearestIndex != -1) { }
		else {
			float dist = ((*contours)[index].end - (*contours)[i].start).length();
			if (dist < minDist) {
				minDist = dist;
				nearestIndex = i;
			}
		}
	}
	return nearestIndex;
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
