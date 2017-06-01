#include "Line.h"

#define NUM_TAIL_VERTICES 100

Line::Line() {
	for (int i = 0; i < NUM_TAIL_VERTICES; i++) {
		tail.addVertex(ofVec3f(ofGetWidth() / 2, ofGetHeight() / 2, 0));
	}

	tail.setMode(OF_PRIMITIVE_LINE_STRIP);

	col = ofColor(255);

	speed = 0.5;
}

void Line::setup() {

}

void Line::update() {
	updatePoint(0, target, speed);
	for (int i = 1; i < tail.getNumVertices(); i++) {
		updatePoint(i, tail.getVertex(i - 1), speed);
	}
}

void Line::draw() {
	ofSetColor(col);
	tail.draw();
}

void Line::updatePoint(int index, ofVec3f target, float speed) {

}

void Line::updatePoint(int index, ofVec2f target, float speed) {

}