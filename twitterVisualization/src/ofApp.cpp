// David Donnelly
// 872922535
// Creative Progamming
// twitterVisualization

// Fetches a tweet from twitter and then creates an abstract art visualization
// in ink based off of the tweet

#include "ofApp.h"
#include "ofxInkSim.h"
#include "ofxInkSim.h"

void ofApp::setup()
{
	//ink and gui setup
	inkSim.setup();
	gui.setup(inkSim.getUniformInfo());
	gui.toggleVisible();

	//Twitter setup
	auto credentials = ofxHTTP::OAuth10Credentials::fromFile("credentials.json");
	client.setCredentials(credentials);
	ofxTwitter::StreamingRequestParameters params;
	params.setFilterLevel(ofx::Twitter::BaseFilterStreamingRequestParameters::FilterLevel::NONE);
	fetchTweet("love");

	//setting up mapping and references
	referenceSheet = "0u[k?n-9\"$!}(ah=%~4i)mbcx8jr&;3'ws167>@<t^p\\f*e#/.:o2]{gv5+l,qz_dy";
	for (int i = 0; i < 66; i++) {
		coordinate *pos = new coordinate;
		pos->x = ((i % 11)*ofGetWidth()) / 10;
		pos->y = (((int)(i / 11))*ofGetWidth()) / 7;
		mapping.insert({ referenceSheet[i], *pos });
		if ((referenceSheet[i] >= 97) && (referenceSheet[i] <= 122)) {
			char c = referenceSheet[i] - 32;
			mapping.insert({ c, *pos });
		}
	}

	//text = "hello world";
	currentIndex = 0;
	toggleMirror = false;
	newChar = true;
	moving = true;
	speed = 4;

}

void ofApp::update()
{
	if (moving) {
		//sets charater it goes to
		if (newChar) {
			myX = mapping[text[currentIndex]].x;
			myY = mapping[text[currentIndex]].y;
			destX = mapping[text[currentIndex + 1]].x;
			destY = mapping[text[currentIndex + 1]].y;
			newChar = false;
		}

		myX += 0.005*speed*(destX - myX);
		myY += 0.005*speed*(destY - myY);

		//changes the point it heads when it reaches the last spot
		if ((abs(destY - myY) <= 2) && (abs(destX - myX) <= 2)) {
			if (currentIndex < text.length() - 2) {
				currentIndex++;
				if (text[currentIndex + 1] == ' ') {
					currentIndex += 2;
					inkSim.stopStroke(&brush);
				}
				newChar = true;
			}
			else {
				moving = false;
			}
		}
	}

	inkSim.update();
}

void ofApp::draw()
{
	//draws ink strokes
	if (moving) {
		ofColor c = ofColor::lightBlue;
		inkSim.stroke(&brush, myX, myY, getInkColor(c.getHueAngle(), 255, 10));
		if (toggleMirror) {
			inkSim.stroke(&brush, ofGetWidth() - myX, myY, getInkColor(c.getHueAngle(), 255, 10));
		}
	}

	//draws ink and gui
	inkSim.draw();
	gui.draw();

	//draws tweet if toggled on
	if (showTweet) {
		ofDrawBitmapStringHighlight(text, 10, ofGetHeight() - 20);
	}
}

//sets a tweet to text using the search term s
void ofApp::fetchTweet(char* s) {
	auto result = client.search(s);
	if (result->isSuccess()) {
		for (auto& status : result->statuses()) {
			text = status.text();
		}
	}
	else {
		for (auto& error : result->errors()) {
			std::cout << error.code() << " / " << error.message() << std::endl;
		}
		std::cout << result->error() << std::endl;
	}
}



void ofApp::keyPressed(int key)
{
	if (key == '1')
	{
		inkSim.setDrawMode(ofxInkSim::INKFIX);
	}
	else if (key == '2')
	{
		inkSim.setDrawMode(ofxInkSim::INKSURF);
	}
	else if (key == '3')
	{
		inkSim.setDrawMode(ofxInkSim::INKFLOW);
	}
	else if (key == '4')
	{
		inkSim.setDrawMode(ofxInkSim::WATERFLOW);
	}
	else if (key == 'd')
	{
		inkSim.toggleDebug();
	}
	else if (key == ' ')
	{
		gui.toggleVisible();
	}
	else if (key == 'r')
	{
		gui.resetToDefault();
	}
	else if (key == 'c')
	{
		inkSim.clear();
	}
	else if (key == 't') {
		showTweet = !showTweet;
	}
}

void ofApp::keyReleased(int key) {}
void ofApp::mouseMoved(int x, int y) {}
void ofApp::mousePressed(int x, int y, int button) {}
void ofApp::windowResized(int w, int h) {}
void ofApp::gotMessage(ofMessage msg) {}
void ofApp::dragEvent(ofDragInfo dragInfo) {}
void ofApp::mouseDragged(int x, int y, int button){}
void ofApp::mouseReleased(int x, int y, int button){}