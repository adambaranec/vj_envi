#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	oscReceiver.setup("192.168.50.113", 8000);
	ofSoundStreamSettings settings;
	settings.numOutputChannels = 0;
	settings.numInputChannels = 6;
	settings.bufferSize = 256;
	//Focusrite USB Asio
	settings.setInDevice(soundStream.getDeviceList()[4]);
	settings.setInListener(this);
	soundStream.setup(settings);
	//camera is set to 1920x1080 resolution
	camera.setGlobalPosition(0, 0, 1);
	camera.setFov(45);
	camera.setNearClip(0.1);
	camera.setFarClip(1000);
	shader.load("vertex.vert", "fragment.frag");
	shaderViewer.setUseVbo(true);
	shaderViewer.setPosition(glm::vec3(0.0, 0.0, 0.0));
	shaderViewer.setHeight(1);
	shaderViewer.setWidth((1920.0f / 1080.0f));
	ofHideCursor();
}

//--------------------------------------------------------------
void ofApp::update() {
	if (ofGetFrameNum() != 0) {
		if (ofGetFrameNum() % (60 * 60)*2 == 0) {
			if (var == 11) { var = -1; }
			var += 1;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	camera.begin();
	shader.begin();
	shader.setUniform1f("time", ofGetElapsedTimef());
	shader.setUniform1f("amp", amplitude);
	shader.setUniform1f("aspect", (float)ofGetWidth() / ofGetHeight());
	shader.setUniform1i("var", var);
	/*shader.setUniform1i("circlesParams.quantity", circlesParams.quantity);
	shader.setUniform1f("circlesParams.amount", circlesParams.amount);
	shader.setUniform1f("circlesParams.hueRange", circlesParams.hueRange);
	shader.setUniform3f("circlesParams.hsvColor", circlesParams.hsvColor);
	shader.setUniform1i("circlesParams.direction", circlesParams.direction);
	shader.setUniform1i("circlesParams.monochrome", circlesParams.monochrome);
	shader.setUniform1i("circlesParams.coordModification", circlesParams.coordModification);
	shader.setUniform1i("circlesParams.visible", circlesParams.visible);
	shader.setUniform1i("circlesParams.mode", circlesParams.mode);
	shader.setUniform1i("circlesParams.index", circlesParams.index);

	shader.setUniform1f("ringsParams.amount", ringsParams.amount);
	shader.setUniform1i("ringsParams.visible", ringsParams.visible);
	shader.setUniform1i("ringsParams.mode", ringsParams.mode);
	shader.setUniform1i("ringsParams.index", ringsParams.index);
	shader.setUniform3f("ringsParams.hsvColor", ringsParams.hsvColor);*/
	shaderViewer.draw();
	shader.end();
	camera.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
	amplitude = buffer.getRMSAmplitudeChannel(5);
}
