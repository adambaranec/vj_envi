#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
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
	ofLoadImage(tex, "vj-loop-5-hd-texture.jpg");
	camera.setGlobalPosition(0, 0, 1);
	camera.setFov(45);
	camera.setNearClip(0.1);
	camera.setFarClip(1000);
	shader.load("vertex.vert", "texViewer.frag");
	shaderViewer.setUseVbo(true);
	shaderViewer.setPosition(glm::vec3(0.0, 0.0, 0.0));
	shaderViewer.setHeight(1);
	shaderViewer.setWidth((float)ofGetWidth() / (float)ofGetHeight());
	ofHideCursor();
}

//--------------------------------------------------------------
void ofApp::update() {
}
//--------------------------------------------------------------
void ofApp::draw(){
	camera.begin();
	shader.begin();
	//shader.setUniformTexture("tex", tex, 0);
	//shader.setUniform1f("time", ofGetElapsedTimef());
	//shader.setUniform1f("aspect", (float)ofGetWidth() / (float)ofGetHeight());
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
	//amplitude = buffer.getRMSAmplitudeChannel(5);
}
