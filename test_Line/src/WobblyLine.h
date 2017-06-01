#pragma once

#include "Line.h"

class WobblyLine : public Line{

	public:
		//Constructor
		WobblyLine();
		// Functionality
		void update();
		// Setters and Getters

	private:
		void updatePoint(int index, ofVec3f target, float speed);
		void updatePoint(int index, ofVec2f target, float speed);
};
