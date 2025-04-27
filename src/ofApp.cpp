#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	//oscReceiver.setup("192.168.50.113", 8000);
	/*ofSoundStreamSettings settings;
	settings.numOutputChannels = 0;
	settings.numInputChannels = 6;
	settings.bufferSize = 256;
	//Focusrite USB Asio
	settings.setInDevice(soundStream.getDeviceList()[4]);
	settings.setInListener(this);
	soundStream.setup(settings);*/
	//camera is set to 1920x1080 resolution
	camera.setGlobalPosition(0, 0, 1);
	camera.setFov(45);
	camera.setNearClip(0.1);
	camera.setFarClip(1000);
	//shader.load("vertex.vert", "fragment.frag");
	transitionShader.load("vertex.vert", "transition.frag");
	shaderViewer.setUseVbo(true);
	shaderViewer.setPosition(glm::vec3(0.0, 0.0, 0.0));
	shaderViewer.setHeight(1);
	shaderViewer.setWidth(1920.0f/1080.0f);
	ofDirectory loopsDir("loops");
	loopsDir.allowExt("mp4");
	loopsDir.listDir();
	for (int i = 0; i < loopsDir.size(); i++) {
		ofVideoPlayer player;
		player.load(loopsDir.getPath(i));
		player.setLoopState(OF_LOOP_NORMAL);
		videoPlayers.push_back(player);
	}
	ofDirectory texDir("textures");
	texDir.allowExt("png");
	texDir.listDir();
	for (int i = 0; i < texDir.size(); i++) {
		ofTexture texture;
		ofLoadImage(texture, texDir.getPath(i));
		loopTextures.push_back(texture);
	}
	ofHideCursor();
	shaderViewer.mapTexCoords(0, 0, 1920, 1080);
	shaderViewer.setScale(0.83f, 0.83f, 0.83f);
	mode = LOOP;
	currentVideoPlayer = videoPlayers[0];
	currentVideoPlayer.play();
	fbo.allocate(1920, 1080, GL_RGBA);
	ofSetFrameRate(30);
}

