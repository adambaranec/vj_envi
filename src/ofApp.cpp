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
	while (oscReceiver.hasWaitingMessages()) {
		ofxOscMessage m;
		oscReceiver.getNextMessage(m);

		if (m.getAddress() == "/circles/quantity") {
			int value = m.getArgAsInt(0);
			//ofLog() << "Quantity of CirclesParams: " << value;
			circlesParams.quantity = value;
		}
		else if (m.getAddress() == "/circles/amount") {
			float value = m.getArgAsFloat(0);
			//ofLog() << "Amount of CirclesParams: " << value;
			circlesParams.amount = value;
		}
		else if (m.getAddress() == "/circles/hue-range") {
			float value = m.getArgAsFloat(0);
			//ofLog() << "Hue range of CirclesParams: " << value;
			circlesParams.hueRange = value;
		}
		else if (m.getAddress() == "/circles/monochrome-hue") {
			float value = m.getArgAsFloat(0);
			circlesParams.hsvColor.x = value;
		}
		else if (m.getAddress() == "/circles/monochrome-saturation") {
			float value = m.getArgAsFloat(0);
			circlesParams.hsvColor.y = value;
		}
		else if (m.getAddress() == "/circles/monochrome-value") {
			float value = m.getArgAsFloat(0);
			circlesParams.hsvColor.z = value;
		}
		else if (m.getAddress() == "/circles/rotate-left") {
			int value = m.getArgAsInt(0);
			circlesParams.direction = value;
		}
		else if (m.getAddress() == "/circles/monochrome-switch") {
			int value = m.getArgAsInt(0);
			circlesParams.monochrome = value;
		}
		else if (m.getAddress() == "/circles/coords-modification") {
			int value = m.getArgAsInt(0);
			circlesParams.coordModification = value;
		}
		else if (m.getAddress() == "/circles/show-first") {
			if (m.getArgAsInt(0) == 1){
				circlesParams.mode = 0;
				circlesParams.visible = 1;
			}
			else {
				circlesParams.visible = 0;
			}
		}
		else if (m.getAddress() == "/circles/add") {
			if (m.getArgAsInt(0) == 1) {
				circlesParams.mode = 1;
				circlesParams.visible = 1;
			}
			else {
				circlesParams.visible = 0;
			}
		}
		else if (m.getAddress() == "/circles/blend") {
			if (m.getArgAsInt(0) == 1) {
			    circlesParams.mode = 2;
				circlesParams.visible = 1;
			}
			else {
				circlesParams.visible = 0;
			}
		}
		else if (m.getAddress() == "/circles/layer") {
			if (m.getArgAsInt(0) == 1) {
				circlesParams.mode = 3;
				circlesParams.visible = 1;
			}
			else {
				circlesParams.visible = 0;
			}
		}
		else if (m.getAddress() == "/rings/amount") {
			float value = m.getArgAsFloat(0);
			ringsParams.amount = value;
		}
		else if (m.getAddress() == "/rings/hue") {
			float value = m.getArgAsFloat(0);
			ringsParams.hsvColor.x = value;
		}
		else if (m.getAddress() == "/rings/saturation") {
			float value = m.getArgAsFloat(0);
			ringsParams.hsvColor.y = value;
		}
		else if (m.getAddress() == "/rings/value") {
			float value = m.getArgAsFloat(0);
			ringsParams.hsvColor.z = value;
		}
		else if (m.getAddress() == "/rings/show-first") {
			if (m.getArgAsInt(0) == 1) {
				ringsParams.mode = 0;
			    ringsParams.visible = 1;
			}
			else {
				ringsParams.visible = 0;
			}
		}
		else if (m.getAddress() == "/rings/add") {
			if (m.getArgAsInt(0) == 1) {
				ringsParams.mode = 1;
				ringsParams.visible = 1;
			}
			else {
				ringsParams.visible = 0;
			}
		}
		else if (m.getAddress() == "/rings/blend") {
			if (m.getArgAsInt(0) == 1) {
				ringsParams.mode = 2;
				ringsParams.visible = 1;
			}
			else {
				ringsParams.visible = 0;
			}
		}
		else if (m.getAddress() == "/rings/layer") {
			if (m.getArgAsInt(0) == 1) {
				ringsParams.mode = 3;
				ringsParams.visible = 1;
			}
			else {
				ringsParams.visible = 0;
			}
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

	shader.setUniform1i("circlesParams.quantity", circlesParams.quantity);
	shader.setUniform1f("circlesParams.amount", circlesParams.amount);
	shader.setUniform1f("circlesParams.hueRange", circlesParams.hueRange);
	shader.setUniform3f("circlesParams.hsvColor", circlesParams.hsvColor);
	shader.setUniform1i("circlesParams.direction", circlesParams.direction);
	shader.setUniform1i("circlesParams.monochrome", circlesParams.monochrome);
	shader.setUniform1i("circlesParams.coordModification", circlesParams.coordModification);
	shader.setUniform1i("circlesParams.visible", circlesParams.visible);
	shader.setUniform1i("circlesParams.mode", circlesParams.mode);

	shader.setUniform1f("ringsParams.amount", ringsParams.amount);
	shader.setUniform1i("ringsParams.visible", ringsParams.visible);
	shader.setUniform1i("ringsParams.mode", ringsParams.mode);
	shader.setUniform3f("ringsParams.hsvColor", ringsParams.hsvColor);
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
