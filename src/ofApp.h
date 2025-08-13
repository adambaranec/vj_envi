#pragma once

#include "ofMain.h"

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
	ofPlanePrimitive shaderViewer;
	std::vector<ofVideoPlayer> loopPlayers;
	ofVideoPlayer currentVideoPlayer;
	ofShader currentShader;
	int timestamp, previousIndex, previousModeIndex, index, modeIndex, loopsSize, shadersSize;
	float amplitude = 0.0f;
	//additional textures and 3D shapes used for shaders
	ofBoxPrimitive cube;
	ofSpherePrimitive sphere;
	ofTrueTypeFont font;
	//ofMesh torus;
};
