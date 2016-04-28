#pragma once

#include "ofMain.h"
#include "ofxInkSim.h"
#include "SampleBrush.h"
#include "GUI.h"
#include "ofxTwitter.h"

struct coordinate {
	double x;
	double y;
};

class ofApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	void fetchTweet(char* s);

private:

	GUI gui;

	ofxInkSim inkSim;
	SampleBrush brush;
	ofxTwitter::RESTClient client;


	char* referenceSheet;
	unordered_map<char, coordinate> mapping;
	std::string text;
	int currentIndex;

	float myX, myY, destX, destY;
	float speed;
	bool newChar, moving, singleWord;

	bool toggleGrid, toggleNodes, toggleMirror, showTweet;
};
