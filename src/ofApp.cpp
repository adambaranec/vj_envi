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
	// allocating four FBOs to render loops to
	src0.allocate(1920, 1080, GL_RGBA);
	src1.allocate(1920, 1080, GL_RGBA);
	src2.allocate(1920, 1080, GL_RGBA);
	src3.allocate(1920, 1080, GL_RGBA);
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
	//shaderViewer.mapTexCoords(0, 0, 1920, 1080);
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
	ofEnableDepthTest();
	// preparing to start
	sourceIndex = 0;
	src0Player = loopPlayers[index];
	src0Player.play();
}

//--------------------------------------------------------------
void ofApp::update() {
	if (src0Player.isLoaded()) {
		src0Player.update();
	}
	if (src1Player.isLoaded()) {
		src1Player.update();
	}
	if (src2Player.isLoaded()) {
		src2Player.update();
	}
	if (src3Player.isLoaded()) {
		src3Player.update();
	}
}
//--------------------------------------------------------------
void ofApp::draw(){
	//---------------------------------------------
	//first drawing to the FBOs
	if (src0Player.isFrameNew()) {
		src0.begin();
		ofClear(0, 0, 0, 255);
		src0Player.draw(0, 0);
		src0.end();
	}
	if (src1Player.isFrameNew()) {
		src1.begin();
		ofClear(0, 0, 0, 255);
		src1Player.draw(0, 0);
		src1.end();
	}
	if (src2Player.isFrameNew()) {
		src2.begin();
		ofClear(0, 0, 0, 255);
		src2Player.draw(0, 0);
		src2.end();
	}
	if (src3Player.isFrameNew()) {
		src3.begin();
		ofClear(0, 0, 0, 255);
		src3Player.draw(0, 0);
		src3.end();
	}
	//the final rendering to the FBOs
	camera.begin();
	transitionShader.begin();
	transitionShader.setUniform1f("time", ofGetElapsedTimef());
	transitionShader.setUniform1f("aspect", (float)ofGetWidth() / (float)ofGetHeight());
	transitionShader.setUniformTexture("tex0", src0.getTexture(), 1);
	transitionShader.setUniformTexture("tex1", src1.getTexture(), 2);
	transitionShader.setUniformTexture("tex2", src1.getTexture(), 3);
	transitionShader.setUniformTexture("tex3", src1.getTexture(), 4);
	shaderViewer.draw();
	transitionShader.end();
	camera.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	previousIndex = index;
	switch (key) {
	case '1': sourceIndex = 0; break;
	case '2': sourceIndex = 1; break;
	case '3': sourceIndex = 2; break;
	case '4': sourceIndex = 3; break;
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
		bool equalIndex = previousIndex == index;
		if (!equalIndex) {
			if (index < loopPlayers.size()) {
				if (sourceIndex == 0) {
					src0Player.stop();
					src0Player = loopPlayers[index];
					src0Player.play();
				}
				else if (sourceIndex == 1) {
					src1Player.stop();
					src1Player = loopPlayers[index];
					src1Player.play();
				}
				else if (sourceIndex == 2) {
					src2Player.stop();
					src2Player = loopPlayers[index];
					src2Player.play();
				}
				else if (sourceIndex == 3) {
					src3Player.stop();
					src3Player = loopPlayers[index];
					src3Player.play();
				}
			}
		}
		else {
			if (sourceIndex == 0) {
				src0Player.stop();
				src0Player.play();
			}
			else if (sourceIndex == 1) {
				src1Player.stop();
				src1Player.play();
			}
			else if (sourceIndex == 2) {
				src2Player.stop();
				src2Player.play();
			}
			else if (sourceIndex == 3) {
				src3Player.stop();
				src3Player.play();
			}
		}
	}
	if (key == 13) {
		transitionShader.load("vertex.vert", "transition.frag");
	}
	if (key == '0') {
		switch (sourceIndex) {
		case 0: src0Player.stop(); break;
		case 1: src1Player.stop(); break;
		case 2: src2Player.stop(); break;
		case 3: src3Player.stop(); break;
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
