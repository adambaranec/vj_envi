#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

class ofApp : public ofBaseApp {

public:
	void mainDraw(int modeIndex, int index);
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
	ofShader feedbackShader, crossFadeShader, transitionShader, repetitionShader, customShader;
	ofFbo mainBuffer, prevBuffer, nextBuffer, scene1, scene2, postBuffer;
	ofDirectory loopsDir, shadersDir, texturesDir;
	ofxOscReceiver receiver;
	std::vector<ofVideoPlayer> players;
	std::vector<ofShader> shaders;
	std::vector<ofImage> textures;
	int timestamp, previousIndex, previousModeIndex, index, modeIndex, modeIndexToSet, transitionMode, feedbackMode, loopsSize, shadersSize, texturesSize;
	float amplitude, progress = 1.0f;
	//attributes edited either by OSC or MIDI
	int rows, columns;
	bool feedback = false;
	bool transition = false;
	bool repeat = false;
};
