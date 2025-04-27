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
	shader.load("vertex.vert", "fragment.frag");
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
	status = RUNNING;
	currentVideoPlayer = videoPlayers[0];
	currentVideoPlayer.play();
	fbo.allocate(1920, 1080, GL_RGBA);
	ofSetFrameRate(30);
}

//--------------------------------------------------------------
void ofApp::update() {
	/*if (triggeredTransition = true) {
		elapsedFramesFromTransition = ofGetFrameNum() - timestamp;
		if (elapsedFramesFromTransition < 299) {
			if (status != TRANSITION)
			 status = TRANSITION;
		}
		else if (elapsedFramesFromTransition == 299) {
			if (mode == LOOP) {
				currentVideoPlayer = nextVideoPlayer;
				previousVideoPlayer.stop();
			}
			else if (mode == TEXTURE) {
				currentTex = nextTex;
			}
		}
		else if (elapsedFramesFromTransition > 299) {
			if (status != RUNNING)
				status = RUNNING;
		}
	}*/
	if (status == RUNNING) {
		if (mode == LOOP) {
			currentVideoPlayer.update();
			currentTex = currentVideoPlayer.getTexture();
		}
	}
	/*else if (status == TRANSITION) {
		if (mode == LOOP) {
			if (previousMode == LOOP) {
				previousVideoPlayer.update();
				previousTex = previousVideoPlayer.getTexture();
			}
			else if (previousMode == TEXTURE) {
				previousTex = currentTex;
			}
			nextVideoPlayer.update();
			nextTex = nextVideoPlayer.getTexture();
		}
		else if (mode == TEXTURE) {
			if (previousMode == LOOP) {
				previousVideoPlayer.update();
				previousTex = previousVideoPlayer.getTexture();
			}
			else if (previousMode == TEXTURE) {
				previousTex = currentTex;
			}
			nextTex = currentTex;
		}
	}*/
}
//--------------------------------------------------------------
void ofApp::draw(){
	fbo.begin();
	ofClear(0, 0, 0, 255);
	camera.begin();
	float progress = (float)elapsedFramesFromTransition / 300.0f;
	transitionShader.begin();
	transitionShader.setUniform1i("mode", 0);
	transitionShader.setUniformTexture("currentTex", currentTex, 1);
	//transitionShader.setUniformTexture("prevTex", previousTex, 1);
	//transitionShader.setUniformTexture("newTex", nextTex, 2);
	//if (progress <= 1.0f)
		//transitionShader.setUniform1f("progress", progress);
	if (mode == TEXTURE) 
		shaderViewer.rotateRad(-TWO_PI / 150, glm::vec3(0.0, 0.0, 1.0));
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
	triggeredTransition = true;
	timestamp = ofGetFrameNum();
	int index = 0;
	switch (key) {
	case '1': mode = LOOP; break;
	case '2': mode = TEXTURE; break;
	//case '3': mode = SHADER; break;
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
	if (mode == LOOP) {
		if (previousMode == LOOP) {
			previousVideoPlayer = currentVideoPlayer;
		}
		else if (previousMode == TEXTURE) {
			previousTex = currentTex;
		}
		shaderViewer.resetTransform();
		shaderViewer.setScale(0.83f, 0.83f, 0.83f);
		if (index < videoPlayers.size()) {
			for (int i = 0; i < videoPlayers.size(); i++) {
				if (i == index) {
					videoPlayers[i].play();
				    nextVideoPlayer = videoPlayers[i];
					currentVideoPlayer = videoPlayers[i];
				}
				else {
					videoPlayers[i].stop();
				}
		    }
		}
	}
	else if (mode == TEXTURE) {
		if (previousMode == LOOP) {
			previousVideoPlayer = currentVideoPlayer;
		}
		else if (previousMode == TEXTURE) {
			previousTex = currentTex;
		}
		if (index < loopTextures.size()) {
			currentTex = loopTextures[index];
		}
	}
	/*else if (mode == SHADER) {
		if (index <= 2) {
			shaderViewer.resetTransform();
			shaderViewer.mapTexCoords(0, 0, 1, 1);
			if (currentVideoPlayer.isPlaying()) {
				currentVideoPlayer.stop();
			}
			shaderVar = index;
		}
	}*/
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
