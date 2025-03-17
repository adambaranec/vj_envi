#pragma once

#include "ofMain.h"
#include "ofxOsc\src\ofxOsc.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	void audioIn(ofSoundBuffer& buffer);

	ofSoundStream soundStream;
	ofCamera camera;
	ofShader shader;
	ofPlanePrimitive shaderViewer, imgViewer;
	ofFbo shaderTex;
	ofTexture tex0, tex1, tex2, tex3, sphereTex0, sphereTex1;
	ofColor back;
	ofSpherePrimitive sphere;
	ofxOscReceiver oscReceiver;
	float amplitude;
	int activeSources;
	struct CirclesParams {
		int index = 0;
		int visible = 0;
		int mode = 0;
		float amount = 1.0f;
		int direction = 0;
		int monochrome = 0;
		int coordModification = 0;
		int quantity = 10;
		float hueRange = 0.1f;
		glm::fvec3 hsvColor = glm::fvec3(0.0f, 1.0f, 1.0f);
	} circlesParams;

	struct RingsParams {
		int index = 0;
		int visible = 0;
		int mode = 0;
		float amount = 1.0f;
		float density = 15.0f;
		float speed = 5.0f;
		int direction = 1;
		glm::fvec3 hsvColor = glm::fvec3(0.0f, 1.0f, 1.0f);;
	} ringsParams;
};
