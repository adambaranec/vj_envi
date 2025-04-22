#pragma once

#include "ofMain.h"
//#include "ofxOsc\src\ofxOsc.h"

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
	ofPlanePrimitive shaderViewer;
	std::vector<ofVideoPlayer> videoPlayers;
	std::vector<ofTexture> loopTextures;
	ofTexture currentTex;
	ofVideoPlayer currentVideoPlayer;
	int shaderVar = 0;
	enum Mode { LOOP, TEXTURE, SHADER, CUSTOM } mode;
};
