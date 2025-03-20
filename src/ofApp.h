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
	} circlesParams, circlesParamsFromOsc;

	struct RingsParams {
		int index = 0;
		int visible = 0;
		int mode = 0;
		float amount = 1.0f;
		float density = 15.0f;
		float speed = 5.0f;
		int direction = 1;
		glm::fvec3 hsvColor = glm::fvec3(0.0f, 1.0f, 1.0f);
	} ringsParams, ringsParamsFromOsc;

	struct SquaresParams{
		int index = 0;
		int visible = 0;
		int mode = 0;
		float amount = 1.0f;
		int repeatX = 1;
		int repeatY = 1;
		float scrollX = 0.0f;
		float scrollY = 0.0f;
		int outline = 0;
		int rotate = 0;
		int rotateLeft = 0;
		int rotateRight = 0;
		glm::fvec3 hsvColor = glm::fvec3(0.0f, 1.0f, 1.0f);
	} squaresParams, squaresParamsFromOsc;
	
	struct SolidParams {
		int index = 0;
		int visible = 0;
		int mode = 0;
		float amount = 1.0f;
		glm::fvec3 hsvColor = glm::fvec3(0.0f, 1.0f, 1.0f);
		int showTexture = 0;
		int textureIndex;
	} solidParams, solidParamsFromOsc;

	struct OscillatorParams {
		int index = 0;
		int visible = 0;
		int mode = 0;
		float amount = 1.0f;
		glm::fvec3 hsvColor1 = glm::fvec3(0.0f, 1.0f, 1.0f);
		glm::fvec3 hsvColor2 = glm::fvec3(0.0f, 1.0f, 1.0f);
		int addBall = 0;
		int predefined = 0;
		int predefinedOscIndex;
	} oscParams, oscParamsFromOsc;
};