//--------------------------------------------------------------
void ofApp::update() {
	if (!triggeredTransition) {
		if (mode == LOOP) {
			currentVideoPlayer.update();
			currentTex = currentVideoPlayer.getTexture();
		}
	}
	else {
		if (mode == LOOP) {
			if (previousMode == LOOP) {
				previousVideoPlayer.update();
				previousTex = previousVideoPlayer.getTexture();
				nextVideoPlayer.update();
				nextTex = nextVideoPlayer.getTexture();
			}
			else if (previousMode == TEXTURE) {
				nextVideoPlayer.update();
				nextTex = nextVideoPlayer.getTexture();
			}
		}
		else if (mode == TEXTURE) {
			if (previousMode == LOOP) {
				previousVideoPlayer.update();
				previousTex = previousVideoPlayer.getTexture();
			}
			/*else if (previousMode == TEXTURE) {
				previousTex = nextTex;
			}*/
		}
	}
}
//--------------------------------------------------------------
void ofApp::draw(){
	fbo.begin();
	ofClear(0, 0, 0, 255);
	camera.begin();
	transitionShader.begin();
	if (!triggeredTransition) {
		transitionShader.setUniform1i("mode", 0);
		transitionShader.setUniformTexture("currentTex", currentTex, 1);
	}
	else {
		if (previousTex.isAllocated() && nextTex.isAllocated()) {
			float progress = (float)(ofGetFrameNum() - timestamp) / 300.0f;
			transitionShader.setUniform1i("mode", 1);
			transitionShader.setUniformTexture("prevTex", previousTex, 1);
			transitionShader.setUniformTexture("newTex", nextTex, 2);
			if (progress <= 1.0f) {
				transitionShader.setUniform1f("progress", progress);
			}
			else {
				if (previousVideoPlayer.isPlaying()) { previousVideoPlayer.stop(); }
				if (mode == TEXTURE) {
					shaderViewer.rotateRad(-TWO_PI / 150, glm::vec3(0.0, 0.0, 1.0));
				}
			}
		}
	}
	shaderViewer.draw();
	transitionShader.end();
	camera.end();
	fbo.end();
	fbo.draw(0, 0);
	//RECORDING
	//SHADER  VARIATION 1
	/*int rotDuration = 30 * 4.5;
	int oneDirDur = rotDuration * 4;
	float endVal1 = (float)TWO_PI;
	static float val1 = 0.0f;
	static int frameNum = 1;
	camera.begin();
	shader.begin();
	//shader.setUniform1f("time", ofGetElapsedTimef());
	shader.setUniform1f("aspect", (float)ofGetWidth() / ofGetHeight());
	shader.setUniform1f("val1", val1);
	shader.setUniform1i("var", 0);
	shaderViewer.draw();
	ofImage renderResult;
	renderResult.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
	std::string filename = "shader-0/shader-0-" + ofToString(frameNum, 4, '0') + ".png";
	shader.end();
	camera.end();
	frameNum++;
	if (frameNum < oneDirDur) {
		val1 += endVal1 / (float)rotDuration;
	}
	else {
		val1 -= endVal1 / (float)rotDuration;
	}
	if (frameNum <= oneDirDur * 2) {
		renderResult.save(filename);
	}*/
	//SHADER VARIATION 2
	/*int moveDur = 30 * 4;
	int rotDur = 30 * 3;
	static float val1 = 0.0f;
	static float val2 = 0.0f;
	static int frameNum = 1;
	camera.begin();
	shader.begin();
	//shader.setUniform1f("time", ofGetElapsedTimef());
	shader.setUniform1f("aspect", (float)ofGetWidth() / ofGetHeight());
	shader.setUniform1f("val1", val1);
	shader.setUniform1f("val2", val2);
	shader.setUniform1i("var", 1);
	shaderViewer.draw();
	ofImage renderResult;
	renderResult.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
	std::string filename = "shader-1/shader-1-" + ofToString(frameNum, 4, '0') + ".png";
	shader.end();
	camera.end();
	val1 += (float)PI / 60.0f;
	val2 -= (float)TWO_PI / float(rotDur);
	frameNum++;
	if (frameNum <= 30 * 12) {
		renderResult.save(filename);
	}*/
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	previousMode = mode;
	int index = 0;
	switch (key) {
	case '1': modeToSet = LOOP; break;
	case '2': modeToSet = TEXTURE; break;
	//case '3': modeToSet = SHADER; break;
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
	}
	if (key != '1' && key != '2' && key != '3' && key != '4' && key != '5' && key != '6' && key != '7' && key != '8' && key != '9' && key != '0') {
		timestamp = ofGetFrameNum();
		mode = modeToSet;
		if (mode == LOOP) {
			if (previousMode == LOOP) {
				if (!triggeredTransition) {
					previousVideoPlayer = currentVideoPlayer;
				}
				else {
					previousVideoPlayer = nextVideoPlayer;
					previousVideoPlayer.play();
				}
			}
			else if (previousMode == TEXTURE) {
				if (!triggeredTransition) {
					previousTex = currentTex;
				}
				else {
					previousTex = nextTex;
				}
			}
			shaderViewer.resetTransform();
			shaderViewer.setScale(0.83f, 0.83f, 0.83f);
			if (index < videoPlayers.size()) {
				nextVideoPlayer = videoPlayers[index];
				nextVideoPlayer.play();
			}
		}
		else if (mode == TEXTURE) {
			if (previousMode == LOOP) {
				if (!triggeredTransition) {
					previousVideoPlayer = currentVideoPlayer;
				}
				else {
					previousVideoPlayer = nextVideoPlayer;
				}
				if (index < loopTextures.size()) {
					nextTex = loopTextures[index];
				}
			}
			else if (previousMode == TEXTURE) {
				shaderViewer.resetTransform();
				shaderViewer.setScale(0.83f, 0.83f, 0.83f);
				if (!triggeredTransition) {
					previousTex = currentTex;
				}
				else {
					previousTex = nextTex;
					if (index < loopTextures.size()) {
						nextTex = loopTextures[index];
					}
				}
			}
		}
		if (!triggeredTransition) { triggeredTransition = true; }
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
	//amplitude = buffer.getRMSAmplitudeChannel(5);
}
