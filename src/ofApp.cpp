#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::mainDraw(int modeIndex, int index) {
	ofClear(0, 0, 0, 255);
	if (modeIndex == 0) {
		ofSetRectMode(OF_RECTMODE_CENTER);
		camera.begin();
		if (index == 0 || index == 1 || index == 2 || index == 3 || index == 4 || index == 5 || index == 6) {
			if (index == 0 || index == 2 || index == 4) {
				ofSetColor(255, 0, 0);
			}
			else if (index == 1 || index == 3 || index == 5) {
				ofSetColor(255);
			}
			if (index != 6) {
				ofDrawCircle(0, 0, 0, 0.15f + amplitude);
			}
			if (index == 0 || index == 1 || index == 4 || index == 5) {
				ofSetColor(0);
				ofDrawCircle(0, 0, 0.01, 0.1f + amplitude);
			}
			if (index == 4 || index == 5 || index == 6) {
				for (int i = 0; i < 8; i++) {
					ofPushMatrix();
					if (index == 6) {
						ofTranslate(sin((TWO_PI / 8 * i) - ofGetElapsedTimef()) * 0.32f, cos((TWO_PI / 8 * i) - ofGetElapsedTimef()) * 0.32f);
					}
					else if (index == 4 || index == 5) {
						ofTranslate(sin(TWO_PI / 8 * i) * 0.32f, cos(TWO_PI / 8 * i) * 0.32f);
					}
					ofRotate(ofGetElapsedTimef() * -100);
					if (index == 6) {
						ofSetColor(255, 255, 0);
					}
					else if (index == 4 || index == 5) {
						ofSetColor(255, 0, 255);
					}
					ofDrawRectangle(0, 0, 0.1f, 0.1f);
					ofSetColor(0);
					if (index == 4) {
						ofTranslate(0, 0, 0.001f);
						ofDrawRectangle(0, 0, 0.06f, 0.06f);
					}
					ofPopMatrix();
				}
			}
		}
		else if (index == 7 || index == 8) {
			ofSetColor(255, 0, 255);
			ofDrawRectangle(0, 0, 0.3f + amplitude, 0.3f + amplitude);
			if (index == 8) {
				ofSetColor(255, 0, 255);
				ofDrawRectangle(0.48f, 0.25f, 0.15f + amplitude, 0.15f + amplitude);
				ofSetColor(0);
				ofDrawRectangle(0.48f, 0.25f, 0.001f, 0.08f + amplitude, 0.08f + amplitude);

				ofSetColor(255, 0, 255);
				ofDrawRectangle(0.48f, -0.25f, 0.15f + amplitude, 0.15f + amplitude);
				ofSetColor(0);
				ofDrawRectangle(0.48f, -0.25f, 0.001f, 0.08f + amplitude, 0.08f + amplitude);

				ofSetColor(255, 0, 255);
				ofDrawRectangle(-0.48f, -0.25f, 0.15f + amplitude, 0.15f + amplitude);
				ofSetColor(0);
				ofDrawRectangle(-0.48f, -0.25f, 0.001f, 0.08f + amplitude, 0.08f + amplitude);

				ofSetColor(255, 0, 255);
				ofDrawRectangle(-0.48f, 0.25f, 0.15f + amplitude, 0.15f + amplitude);
				ofSetColor(0);
				ofDrawRectangle(-0.48f, 0.25f, 0.001f, 0.08f + amplitude, 0.08f + amplitude);
			}
			ofSetColor(0);
			ofDrawRectangle(0, 0, 0.001, 0.2f + amplitude, 0.2f + amplitude);
		}
		else if (index == 9) {
			ofSetColor(ofColor::fromHsb(255 * 0.62, 255 * 0.8, 255));
			for (int i = 0; i < 14; i++) {
				ofPushMatrix();
				ofTranslate(sin((TWO_PI / 14 * i) + ofGetElapsedTimef()) * 0.6, 0.0f, cos((TWO_PI / 14 * i) + ofGetElapsedTimef()) * 0.35);
				ofRotateY(ofGetElapsedTimef() * 30);
				ofDrawCircle(0, 0, 0.06f + amplitude * 0.4);
				ofPopMatrix();
			}
		}
		else if (index == 10) {
			ofSetColor(ofColor::fromHsb(255 * 0.62, 255 * 0.92, 255));
			ofPushMatrix();
			ofTranslate(sin(ofGetElapsedTimef() * 1.2) * 0.6, 0, 0);
			ofDrawCircle(0, 0, 0.1f + amplitude * 0.6);
			ofPopMatrix();
			ofPushMatrix();
			ofTranslate(sin(-ofGetElapsedTimef() * 1.2) * 0.6, 0, 0);
			ofDrawCircle(0, 0, 0.1f + amplitude * 0.6);
			ofPopMatrix();
		}
		else if (index == 11) {
			ofBackground(255 * amplitude * 5);
		}
		else if (index == 12) {
			ofSetColor(255, 0, 0);
			ofDrawCircle(0, 0, 0, 0.15f + amplitude);
			ofSetColor(0);
			ofDrawCircle(0, 0, 0.01, 0.1f + amplitude);
			ofSetColor(255);
			ofDrawCircle(0.48f, 0.25f, 0.1f + amplitude);
			ofDrawCircle(0.48f, -0.25f, 0.1f + amplitude);
			ofDrawCircle(-0.48f, -0.25f, 0.1f + amplitude);
			ofDrawCircle(-0.48f, 0.25f, 0.1f + amplitude);
			ofSetColor(0);
			ofDrawCircle(0.48f, 0.25f, 0.001f, 0.07f + amplitude);
			ofDrawCircle(0.48f, -0.25f, 0.001f, 0.07f + amplitude);
			ofDrawCircle(-0.48f, -0.25f, 0.001f, 0.07f + amplitude);
			ofDrawCircle(-0.48f, 0.25f, 0.001f, 0.07f + amplitude);
		}
		else if (index == 13) {
			ofSetColor(255);
			ofDrawRectangle(sin(ofGetElapsedTimef()) * 0.6, 0, 0.2f + amplitude, 0.2f + amplitude);
			ofSetColor(0);
			ofDrawRectangle(sin(ofGetElapsedTimef()) * 0.6, 0, 0.001f, 0.1f + amplitude, 0.1f + amplitude);
			ofSetColor(255);
			ofDrawRectangle(0, sin(ofGetElapsedTimef()) * 0.26, 0.2f + amplitude, 0.2f + amplitude);
			ofSetColor(0);
			ofDrawRectangle(0, sin(ofGetElapsedTimef()) * 0.26, 0.001f, 0.1f + amplitude, 0.1f + amplitude);
		}
		else if (index == 14 || index == 15) {
			if (index == 14) {
				ofSetColor(ofColor::purple);
			}
			ofPushMatrix();
			ofTranslate(0, 0.2, 0);
			if (index == 15) {
				ofSetColor(255);
			}
			ofDrawTriangle(0, 0.035f + amplitude, -0.035f - amplitude, -0.035f - amplitude, 0.035f + amplitude, -0.035f - amplitude);
			ofPopMatrix();
			ofPushMatrix();
			ofTranslate(0.4, 0.2, 0);
			if (index == 15) {
				ofSetColor(255, 255, 0);
			}
			ofDrawTriangle(0, 0.035f + amplitude, -0.035f - amplitude, -0.035f - amplitude, 0.035f + amplitude, -0.035f - amplitude);
			ofPopMatrix();
			ofPushMatrix();
			ofTranslate(-0.4, 0.2, 0);
			if (index == 15) {
				ofSetColor(255, 255, 0);
			}
			ofDrawTriangle(0, 0.035f + amplitude, -0.035f - amplitude, -0.035f - amplitude, 0.035f + amplitude, -0.035f - amplitude);
			ofPopMatrix();
			ofPushMatrix();
			ofTranslate(-0.4, -0.2, 0);
			if (index == 15) {
				ofSetColor(255);
			}
			ofDrawTriangle(0, 0.035f + amplitude, -0.035f - amplitude, -0.035f - amplitude, 0.035f + amplitude, -0.035f - amplitude);
			ofPopMatrix();
			ofPushMatrix();
			ofTranslate(0, -0.2, 0);
			if (index == 15) {
				ofSetColor(255, 255, 0);
			}
			ofDrawTriangle(0, 0.035f + amplitude, -0.035f - amplitude, -0.035f - amplitude, 0.035f + amplitude, -0.035f - amplitude);
			ofPopMatrix();
			ofPushMatrix();
			ofTranslate(0.4, -0.2, 0);
			if (index == 15) {
				ofSetColor(255);
			}
			ofDrawTriangle(0, 0.035f + amplitude, -0.035f - amplitude, -0.035f - amplitude, 0.035f + amplitude, -0.035f - amplitude);
			ofPopMatrix();
		}
		else if (index == 16 || index == 17 || index == 18) {
			ofPushMatrix();
			if (index == 16 || index == 17) {
				ofSetColor(255);
			}
			else if (index == 18) {
				ofSetColor(ofColor::fromHsb(255 * 0.54, 255, 255));
			}
			ofRotate(ofGetElapsedTimef() * -40);
			ofDrawRectangle(0, 0, 1.7f, 0.005f + amplitude);
			ofPopMatrix();

			if (index == 17 || index == 18) {
				ofPushMatrix();
				if (index == 17) {
					ofSetColor(255);
				}
				if (index == 18) {
					ofSetColor(0, 255, 0);
				}
				ofTranslate(0.2, 0.2, 0);
				ofRotate(ofGetElapsedTimef() * -40);
				ofDrawRectangle(0, 0, 1.7f, 0.005f + amplitude);
				ofPopMatrix();

				ofPushMatrix();
				if (index == 17) {
					ofSetColor(255);
				}
				if (index == 18) {
					ofSetColor(255, 0, 0);
				}
				ofTranslate(-0.2, -0.2, 0);
				ofRotate(ofGetElapsedTimef() * -40);
				ofDrawRectangle(0, 0, 1.7f, 0.005f + amplitude);
				ofPopMatrix();
			}
		}
		else if (index == 19 || index == 20) {
			ofPushMatrix();
			ofTranslate(0, 0.2, 0);
			ofSetColor(0, 0, 255);
			ofDrawRectangle(0, 0, 1.7f, 0.005f + amplitude);
			ofPopMatrix();
			ofPushMatrix();
			ofTranslate(0, -0.2, 0);
			ofSetColor(255, 255, 0);
			ofDrawRectangle(0, 0, 1.7f, 0.005f + amplitude);
			ofPopMatrix();
			if (index == 20) {
				ofSetColor(ofColor::orange);
				ofDrawTriangle(0, 0.01f + amplitude, -0.01f - amplitude, -0.01f - amplitude, 0.01f + amplitude, -0.01f - amplitude);
				ofPushMatrix();
				ofTranslate(0.3, 0, 0);
				ofDrawTriangle(0, 0.01f + amplitude, -0.01f - amplitude, -0.01f - amplitude, 0.01f + amplitude, -0.01f - amplitude);
				ofPopMatrix();
				ofPushMatrix();
				ofTranslate(-0.3, 0, 0);
				ofDrawTriangle(0, 0.01f + amplitude, -0.01f - amplitude, -0.01f - amplitude, 0.01f + amplitude, -0.01f - amplitude);
				ofPopMatrix();
				ofPushMatrix();
				ofTranslate(0, 0.3, 0);
				ofDrawTriangle(0, 0.01f + amplitude, -0.01f - amplitude, -0.01f - amplitude, 0.01f + amplitude, -0.01f - amplitude);
				ofPopMatrix();
				ofPushMatrix();
				ofTranslate(0.3, 0.3, 0);
				ofDrawTriangle(0, 0.01f + amplitude, -0.01f - amplitude, -0.01f - amplitude, 0.01f + amplitude, -0.01f - amplitude);
				ofPopMatrix();
				ofPushMatrix();
				ofTranslate(-0.3, 0.3, 0);
				ofDrawTriangle(0, 0.01f + amplitude, -0.01f - amplitude, -0.01f - amplitude, 0.01f + amplitude, -0.01f - amplitude);
				ofPopMatrix();
				ofPushMatrix();
				ofTranslate(0, -0.3, 0);
				ofDrawTriangle(0, 0.01f + amplitude, -0.01f - amplitude, -0.01f - amplitude, 0.01f + amplitude, -0.01f - amplitude);
				ofPopMatrix();
				ofPushMatrix();
				ofTranslate(0.3, -0.3, 0);
				ofDrawTriangle(0, 0.01f + amplitude, -0.01f - amplitude, -0.01f - amplitude, 0.01f + amplitude, -0.01f - amplitude);
				ofPopMatrix();
				ofPushMatrix();
				ofTranslate(-0.3, -0.3, 0);
				ofDrawTriangle(0, 0.01f + amplitude, -0.01f - amplitude, -0.01f - amplitude, 0.01f + amplitude, -0.01f - amplitude);
				ofPopMatrix();
			}
		}
		else if (index == 21 || index == 22) {
			if (index == 21) {
				ofSetColor(ofColor::darkBlue);
			}
			else if (index == 22) {
				ofSetColor(ofColor::yellow);
			}
			ofDrawCircle(sin(TWO_PI + ofGetElapsedTimef() * -0.5) * 0.18, cos(TWO_PI + ofGetElapsedTimef() * -0.5) * 0.18, 0, 0.06f + amplitude * 0.5);
			if (index == 21) {
				ofSetColor(ofColor::brown);
			}
			else if (index == 22) {
				ofSetColor(ofColor::green);
			}
			ofDrawCircle(sin(PI / 2 + ofGetElapsedTimef() * -0.5) * 0.18, cos(PI / 2 + ofGetElapsedTimef() * -0.5) * 0.18, 0, 0.06f + amplitude * 0.5);
			if (index == 21) {
				ofSetColor(ofColor::purple);
			}
			else if (index == 22) {
				ofSetColor(ofColor::red);
			}
			ofDrawCircle(sin(PI + ofGetElapsedTimef() * -0.5) * 0.18, cos(PI + ofGetElapsedTimef() * -0.5) * 0.18, 0, 0.06f + amplitude * 0.5);
			if (index == 21) {
				ofSetColor(ofColor::darkCyan);
			}
			else if (index == 22) {
				ofSetColor(ofColor::magenta);
			}
			ofDrawCircle(sin(PI + PI / 2 + ofGetElapsedTimef() * -0.5) * 0.18, cos(PI + PI / 2 + ofGetElapsedTimef() * -0.5) * 0.18, 0, 0.06f + amplitude * 0.5);
		}
		camera.end();
	}
	else if (modeIndex == 1) {
		ofSetRectMode(OF_RECTMODE_CORNER);
		if (index < loopsSize) {
			ofSetColor(255);
			players[index].draw(0, 0, ofGetWidth(), ofGetHeight());
		}
	}
	else if (modeIndex == 2) {
		ofSetRectMode(OF_RECTMODE_CORNER);
		if (index < shadersSize) {
			shaders[index].begin();
			shaders[index].setUniform1f("time", ofGetElapsedTimef());
			shaders[index].setUniform1f("aspect", (float)ofGetWidth() / (float)ofGetHeight());
			ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
			shaders[index].end();
		}
	}
	else if (modeIndex == 3) {
		ofSetRectMode(OF_RECTMODE_CORNER);
		customShader.begin();
		customShader.setUniform1f("time", ofGetElapsedTimef());
		customShader.setUniform1f("amp", amplitude);
		customShader.setUniform1f("aspect", (float)ofGetWidth() / (float)ofGetHeight());
		customShader.setUniform2i("resolution", ofGetWidth(), ofGetHeight());
		ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
		customShader.end();
	}
}

