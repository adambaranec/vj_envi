#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	loopsDir.open("loops");
	loopsDir.allowExt("mp4");
	loopsDir.listDir();
	loopsSize = loopsDir.size();
	for (int i = 0; i < loopsSize; i++) {
		ofVideoPlayer player;
		player.load(loopsDir.getPath(i));
		player.setVolume(0.0f);
		player.setLoopState(OF_LOOP_NORMAL);
		players.push_back(player);
	}
	texturesDir.open("textures");
	texturesDir.allowExt("png");
	texturesDir.allowExt("jpg");
	texturesDir.listDir();
	texturesSize = texturesDir.size();
	for (int i = 0; i < texturesSize; i++) {
		ofImage image;
		image.load(texturesDir.getPath(i));
		textures.push_back(image);
	}
	//---------------------------------------------
	customShader.load("vertex.vert", "shaders/custom/custom.frag");
	feedbackShader.load("vertex.vert", "shaders/feedback/feedback.frag");
	customShader.begin();
	for (int i = 0; i < textures.size(); i++) {
		string name = "tex[" + ofToString(i) + "]";

		// Find the location once
		GLint loc = glGetUniformLocation(customShader.getProgram(), name.c_str());

		// Store it for later
		texLocs.push_back(loc);

		// Optional: Pre-link the index to the unit ID here as well
		if (loc != -1) {
			glUniform1i(loc, i + 1);
		}
	}
	customShader.end();
	//---------------------------------------------
	mainBuffer.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	prevBuffer.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	nextBuffer.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	//---------------------------------------------
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofHideCursor();
	ofEnableSmoothing();
	ofEnableDepthTest();
	/*
	camera.setGlobalPosition(0, 0, 1);
	camera.setFov(45);
	camera.setNearClip(0.1);
	camera.setFarClip(1000);
	*/
	//---------------------------------------------
	ofSoundStreamSettings settings;
	settings.numOutputChannels = 0;
	settings.numInputChannels = 6;
	settings.bufferSize = 256;
	settings.setInDevice(soundStream.getMatchingDevices("Focusrite USB ASIO")[0]);
	settings.setInListener(this);
	soundStream.setup(settings);
}

//--------------------------------------------------------------
void ofApp::update() {
}
//--------------------------------------------------------------
void ofApp::draw(){
	for (int i = 0; i < textures.size(); i++) {
		int unit = i + 1;
		textures[i].getTexture().bind(unit);
		if (texLocs[i] != -1) {
			glUniform1i(texLocs[i], unit);
		}
	}
	ofSetRectMode(OF_RECTMODE_CORNER);
	ofClear(0, 0, 0, 255);
	if (!feedback) {
		customShader.begin();
		customShader.setUniform1f("time", ofGetElapsedTimef());
		customShader.setUniform1f("amp", amplitude);
		customShader.setUniform1f("aspect", (float)ofGetWidth() / (float)ofGetHeight());
		customShader.setUniform2f("resolution", (float)ofGetWidth(), (float)ofGetHeight());
		ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
		customShader.end();
	}
	else {
		nextBuffer.begin();
		ofClear(0, 0, 0, 255);
		customShader.begin();
		customShader.setUniform1f("time", ofGetElapsedTimef());
		customShader.setUniform1f("amp", amplitude);
		customShader.setUniform1f("aspect", (float)ofGetWidth() / (float)ofGetHeight());
		customShader.setUniform2f("resolution", (float)ofGetWidth(), (float)ofGetHeight());
		ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
		customShader.end();
		nextBuffer.end();

		mainBuffer.begin();
		ofClear(0, 0, 0, 255);
		feedbackShader.begin();
		feedbackShader.setUniform1i("mode", feedbackMode);
		feedbackShader.setUniformTexture("nextBuffer", nextBuffer.getTexture(), 0);
		feedbackShader.setUniformTexture("prevBuffer", prevBuffer.getTexture(), 1);
		ofSetRectMode(OF_RECTMODE_CORNER);
		ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
		feedbackShader.end();
		mainBuffer.end();

		prevBuffer.begin();
		ofClear(0, 0, 0, 255);
		mainBuffer.draw(0, 0);
		prevBuffer.end();

		mainBuffer.draw(0, 0);
	}
	for (int i = 0; i < textures.size(); i++) {
		textures[i].getTexture().unbind(i + 1);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 13) {
		ofShader test;
		bool success = test.load("vertex.vert", "shaders/custom/custom.frag");
		GLuint programID = test.getProgram();
		GLint linkStatus;
		glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);
		if (linkStatus) {
			customShader = std::move(test);
			customShader.begin();
			texLocs.clear(); 

			for (int i = 0; i < textures.size(); i++) {
				string name = "tex[" + ofToString(i) + "]";
				GLint loc = glGetUniformLocation(customShader.getProgram(), name.c_str());
				texLocs.push_back(loc);
				if (loc != -1) {
					glUniform1i(loc, i + 1);
				}
				else {
					ofLogWarning("Shader") << "Could not find uniform: " << name;
				}
			}
			customShader.end();
		}
	}
	if (key == '0') {
		if (feedback) { feedback = !feedback; }
	}
	else if (key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6') {
		if (!feedback) { feedback = !feedback; }
		feedbackMode = key - 49;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer& buffer)
{
	// used when capturing audio is enabled and then
	// sent as a uniform to a shader
	amplitude = buffer.getRMSAmplitudeChannel(5) * 0.1;
}
