#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

private:
	//drawing coordinates
	int headCenterX;
	int headCenterY;
	int headWidth;
	int headHeight;

	int eyeLeftCenterX;
	int eyeLeftCenterY;
	int eyeRightCenterX;
	int eyeRightCenterY;

	int pupilLeftX;
	int pupilLeftY;
	int pupilRightX;
	int pupilRightY;
	int pupilSize;

	int eyelidLeftHeight;
	int eyelidRightHeight;

	//extras
	int windowWidth;
	int windowHeight;
	int timer;
	bool resized;
	bool moved;
	bool follow;
	bool noseOn;
		
};
