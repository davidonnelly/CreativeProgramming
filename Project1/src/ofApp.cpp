//
//David Donnelly
//8720922535
//Homework 1: The Face
//
//Features: Lego-ish head
//Clicking on screen moves the head to that location
//Pressing 'f' toggles whether the head follow your cursor
//Pressing 'r' resets the head to the center of the screen
//Pressing 'n' toggles the nose
//Resising the window resizes the head as well
//It also blinks
//

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//general
	timer = 0;
	noseOn = true;
	windowWidth = 400;
	windowHeight = 400;
	ofBackground(ofColor::lightBlue);

	//Centering head
	headCenterX = windowWidth/2;
	headCenterY = windowHeight/2;
	headWidth = 110*(windowHeight/400);
	headHeight = 120*(windowHeight/400);
	
	//Centering eye
	eyeLeftCenterX = headCenterX - headWidth / 5;
	eyeLeftCenterY = headCenterY - headHeight/ 6;
	eyeRightCenterX = headCenterX + headWidth / 5;
	eyeRightCenterY = headCenterY - headHeight / 6;

	//Centering pupil in eye
	pupilLeftX = eyeLeftCenterX;
	pupilLeftY = eyeLeftCenterY;
	pupilRightX = eyeRightCenterX;
	pupilRightY = eyeRightCenterY;
	pupilSize = headWidth / 20;

	//Calcluating eyelid height
	eyelidLeftHeight = eyeLeftCenterY - headHeight/8 - headHeight / 4 + headHeight/16;
	eyelidRightHeight = eyeRightCenterY - headHeight / 8 - headHeight / 4 + headHeight / 16;
}

//--------------------------------------------------------------
void ofApp::update(){
	//re-sets up during resize
	if (resized) {
		headCenterX = windowWidth / 2;
		headCenterY = windowHeight / 2;
		headWidth = 110 * (windowHeight / 400);
		headHeight = 120 * (windowHeight / 400);
		ofBackground(ofColor::lightBlue);

		eyeLeftCenterX = headCenterX - headWidth / 5;
		eyeLeftCenterY = headCenterY - headHeight / 6;
		eyeRightCenterX = headCenterX + headWidth / 5;
		eyeRightCenterY = headCenterY - headHeight / 6;

		pupilLeftX = eyeLeftCenterX;
		pupilLeftY = eyeLeftCenterY;
		pupilRightX = eyeRightCenterX;
		pupilRightY = eyeRightCenterY;
		pupilSize = headWidth / 20;

		eyelidLeftHeight = eyeLeftCenterY - headHeight / 8 - headHeight / 4 + headHeight / 16;
		eyelidRightHeight = eyeRightCenterY - headHeight / 8 - headHeight / 4 + headHeight / 16;
		resized = false;
	}


	//blinks
	timer++;
	if (timer > 300 && timer< 300 + headHeight / 4 - headHeight / 16) {
		eyelidLeftHeight++;
		eyelidRightHeight++;
	}
	else if (timer >= 300 + headHeight / 4-headHeight / 16 && timer < 300 + headHeight / 2 - headHeight / 8) {
		eyelidLeftHeight--;
		eyelidRightHeight--;
	}
	else if (timer >= 300 + headHeight / 2 - headHeight / 16) {
		timer = 0;
	}


	//moves eyes with head
	if (moved) {
		eyelidLeftHeight = eyelidLeftHeight - eyeLeftCenterY + (headCenterY - headHeight / 6);
		eyelidRightHeight = eyelidRightHeight - eyeRightCenterY + (headCenterY - headHeight / 6);

		eyeLeftCenterX = headCenterX - headWidth / 5;
		eyeLeftCenterY = headCenterY - headHeight / 6;
		eyeRightCenterX = headCenterX + headWidth / 5;
		eyeRightCenterY = headCenterY - headHeight / 6;

		pupilLeftX = eyeLeftCenterX;
		pupilLeftY = eyeLeftCenterY;
		pupilRightX = eyeRightCenterX;
		pupilRightY = eyeRightCenterY;
		pupilSize = headWidth / 20;

		
		moved = false;
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	//Lego Head Base
	ofSetColor(ofColor::yellow);
	ofDrawRectRounded(headCenterX - (headWidth / 10), headCenterY - (headHeight / 2) - headHeight / 10, headWidth / 5, headHeight / 5, headWidth / 20);
	ofDrawRectRounded(headCenterX-(headWidth/2), headCenterY-(headHeight/2), headWidth, headHeight, headWidth/10);

	//Eyes
	ofSetColor(ofColor::white);
	ofDrawEllipse(eyeRightCenterX, eyeRightCenterY, headWidth / 5, headHeight / 4);
	ofDrawEllipse(eyeLeftCenterX, eyeLeftCenterY, headWidth / 5, headHeight / 4);

	//Pupils
	ofSetColor(ofColor::black);
	ofDrawCircle(pupilLeftX, pupilLeftY, headWidth / 20);
	ofDrawCircle(pupilRightX, pupilRightY, headWidth / 20);

	//Eyelids
	ofSetColor(ofColor::yellow);
	ofDrawRectangle(eyeLeftCenterX - headWidth / 8, eyelidLeftHeight, headWidth / 4, headHeight / 4);
	ofDrawRectangle(eyeRightCenterX - headWidth / 8, eyelidRightHeight, headWidth / 4, headHeight / 4);

	//mouth
	ofSetColor(ofColor::black);
	ofDrawLine(headCenterX - (headWidth / 6), headCenterY + (headHeight / 4), headCenterX + (headWidth / 6), headCenterY + (headHeight / 4));

	//nose
	if (noseOn) {
		ofSetColor(ofColor::fireBrick);
		ofDrawCircle(headCenterX, headCenterY, headWidth / 15);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'r') { //resets
		follow = false;
		moved = true;
		headCenterX = windowWidth/2;
		headCenterY = windowHeight/2;
	}
	else if (key == 'f') { //toggles follow
		follow = !follow;
	}
	else if (key == 'n') { //toggles nose
		noseOn = !noseOn;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	if (follow) {
		moved = true;
		headCenterX = x;
		headCenterY = y;;
	}
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	moved = true;
	headCenterX = x;
	headCenterY = y;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	resized = true;
	windowWidth = w;
	windowHeight = h;
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
