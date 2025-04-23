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
	mode = LOOP;
	currentVideoPlayer = videoPlayers[0];
	currentVideoPlayer.play();
}

//--------------------------------------------------------------
void ofApp::update() {
	if (mode == LOOP) {
		currentVideoPlayer.update();
		currentTex = currentVideoPlayer.getTexture();
	}
}
//--------------------------------------------------------------
void ofApp::draw(){
	ofClear(0, 0, 0, 255);
	camera.begin();
	if (mode != SHADER) {
		currentTex.bind();
	}
	else {
		shader.begin();
		shader.setUniform1f("time", ofGetElapsedTimef());
		shader.setUniform1f("aspect", (float)ofGetWidth() / ofGetHeight());
		shader.setUniform1i("var", shaderVar);
	}
	if (mode == TEXTURE) {
	shaderViewer.rotateRad(-TWO_PI/300, glm::vec3(0.0, 0.0, 1.0));
	}
	shaderViewer.draw();
	if (mode != SHADER) {
		currentTex.unbind();
	}
	else {
		shader.end();
	}
	camera.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	int index = 0;
	switch (key) {
	case '1': mode = LOOP; break;
	case '2': mode = TEXTURE; break;
	case '3': mode = SHADER; break;
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
		shaderViewer.resetTransform();
		shaderViewer.mapTexCoords(0, 0, 1920, 1080);
		if (index < videoPlayers.size()) {
			for (int i = 0; i < videoPlayers.size(); i++) {
				if (i != index) {
					videoPlayers[i].stop();
				}
				else {
					videoPlayers[i].play();
					currentVideoPlayer = videoPlayers[i];
				}
			}
		}
	}
	else if (mode == TEXTURE) {
		shaderViewer.mapTexCoords(0, 0, 1920, 1080);
		if (currentVideoPlayer.isPlaying()) {
			currentVideoPlayer.stop();
		}
		if (index < loopTextures.size()) {
			currentTex = loopTextures[index];
		}
	}
	else if (mode == SHADER) {
		if (index <= 2) {
			shaderViewer.resetTransform();
			shaderViewer.mapTexCoords(0, 0, 1, 1);
			if (currentVideoPlayer.isPlaying()) {
				currentVideoPlayer.stop();
			}
			shaderVar = index;
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
