#pragma once

#include "ofMain.h"
#include "ofxTSPSReceiver.h"
#include "ofxFontStash.h"
#include "ofxTwitter.h"

class ofApp : public ofBaseApp {
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
	void addTweets(string search);

	ofxTSPS::Receiver tspsReceiver;

	int timer;
	int lines;

	ofTrueTypeFont myTempFont;
	ofxFontStash myFont;
	ofxTwitter::RESTClient client;

	vector<float> positions;
	vector<float> positions2;
	vector<float> lengths;
	vector<float> velocities;
	vector<string> strings;
	vector<string> tweets;
};