//--------------------------------------------------------------
void ofApp::setup() {
	loopsDir.open("loops");
	loopsDir.allowExt("mp4");
	loopsDir.listDir();
	loopsSize = loopsDir.size();
	for (int i = 0; i < loopsSize; i++) {
		ofVideoPlayer player;
		player.load(loopsDir.getPath(i));
		player.setVolume(0.0f);
		player.setLoopState(OF_LOOP_NORMAL);
		players.push_back(player);
	}
	texturesDir.open("textures");
	texturesDir.allowExt("png");
	texturesDir.allowExt("jpg");
	texturesDir.listDir();
	texturesSize = texturesDir.size();
	for (int i = 0; i < texturesSize; i++) {
		ofImage image;
		image.load(texturesDir.getPath(i));
		textures.push_back(image);
	}
	//---------------------------------------------
	customShader.load("vertex.vert", "shaders/custom/custom.frag");
	feedbackShader.load("vertex.vert", "shaders/feedback/feedback.frag");
	customShader.begin();
	for (int i = 0; i < textures.size(); i++) {
		string name = "tex[" + ofToString(i) + "]";

		// Find the location once
		GLint loc = glGetUniformLocation(customShader.getProgram(), name.c_str());

		// Store it for later
		texLocs.push_back(loc);

		// Optional: Pre-link the index to the unit ID here as well
		if (loc != -1) {
			glUniform1i(loc, i + 1);
		}
	}
	customShader.end();
	//---------------------------------------------
	mainBuffer.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	prevBuffer.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	nextBuffer.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	/*
	shadersDir.open("shaders/elements");
	shadersDir.allowExt("frag");
	shadersDir.listDir();
	shadersSize = shadersDir.size();
	for (int i = 0; i < shadersSize; i++) {
		ofShader shader;
		shader.load("vertex.vert", shadersDir.getPath(i));
		shaders.push_back(shader);
	}
	texturesDir.open("textures");
	texturesDir.allowExt("png");
	texturesDir.allowExt("jpg");
	texturesDir.listDir();
	texturesSize = texturesDir.size();
	for (int i = 0; i < texturesSize; i++) {
		ofImage image;
		image.load(texturesDir.getPath(i));
		textures.push_back(image);
	}
	//---------------------------------------------
	feedbackShader.load("vertex.vert", "shaders/feedback/feedback.frag");
	transitionShader.load("vertex.vert", "shaders/transitions/transition.frag");
	repetitionShader.load("vertex.vert", "shaders/post/repeat.frag");
	customShader.load("vertex.vert", "shaders/custom/custom.frag");
	//---------------------------------------------
	mainBuffer.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	prevBuffer.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	nextBuffer.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	scene1.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	scene2.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	postBuffer.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	//---------------------------------------------
	camera.setGlobalPosition(0, 0, 1);
	camera.setFov(45);
	camera.setNearClip(0.1);
	camera.setFarClip(1000);
	//---------------------------------------------
	ofSetFrameRate(60);
	ofHideCursor();
	ofEnableDepthTest();
	//---------------------------------------------
	*/
	ofSoundStreamSettings settings;
	settings.numOutputChannels = 0;
	settings.numInputChannels = 6;
	settings.bufferSize = 256;
	settings.setInDevice(soundStream.getMatchingDevices("Focusrite USB ASIO")[0]);
	settings.setInListener(this);
	soundStream.setup(settings);
}

