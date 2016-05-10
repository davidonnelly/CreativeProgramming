// David Donnelly
// 872922535
// Video Manipulation
// Shows the camera with half of the image inverted
// Dragging on the window up and down changes where the split is
// Pressing 'f' flips which side is inverted


#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	camWidth = ofGetWidth();
	camHeight = ofGetHeight();
	myY = ofGetHeight() / 2;

	vidGrabber.initGrabber(camWidth, camHeight);
	videoInverted.allocate(camWidth, camHeight, OF_PIXELS_RGB);
	videoTexture.allocate(videoInverted);
}


//--------------------------------------------------------------
void ofApp::update() {
	vidGrabber.update();

	ofPixels& pixels = vidGrabber.getPixels();
	if (myY > 0 && myY < camHeight) {
		if (!flip) {
			for (int i = 0; i < 3 * camWidth*myY; i++) {
				videoInverted[i] = 255 - pixels[i];
			}
			for (int i = 3 * camWidth*myY; i < pixels.size(); i++) {
				videoInverted[i] = pixels[i];
			}
		}
		else {
			for (int i = 0; i < 3 * camWidth*myY; i++) {
				videoInverted[i] = pixels[i];
			}
			for (int i = 3 * camWidth*myY; i < pixels.size(); i++) {
				videoInverted[i] = 255 - pixels[i];
			}
		}
	}
	videoTexture.loadData(videoInverted);
}

//--------------------------------------------------------------
void ofApp::draw() {
	videoTexture.draw(0, 0);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'f') {
		flip = !flip;
	}
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	myY = y;
}


void ofApp::keyReleased(int key) {}
void ofApp::mouseMoved(int x, int y) {}
void ofApp::mousePressed(int x, int y, int button) {}
void ofApp::mouseReleased(int x, int y, int button) {}
void ofApp::mouseEntered(int x, int y) {}
void ofApp::mouseExited(int x, int y) {}
void ofApp::windowResized(int w, int h) {}
void ofApp::gotMessage(ofMessage msg) {}
void ofApp::dragEvent(ofDragInfo dragInfo) {}
