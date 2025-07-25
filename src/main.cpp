#include "ofMain.h"
#include "ofApp.h"

bool isDigits(std::string& str)
{
	for (char ch : str) {
		int v = ch; // ASCII Val converted
		if (!(ch >= 48 && ch <= 57)) {
			return false;
			break;
		}
	}

	return true;
}

//========================================================================
int main(int argc, char* argv[]) {

	//Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
	ofGLWindowSettings settings;
	settings.setSize(1920, 1080);
	settings.setGLVersion(4,6);
	settings.windowMode = OF_WINDOW; //can also be OF_FULLSCREEN

	ofDirectory loopsDir("loops");
	loopsDir.allowExt("mp4");
	loopsDir.listDir();

	auto window = ofCreateWindow(settings);
	auto app = make_shared<ofApp>();
	if (argc == 2) {
		std::string indexArg = argv[1];
		int receivedIndex = std::stoi(indexArg);
		bool indexArgCheck = isDigits(indexArg);
		if (indexArgCheck) {
			if (receivedIndex < loopsDir.size()) {
				app->index = receivedIndex;
				ofRunApp(window, app);
				ofRunMainLoop();
			}
			else {
				ofLog() << "No element at this index";
			}
		} else {
			ofLog() << "Error, only numbers";
		}
	} else if (argc == 1) {
		ofRunApp(window, app);
		ofRunMainLoop();
	}
}

/*
int numSlices = 40;  // Number of divisions around the torus
int numSegments = 20; // Number of divisions along the tube
float R = 200;       // Major radius
float r = 50;        // Minor radius

for (int i = 0; i < numSlices; i++) {
	float theta = ofMap(i, 0, numSlices, 0, TWO_PI);
	for (int j = 0; j < numSegments; j++) {
		float phi = ofMap(j, 0, numSegments, 0, TWO_PI);

		// Parametric equations for torus
		float x = (R + r * cos(phi)) * cos(theta);
		float y = (R + r * cos(phi)) * sin(theta);
		float z = r * sin(phi);

		torus.addVertex(ofVec3f(x, y, z));
		torus.addNormal(ofVec3f(x, y, z).normalized());
	}
}*/