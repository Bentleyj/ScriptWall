#include "WobblyLine.h"

WobblyLine::WobblyLine() {
	Line();
}

void WobblyLine::update() {
	updatePoint(0, target, speed);
	for (int i = 1; i < tail.getNumVertices(); i++) {
		updatePoint(i, tail.getVertex(i - 1), speed);
	}
}

void WobblyLine::updatePoint(int index, ofVec3f target, float speed) {
	ofVec3f vertPos = tail.getVertex(index);

	vertPos.x = ofLerp(vertPos.x, target.x, speed);
	vertPos.y = ofLerp(vertPos.y, target.y, speed);
	vertPos.z = ofLerp(vertPos.z, target.z, speed);

	tail.setVertex(index, vertPos);
}

void WobblyLine::updatePoint(int index, ofVec2f target, float speed) {
	updatePoint(index, ofVec3f(target), speed);
}