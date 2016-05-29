#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main() {
	ofAppGlutWindow window; // create a window
							// set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
							//ofSetupOpenGL(&window, 1024, 768, OF_WINDOW);
	ofSetupOpenGL(&window, 1024, 768, OF_FULLSCREEN);
	ofRunApp(new ofApp()); // start the app
}
