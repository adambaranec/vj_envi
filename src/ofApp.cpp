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
	// shader - for generative visuals
	// transitionShader - the main shader to show the results
	// VERT and FRAG files stored in bin/data
	shader.load("vertex.vert", "fragment.frag");
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
		videoPlayers.push_back(player);
	}
	// stored in bin/data/textures (images only)
	ofDirectory texDir("textures");
	texDir.allowExt("png");
	texDir.listDir();
	for (int i = 0; i < texDir.size(); i++) {
		ofTexture texture;
		ofLoadImage(texture, texDir.getPath(i));
		loopTextures.push_back(texture);
	}
	// external textures for use in generative sources
	// (stored independently in bin/data)
	ofLoadImage(zilip, "zilip.jpg");
	ofLoadImage(les, "les.jpg");
	ofLoadImage(zalesie, "zalesie.jpg");
	ofLoadImage(zakutie, "zakutie.jpg");
	ofLoadImage(korzo, "korzo.jpg");
	// preparing to start
	if (mode == VIDEO) {
		currentVideoPlayer = videoPlayers[index];
		currentVideoPlayer.play();
	}
}

//--------------------------------------------------------------
void ofApp::update() {
	if (previousMode == VIDEO) {
		previousVideoPlayer.update();
	}
	if (mode == VIDEO) {
		currentVideoPlayer.update();
	}
}
//--------------------------------------------------------------
void ofApp::draw(){
	//---------------------------------------------
	//first drawing to the FBOs
	currentFrame.begin();
	if (mode == VIDEO){
		currentVideoPlayer.draw(0, 0);
	}
	else if (mode == SHADER && index <= maxShaderIndex) {
		shader.begin();
		shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
		shader.setUniform1f("time", ofGetElapsedTimef());
		shader.setUniform1i("var", index);
		if (index == 1) {
			shader.setUniformTexture("zilip", zilip, 1);
			shader.setUniformTexture("les", les, 2);
		}
		else if (index == 2) {
			shader.setUniformTexture("zalesie", zalesie, 1);
		}
		else if (index == 3) {
			shader.setUniformTexture("zakutie", zakutie, 1);
		}
		else if (index == 4) {
			shader.setUniformTexture("korzo", korzo, 1);
		}
		ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
		shader.end();
	}
	currentFrame.end();
	if (progress < 1.0f) {
		previousFrame.begin();
		if (previousMode == VIDEO) {
			previousVideoPlayer.draw(0, 0);
		}
		else if (previousMode == SHADER && index <= maxShaderIndex) {
			shader.begin();
			shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
			shader.setUniform1f("time", ofGetElapsedTimef());
			shader.setUniform1i("var", previousIndex);
			if (previousIndex == 1) {
				shader.setUniformTexture("zilip", zilip, 1);
				shader.setUniformTexture("les", les, 2);
			}
			else if (previousIndex == 2) {
				shader.setUniformTexture("zalesie", zalesie, 1);
			}
			else if (previousIndex == 3) {
				shader.setUniformTexture("zakutie", zakutie, 1);
			}
			else if (previousIndex == 4) {
				shader.setUniformTexture("korzo", korzo, 1);
			}
			ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
			shader.end();
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
	case '1': modeToSet = VIDEO; break;
	case '2': modeToSet = SHADER; break;
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
	}
	if (key != '1' && key != '2' && key != '3' && key != '4' && key != '5' && key != '6' && key != '7' && key != '8' && key != '9' && key != '0') {
		transitionMode = static_cast<int>(ofRandom(0, maxTransitionIndex + 1));
		bool equalIndex = previousIndex == index;
		bool equalMode = previousMode == modeToSet;
		bool firstCondition = equalIndex && !equalMode;
		bool secondCondition = !equalIndex && equalMode;
		bool thirdCondition = !equalIndex && !equalMode;
		if (firstCondition || secondCondition || thirdCondition) {
			mode = modeToSet;
			progress = .0f;
			timestamp = ofGetFrameNum();
			if (previousMode == VIDEO) {
				previousVideoPlayer = currentVideoPlayer;
			}
			if (mode == VIDEO && index < videoPlayers.size()) {
				currentVideoPlayer = videoPlayers[index];
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
