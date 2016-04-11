#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	by = 200;
	bx = 500;
	xVel = 0;
	yVel = 0;
	yAcc = 4;
}

//--------------------------------------------------------------
void ofApp::update() {
	if (autoMatic) {
		counter++;

		if (counter > 450) {
			by = 200;
			yVel = 0;
			finished = false;
			counter = 0;
		}
	}
	if (!finished) {

		if (by >= ofGetHeight() - 13) {
			yVel = -yVel;
			by = ofGetHeight() - 13;
			if (yVel > -.5) {
				yVel = 0;
				by = ofGetHeight() - 13;
				finished = true;
			}
		}

		yVel += yAcc;
		by = by + yVel;
	}

	if (move) {
		bx = ofGetMouseX();
		by = ofGetMouseY();
		yVel = 0;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetColor(ofColor::darkGreen);
	ofDrawCircle(bx, by, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'a') {
		autoMatic = !autoMatic;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	if (ofDist(x, y, bx, by) <= 15){
		move = true;
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if (move) {
		move = false;
		finished = false;
	}
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	finished = false;
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
