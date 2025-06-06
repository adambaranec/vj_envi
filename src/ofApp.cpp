#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	// code to be used for visualising sound
	// coming from Focusrite
	/*ofSoundStreamSettings settings;
	settings.numOutputChannels = 0;
	settings.numInputChannels = 6;
	settings.bufferSize = 256;
	//Focusrite USB Asio
	settings.setInDevice(soundStream.getDeviceList()[4]);
	settings.setInListener(this);
	soundStream.setup(settings);*/
    //---------------------------------------------
	// global OF settings
	ofSetFrameRate(30);
	ofHideCursor();
	//---------------------------------------------
	// allocating the two FBOs to render to -
	// previousFrame is used when the transition is happening
	// and currentFrame is used as the following texture to render
	// when the transition is done or as the default texture.
	previousFrame.allocate(1920, 1080, GL_RGBA);
	currentFrame.allocate(1920, 1080, GL_RGBA);
	//---------------------------------------------
	// camera to set for the plane primitive to show
	// the result of rendering of the FBOs
	// the following settings of the camera fit to 1920x1080 resolution
	camera.setGlobalPosition(0, 0, 1);
	camera.setFov(45);
	camera.setNearClip(0.1);
	camera.setFarClip(1000);
	//---------------------------------------------
	// to view the visuals correctly, the plane primitive 
	// as the container must have the needed position, width and height
	shaderViewer.setUseVbo(true);
	shaderViewer.setPosition(glm::vec3(0.0, 0.0, 0.0));
	shaderViewer.setHeight(1);
	shaderViewer.setWidth(1920.0f/1080.0f);
	shaderViewer.mapTexCoords(0, 0, 1920, 1080);
	// for some reason, with its default scale the visuals are
	// not shown as whole
	shaderViewer.setScale(0.83f, 0.83f, 0.83f);
	//---------------------------------------------
	// transitionShader - the main shader to show the results
	transitionShader.load("vertex.vert", "transition.frag");
	//---------------------------------------------
	// loading external sources
	// stored in bin/data/loops
	ofDirectory loopsDir("loops");
	loopsDir.allowExt("mp4");
	loopsDir.listDir();
	for (int i = 0; i < loopsDir.size(); i++) {
		ofVideoPlayer player;
		player.load(loopsDir.getPath(i));
		player.setLoopState(OF_LOOP_NORMAL);
		player.setVolume(0.0f);
		loopPlayers.push_back(player);
	}
	// stored in bin/data/nature
	ofDirectory natureClipsDir("nature");
	natureClipsDir.allowExt("mp4");
	natureClipsDir.listDir();
	for (int i = 0; i < natureClipsDir.size(); i++) {
		ofVideoPlayer player;
		player.load(natureClipsDir.getPath(i));
		player.setLoopState(OF_LOOP_NORMAL);
		player.setVolume(0.0f);
		natureClipPlayers.push_back(player);
	}
	// stored in bin/data/3D
	ofDirectory threeDDir("3D");
	threeDDir.allowExt("mp4");
	threeDDir.listDir();
	for (int i = 0; i < threeDDir.size(); i++) {
		ofVideoPlayer player;
		player.load(threeDDir.getPath(i));
		player.setLoopState(OF_LOOP_NORMAL);
		player.setVolume(0.0f);
		threeDPlayers.push_back(player);
	}
	/*
	int numSlices = 40;  // Number of divisions around the torus
	int numSegments = 20; // Number of divisions along the tube
	float R = 200;       // Major radius
	float r = 50;        // Minor radius

	for (int i = 0; i < numSlices; i++) {
		float theta = ofMap(i, 0, numSlices, 0, TWO_PI);
		for (int j = 0; j < numSegments; j++) {
			float phi = ofMap(j, 0, numSegments, 0, TWO_PI);

			// Parametric equations for torus
			float x = (R + r * cos(phi)) * cos(theta);
			float y = (R + r * cos(phi)) * sin(theta);
			float z = r * sin(phi);

			torus.addVertex(ofVec3f(x, y, z));
			torus.addNormal(ofVec3f(x, y, z).normalized());
		}
	}*/
	ofEnableDepthTest();
	// preparing to start
	if (mode == LOOPS) {
		currentVideoPlayer = loopPlayers[index];
		currentVideoPlayer.play();
	}
	else if (mode == NATURE) {
		currentVideoPlayer = natureClipPlayers[index];
		currentVideoPlayer.play();
	}
	else if (mode == THREE_D) {
		currentVideoPlayer = threeDPlayers[index];
		currentVideoPlayer.play();
	}
}

