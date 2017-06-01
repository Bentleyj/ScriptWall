#pragma once

#include "ofMain.h"

class Line : public ofBaseApp{

	public:
		//Constructor
		Line();
		// Functionality
		void setup();
		virtual void update();
		void draw();
		// Setters and Getters
		void setCol(ofColor _val) { col = _val; };
		ofColor getCol() { return col; };

		void setSpeed(float _val) { speed = _val; };
		float getSpeed() { return speed; };

		void setTarget(ofVec3f _val) { target = _val; };
		void setTarget(ofVec2f _val) { target = ofVec3f(_val); };
		void setTarget(float _x, float _y) { setTarget(ofVec2f(_x, _y)); };
		ofVec3f getTarget() { return target; };

	protected:
		virtual void updatePoint(int index, ofVec3f target, float speed);
		virtual void updatePoint(int index, ofVec2f target, float speed);

		ofColor col;
		ofMesh tail;
		vector<ofVec3f> tailPoints;
		ofVec3f target;
		float speed;
};
