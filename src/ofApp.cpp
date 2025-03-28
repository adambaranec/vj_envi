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
		/*  ----------- CIRCLES --------------*/
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
				circlesParams.visible = 1;
				activeSources += 1;
				circlesParams.index = 1;
				circlesParams.mode = 0;
			}
			else {
				circlesParams.visible = 0;
				activeSources -= 1;
				if (ringsParams.index != 0) { ringsParams.index -= 1; }
				circlesParams.index = 0;
			}
		}
		else if (m.getAddress() == "/circles/add") {
			if (m.getArgAsInt(0) == 1) {
				circlesParams.visible = 1;
				activeSources += 1;
				circlesParams.index = activeSources;
				circlesParams.mode = 1;
			}
			else {
				circlesParams.visible = 0;
				circlesParams.index = 0;
				activeSources -= 1;
			}
		}
		else if (m.getAddress() == "/circles/blend") {
			if (m.getArgAsInt(0) == 1) {
				circlesParams.visible = 1;
				activeSources += 1;
				circlesParams.index = activeSources;
				circlesParams.mode = 2;
			}
			else {
				circlesParams.visible = 0;
				circlesParams.index = 0;
				activeSources -= 1;
			}
		}
		else if (m.getAddress() == "/circles/layer") {
			if (m.getArgAsInt(0) == 1) {
				circlesParams.visible = 1;
				activeSources += 1;
				circlesParams.index = activeSources;
				circlesParams.mode = 3;
			}
			else {
				circlesParams.visible = 0;
				circlesParams.index = 0;
				activeSources -= 1;
			}
		}  /*  ----------- RINGS --------------*/
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
				ringsParams.visible = 1;
				activeSources += 1;
				ringsParams.index = 1;
				ringsParams.mode = 0;
			}
			else {
				ringsParams.visible = 0;
				ringsParams.index = 0;
				if (circlesParams.index != 0) {circlesParams.index -= 1; }
				activeSources -= 1;
			}
		}
		else if (m.getAddress() == "/rings/add") {
			if (m.getArgAsInt(0) == 1) {
				ringsParams.visible = 1;
				activeSources += 1;
				ringsParams.index = activeSources;
				ringsParams.mode = 1;
			}
			else {
				ringsParams.visible = 0;
				ringsParams.index = 0;
				activeSources -= 1;
			}
		}
		else if (m.getAddress() == "/rings/blend") {
			if (m.getArgAsInt(0) == 1) {
				ringsParams.visible = 1;
				activeSources += 1;
				ringsParams.index = activeSources;
				ringsParams.mode = 2;
			}
			else {
				ringsParams.visible = 0;
				ringsParams.index = 0;
				activeSources -= 1;
			}
		}
		else if (m.getAddress() == "/rings/layer") {
			if (m.getArgAsInt(0) == 1) {
				ringsParams.visible = 1;
				activeSources += 1;
				ringsParams.index = activeSources;
				ringsParams.mode = 3;
			}
			else {
				ringsParams.visible = 0;
				ringsParams.index = 0;
				activeSources -= 1;
			}
		}        /*  ----------- SQUARES --------------*/
		else if (m.getAddress() == "/squares/amount") {
		}
		else if (m.getAddress() == "/squares/repeatx") {
		}
		else if (m.getAddress() == "/squares/repeaty") {
		}
		else if (m.getAddress() == "/squares/scrollx") {
		}
		else if (m.getAddress() == "/squares/scrolly") {
		}
		else if (m.getAddress() == "/squares/hue") {
		}
		else if (m.getAddress() == "/squares/saturation") {
		}
		else if (m.getAddress() == "/squares/value") {
		}
		else if (m.getAddress() == "/squares/outline-switch") {
		}
		else if (m.getAddress() == "/squares/rotate-switch") {
		}
		else if (m.getAddress() == "/squares/rotate-left") {
		}
		else if (m.getAddress() == "/squares/rotate-right") {
		}
		else if (m.getAddress() == "/squares/show-first") {
		}
		else if (m.getAddress() == "/squares/add") {
		}
		else if (m.getAddress() == "/squares/blend") {
		}
		else if (m.getAddress() == "/squares/layer") {
		}  /*  ----------- SOLID --------------*/ 
		else if (m.getAddress() == "/solid/amount") {
		}
		else if (m.getAddress() == "/solid/hue") {
		}
		else if (m.getAddress() == "/solid/saturation") {
		}
		else if (m.getAddress() == "/solid/value") {
		}
		else if (m.getAddress() == "/solid/show-texture") {
		}
		else if (m.getAddress() == "/solid/tex1") {
		}
		else if (m.getAddress() == "/solid/tex2") {
		}
		else if (m.getAddress() == "/solid/tex3") {
		}
		else if (m.getAddress() == "/solid/tex4") {
		}
		else if (m.getAddress() == "/solid/tex5") {
		}
		else if (m.getAddress() == "/solid/tex6") {
		}
		else if (m.getAddress() == "/solid/tex7") {
		}
		else if (m.getAddress() == "/solid/tex8") {
		}
		else if (m.getAddress() == "/solid/tex9") {
		}
		else if (m.getAddress() == "/solid/tex10") {
		}
		else if (m.getAddress() == "/solid/tex11") {
		}
		else if (m.getAddress() == "/solid/tex12") {
		}
		else if (m.getAddress() == "/solid/show-first") {
		}
		else if (m.getAddress() == "/solid/add") {
		}
		else if (m.getAddress() == "/solid/blend") {
		}
		else if (m.getAddress() == "/solid/layer") {
		}/*  ----------- OSCILLATOR --------------*/ 
		else if (m.getAddress() == "/osc/amount") {
		}
		else if (m.getAddress() == "/osc/hue1") {
		}
		else if (m.getAddress() == "/osc/hue2") {
		}
		else if (m.getAddress() == "/osc/saturation1") {
		}
		else if (m.getAddress() == "/osc/saturation2") {
		}
		else if (m.getAddress() == "/osc/value1") {
		}
		else if (m.getAddress() == "/osc/value2") {
		}
		else if (m.getAddress() == "/osc/predefined") {
		}
		else if (m.getAddress() == "/osc/add-ball") {
		}
		else if (m.getAddress() == "/osc/show-first") {
		}
		else if (m.getAddress() == "/osc/add") {
		}
		else if (m.getAddress() == "/osc/blend") {
		}
		else if (m.getAddress() == "/osc/layer") {
		}
		/*  ----------- SOURCE INDICES AND MIXING --------------*/
		else if (m.getAddress() == "/circles/index2") {
		}
		else if (m.getAddress() == "/circles/index3") {
		}
		else if (m.getAddress() == "/circles/index4") {
		}
		else if (m.getAddress() == "/rings/index2") {
		}
		else if (m.getAddress() == "/rings/index3") {
		}
		else if (m.getAddress() == "/rings/index4") {
		}
		else if (m.getAddress() == "/squares/index2") {
		}
		else if (m.getAddress() == "/squares/index3") {
		}
		else if (m.getAddress() == "/squares/index4") {
		}
		else if (m.getAddress() == "/solid/index2") {
		}
		else if (m.getAddress() == "/solid/index3") {
		}
		else if (m.getAddress() == "/solid/index4") {
		}
		else if (m.getAddress() == "/osc/index2") {
		}
		else if (m.getAddress() == "/osc/index3") {
		}
		else if (m.getAddress() == "/osc/index4") {
		}
		else if (m.getAddress() == "/rings/index2") {
		}
		else if (m.getAddress() == "/rings/index3") {
		}
		else if (m.getAddress() == "/confirm") {
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