//--------------------------------------------------------------
void ofApp::update() {
}
//--------------------------------------------------------------
void ofApp::draw(){
	for (int i = 0; i < textures.size(); i++) {
		int unit = i + 1;
		textures[i].getTexture().bind(unit);
		if (texLocs[i] != -1) {
			glUniform1i(texLocs[i], unit);
		}
	}
	ofSetRectMode(OF_RECTMODE_CORNER);
	ofClear(0, 0, 0, 255);
	if (!feedback) {
		customShader.begin();
		customShader.setUniform1f("time", ofGetElapsedTimef());
		customShader.setUniform1f("amp", amplitude);
		customShader.setUniform1f("aspect", (float)ofGetWidth() / (float)ofGetHeight());
		customShader.setUniform2f("resolution", (float)ofGetWidth(), (float)ofGetHeight());
		ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
		customShader.end();
	}
	else {
		nextBuffer.begin();
		ofClear(0, 0, 0, 255);
		customShader.begin();
		customShader.setUniform1f("time", ofGetElapsedTimef());
		customShader.setUniform1f("amp", amplitude);
		customShader.setUniform1f("aspect", (float)ofGetWidth() / (float)ofGetHeight());
		customShader.setUniform2f("resolution", (float)ofGetWidth(), (float)ofGetHeight());
		ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
		customShader.end();
		nextBuffer.end();

		mainBuffer.begin();
		ofClear(0, 0, 0, 255);
		feedbackShader.begin();
		feedbackShader.setUniform1i("mode", feedbackMode);
		feedbackShader.setUniformTexture("nextBuffer", nextBuffer.getTexture(), 0);
		feedbackShader.setUniformTexture("prevBuffer", prevBuffer.getTexture(), 1);
		ofSetRectMode(OF_RECTMODE_CORNER);
		ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
		feedbackShader.end();
		mainBuffer.end();

		prevBuffer.begin();
		ofClear(0, 0, 0, 255);
		mainBuffer.draw(0, 0);
		prevBuffer.end();

		mainBuffer.draw(0, 0);
	}
	for (int i = 0; i < textures.size(); i++) {
		textures[i].getTexture().unbind(i + 1);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 13) {
		ofShader test;
		bool success = test.load("vertex.vert", "shaders/custom/custom.frag");
		GLuint programID = test.getProgram();
		GLint linkStatus;
		glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);
		if (linkStatus) {
			customShader = std::move(test);
			customShader.begin();
			texLocs.clear(); 

			for (int i = 0; i < textures.size(); i++) {
				string name = "tex[" + ofToString(i) + "]";
				GLint loc = glGetUniformLocation(customShader.getProgram(), name.c_str());
				texLocs.push_back(loc);
				if (loc != -1) {
					glUniform1i(loc, i + 1);
				}
				else {
					ofLogWarning("Shader") << "Could not find uniform: " << name;
				}
			}
			customShader.end();
		}
	}
	if (key == '0') {
		if (feedback) { feedback = !feedback; }
	}
	else if (key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6') {
		if (!feedback) { feedback = !feedback; }
		feedbackMode = key - 49;
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
	amplitude = buffer.getRMSAmplitudeChannel(5) * 0.1;
}