//--------------------------------------------------------------
void ofApp::update() {
	if (previousMode == LOOPS || previousMode == NATURE || previousMode == THREE_D) {
		previousVideoPlayer.update();
	}
	if (mode == LOOPS || mode == NATURE || mode == THREE_D) {
		currentVideoPlayer.update();
	}
}
//--------------------------------------------------------------
void ofApp::draw(){
	//---------------------------------------------
	//first drawing to the FBOs
	currentFrame.begin();
	ofClear(0, 0, 0, 255);
	if (mode == LOOPS || mode == NATURE || mode == THREE_D){
		currentVideoPlayer.draw(0, 0);
	}
	currentFrame.end();
	if (progress < 1.0f) {
		previousFrame.begin();
		ofClear(0, 0, 0, 255);
		if (previousMode == LOOPS || previousMode == NATURE || previousMode == THREE_D) {
			previousVideoPlayer.draw(0, 0);
		}
		previousFrame.end();
	}
	//---------------------------------------------
	//rendering final textures with transition
	camera.begin();
	transitionShader.begin();
	transitionShader.setUniform1f("time", ofGetElapsedTimef());
	transitionShader.setUniform1f("aspect", (float)ofGetWidth() / (float)ofGetHeight());
	transitionShader.setUniform1f("progress", progress);
	if (progress < 1.0f) {
		progress = (float)(ofGetFrameNum() - timestamp) / 450.0f;
		transitionShader.setUniform1i("mode", transitionMode);
		transitionShader.setUniformTexture("prevTex", previousFrame.getTexture(), 2);
	}
	else {
		if (previousVideoPlayer.isPlaying()) { previousVideoPlayer.stop(); }
	}
	transitionShader.setUniformTexture("currentTex", currentFrame.getTexture(), 1);
	shaderViewer.draw();
	transitionShader.end();
	camera.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	previousMode = mode;
	previousIndex = index;
	switch (key) {
	case '1': modeToSet = LOOPS; break;
	case '2': modeToSet = NATURE; break;
	case '3': modeToSet = THREE_D; break;
	}
	switch (key) {
	case 'q': index = 0; break;
	case 'w': index = 1; break;
	case 'e': index = 2; break;
	case 'r': index = 3; break;
	case 't': index = 4; break;
	case 'y': index = 5; break;
	case 'u': index = 6; break;
	case 'i': index = 7; break;
	case 'o': index = 8; break;
	case 'p': index = 9; break;
	case '[': index = 10; break;
	case ']': index = 11; break;
	case 'a': index = 12; break;
	case 's': index = 13; break;
	case 'd': index = 14; break;
	case 'f': index = 15; break;
	case 'g': index = 16; break;
	case 'h': index = 17; break;
	case 'j': index = 18; break;
	case 'k': index = 19; break;
	case 'l': index = 20; break;
	case ';': index = 21; break;
	case '\'': index = 22; break;
	case 'z': index = 23; break;
	case 'x': index = 24; break;
	case 'c': index = 25; break;
	case 'v': index = 26; break;
	case 'b': index = 27; break;
	case 'n': index = 28; break;
	case 'm': index = 29; break;
	case ',': index = 30; break;
	case '.': index = 31; break;
	case '/': index = 32; break;
	}
	if (key != '1' && key != '2' && key != '3' && key != '4' && key != '5' && key != '6' && key != '7' && key != '8' && key != '9' && key != '0') {
		transitionMode = static_cast<int>(ofRandom(0, 5));
		bool equalIndex = previousIndex == index;
		bool equalMode = previousMode == modeToSet;
		bool firstCondition = equalIndex && !equalMode;
		bool secondCondition = !equalIndex && equalMode;
		bool thirdCondition = !equalIndex && !equalMode;
		if (firstCondition || secondCondition || thirdCondition) {
			mode = modeToSet;
			progress = .0f;
			timestamp = ofGetFrameNum();
			if (previousMode == LOOPS || previousMode == NATURE || previousMode == THREE_D) {
				previousVideoPlayer = currentVideoPlayer;
			}
			if (mode == LOOPS && index < loopPlayers.size()) {
				currentVideoPlayer = loopPlayers[index];
				currentVideoPlayer.play();
			}
			else if (mode == NATURE && index < natureClipPlayers.size()) {
				currentVideoPlayer = natureClipPlayers[index];
				currentVideoPlayer.play();
			} 
			else if (mode == THREE_D && index < threeDPlayers.size()) {
				currentVideoPlayer = threeDPlayers[index];
				currentVideoPlayer.play();
			}
		}
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
	shaderViewer.setHeight(1);
	shaderViewer.setWidth((float)w / (float)h);
	shaderViewer.setScale(0.83f, 0.83f, 0.83f);
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
	//amplitude = buffer.getRMSAmplitudeChannel(5);
}
