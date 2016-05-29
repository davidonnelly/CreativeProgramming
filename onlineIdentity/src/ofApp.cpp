// David Donnelly
// 872922535
//
// Online Identity
// This program takes input from TSPS and fetches from twitter phrases
// starting with 'you are' and forms the outline of the user's body in effort
// to look into one's identity on the internet

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofBackground(0);
	tspsReceiver.connect(12000);
	lines = ofGetHeight() / 32;
	ofSetVerticalSync(true);

	//fonts setup
	myFont.setup("GeosansLight.ttf", 1.0, 1024, false, 8, 1.0);
	myTempFont.loadFont("GeosansLight.ttf", 32, true, true);
	ofBackground(255);


	//twitter setup
	auto credentials = ofxHTTP::OAuth10Credentials::fromFile("credentials.json");
	client.setCredentials(credentials);
	ofxTwitter::StreamingRequestParameters params;
	params.setFilterLevel(ofx::Twitter::BaseFilterStreamingRequestParameters::FilterLevel::NONE);
	addTweets("you are");
	addTweets("you're");
	addTweets("you are so");
	addTweets("you really are");
	addTweets("you really are so");
	
	//assigning tweets to strings and strings to lines
	int tweetPos = 0;
	for (int i = 0; i <= lines; i++) {
		positions.push_back(0);
		positions2.push_back(ofGetWidth()*1.5);
		velocities.push_back(ofRandom(-4.5f, -7.3f));
		lengths.push_back(0);
		strings.push_back(tweets[tweetPos]);
		tweetPos++;
		if (tweetPos >= tweets.size()) {
			tweetPos = 0;
		}
		while (myTempFont.stringWidth(strings[i]) < ofGetWidth()+100) {
			strings[i] += "        " + tweets[tweetPos];
			tweetPos++;
			if (tweetPos >= tweets.size()) {
				tweetPos = 0;
			}
		}
		lengths[i] = myTempFont.stringWidth(strings[i]) + 100;
		positions2[i] = lengths[i];
	}
}

//--------------------------------------------------------------
void ofApp::update() {
	//moving lines left and then moving them back when they reach the edge
	for (int i = 0; i <= lines; i++) {
		int vel = velocities[i];
		positions[i] += vel;
		positions2[i] += vel;

		if (positions[i] < -lengths[i]){
			positions[i] = positions2[i] + lengths[i];
		}
		if (positions2[i] < -lengths[i]) {
			positions2[i] = positions[i]+lengths[i];
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	//drawing the fonts
	ofSetColor(0);
	for (int i = 1; i <= lines; i++) {
		myFont.draw(strings[i],32, positions[i], 32 * i);
		myFont.draw(strings[i], 32, positions2[i], 32 * i);
	}


	//drawing the negative space from the user
	vector<ofxTSPS::Person*> people = tspsReceiver.getPeople();
	for (int i = 0; i < people.size(); i++) {
		ofSetColor(255);
		ofFill();
		ofBeginShape();
		ofEnableSmoothing();
		for (int j = 0; j < people[i]->contour.size(); j++) {
			ofVertex(people[i]->contour[j].x * ofGetWidth(), people[i]->contour[j].y * ofGetHeight());
		}
		ofEndShape();
	}
}

//add tweets based on search
void ofApp::addTweets(string search) {
	auto result = client.search(search);
	for (auto& status : result->statuses())
	{
		string str = status.text();
		if (str.find(search) != -1) {
			str = str.substr(str.find(search));

			if (str.find('.') != -1) {
				str = str.substr(0, str.find('.')+1);
			}
			if(str.find('!') != -1) {
				str = str.substr(0, str.find('!')+1);
			}
			if (str.find('?') != -1) {
				str = str.substr(0, str.find('?') + 1);
			}
			if (str.find("http") != -1) {
				str = str.substr(0, str.find("http"));
			}

			tweets.push_back(str);
		}
	}
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {}
//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}
//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}
//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}
//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
