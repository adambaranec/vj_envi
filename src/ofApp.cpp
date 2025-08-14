#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	// code to be used for visualising sound
	// coming from Focusrite
	ofSoundStreamSettings settings;
	settings.numOutputChannels = 0;
	settings.numInputChannels = 6;
	settings.bufferSize = 256;
	//Focusrite USB Asio
	settings.setInDevice(soundStream.getDeviceList()[4]);
	settings.setInListener(this);
	soundStream.setup(settings);
    //---------------------------------------------
	// global OF settings
	ofSetFrameRate(30);
	ofHideCursor();
	/*
	//---------------------------------------------
	// allocating four FBOs to render loops to
	src0.allocate(1920, 1080, GL_RGBA);
	src1.allocate(1920, 1080, GL_RGBA);
	src2.allocate(1920, 1080, GL_RGBA);
	src3.allocate(1920, 1080, GL_RGBA);
	*/
	//---------------------------------------------
	// camera to set for the plane primitive to show
	// the result of rendering of the FBOs
	// the following settings of the camera fit to 1920x1080 resolution
	camera.setGlobalPosition(0, 0, 1);
	camera.setFov(45);
	camera.setNearClip(0.1);
	camera.setFarClip(1000);
	/*
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
	*/
	//---------------------------------------------
	//---------------------------------------------
	ofEnableDepthTest();
	ofSetCircleResolution(100);
	currentVideoPlayer.setLoopState(OF_LOOP_NORMAL);
	currentVideoPlayer.setVolume(0.0f);
	//---------------------------------------------
	//---------------------------------------------
	bitmapFbo.allocate(200,200, GL_RGBA);
	bitmapFbo.begin();
	ofClear(100, 0, 0, 255);
	ofSetDrawBitmapMode(OF_BITMAPMODE_SIMPLE);
	ofSetColor(ofColor::cyan);
	string text = "";
	ofRectangle boundingBox = bitmapFont.getBoundingBox(text, 0, 0);
	ofDrawBitmapString(text, (bitmapFbo.getWidth() / 2) - (boundingBox.getWidth() / 2), (bitmapFbo.getHeight() / 2) - (boundingBox.getHeight() / 4));
	bitmapFbo.end();
}

//--------------------------------------------------------------
void ofApp::update() {
	if (modeIndex == 1) {
		currentVideoPlayer.update();
	}
}
//--------------------------------------------------------------
void ofApp::draw(){
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
			ofDrawRectangle(sin(ofGetElapsedTimef())*0.6, 0, 0.2f + amplitude, 0.2f + amplitude);
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
				ofSetColor(255,255,0);
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
			} else if (index == 18) {
				ofSetColor(ofColor::fromHsb(255*0.54,255,255));
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
				ofTranslate(0.3,0,0);
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
			ofDrawCircle(sin(TWO_PI + ofGetElapsedTimef() * -0.5) * 0.18, cos(TWO_PI + ofGetElapsedTimef()*-0.5) * 0.18, 0, 0.06f + amplitude * 0.5);
			if (index == 21) {
				ofSetColor(ofColor::brown);
			}
			else if (index == 22) {
				ofSetColor(ofColor::green);
			}
			ofDrawCircle(sin(PI/2 + ofGetElapsedTimef() * -0.5) * 0.18, cos(PI/2 + ofGetElapsedTimef() * -0.5) * 0.18, 0, 0.06f + amplitude * 0.5);
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
			ofDrawCircle(sin(PI + PI/2 + ofGetElapsedTimef() * -0.5) * 0.18, cos(PI + PI / 2 + ofGetElapsedTimef() * -0.5)*0.18, 0, 0.06f + amplitude * 0.5);
		}
		camera.end();
	}
	else if (modeIndex == 1) {
		ofSetRectMode(OF_RECTMODE_CORNER);
		ofSetColor(255);
		if (index < loopsSize) {
			currentVideoPlayer.draw(0, 0, ofGetWidth(), ofGetHeight());
		}
	}
	else if (modeIndex == 2) {
			ofSetRectMode(OF_RECTMODE_CORNER);
			if (index < shadersSize) {
				currentShader.begin();
				currentShader.setUniform1f("time", ofGetElapsedTimef());
				currentShader.setUniform1f("aspect", (float)ofGetWidth() / (float)ofGetHeight());
				ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
				currentShader.end();
			}
	}
	else if (modeIndex == 3) {
		ofSetRectMode(OF_RECTMODE_CORNER);
		ofSetColor(255);
		bitmapFbo.draw(0, 0, ofGetWidth(), ofGetHeight());
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	previousIndex = index;
	previousModeIndex = modeIndex;
	switch (key) {
	case '1': modeIndex = 0; break;
	case '2': modeIndex = 1; break;
	case '3': modeIndex = 2; break;
	case '4': modeIndex = 3; break;
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
	if (modeIndex == 1) {
		ofDirectory loopsDir("loops");
		loopsDir.allowExt("mp4");
		loopsDir.listDir();
		loopsSize = loopsDir.size();
		if (index < loopsSize) {
			if (previousModeIndex != modeIndex) {
				currentVideoPlayer.load(loopsDir.getPath(index));
				currentVideoPlayer.play();
			}
			else if (previousModeIndex == modeIndex) {
				if (previousIndex == index) {
					currentVideoPlayer.stop();
					currentVideoPlayer.play();
				}
				else if (previousIndex != index) {
					currentVideoPlayer.load(loopsDir.getPath(index));
					currentVideoPlayer.play();
				}
			}
		}
	}
	else if (modeIndex == 0) {
		currentVideoPlayer.stop();
	} else if (modeIndex == 2) {
		ofDirectory shadersDir("shaders");
		shadersDir.allowExt("frag");
		shadersDir.listDir();
		shadersSize = shadersDir.size();
		if (index < shadersSize) {
			currentShader.load("vertex.vert", shadersDir.getPath(index));
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
	/*
	shaderViewer.setHeight(1);
	shaderViewer.setWidth((float)w / (float)h);
	shaderViewer.setScale(0.83f, 0.83f, 0.83f);
	*/
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
	amplitude = buffer.getRMSAmplitudeChannel(5);
}
