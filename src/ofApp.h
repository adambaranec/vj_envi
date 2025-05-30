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
	ofShader transitionShader;
	ofPlanePrimitive shaderViewer;
	std::vector<ofVideoPlayer> loopPlayers, natureClipPlayers, threeDPlayers;
	std::vector<ofTexture> loopTextures;
	ofVideoPlayer currentVideoPlayer, previousVideoPlayer;
	int timestamp, elapsedFramesFromTransition, index, previousIndex, transitionMode;
	enum Mode {LOOPS, NATURE, THREE_D} mode, previousMode, modeToSet;
	ofFbo previousFrame, currentFrame;
	float progress = 1.0f;
	//additional textures and 3D shapes used for shaders
	ofBoxPrimitive cube;
	ofSpherePrimitive sphere;
	//ofMesh torus;
};
