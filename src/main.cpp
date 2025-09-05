#include "ofMain.h"
#include "ofApp.h"

static bool isDigits(std::string& str)
{
	for (char ch : str) {
		int v = ch;
		if (!(ch >= 48 && ch <= 57)) {
			return false;
			break;
		}
	}

	return true;
}

//========================================================================
int main(int argc, char* argv[]) {

	ofGLWindowSettings settings;
	settings.setSize(1920, 1080);
	settings.setGLVersion(4,6);
	settings.windowMode = OF_WINDOW;
	auto window = ofCreateWindow(settings);
	auto app = make_shared<ofApp>();

    if (argc == 1) {
		ofRunApp(window, app);
		ofRunMainLoop();
	}
	else if (argc == 2) {
		std::string indexArg = argv[1];
		int receivedIndex = std::stoi(indexArg);
		bool indexArgCheck = isDigits(indexArg);
		if (indexArgCheck) {
			if (receivedIndex < 23) {
				app->index = receivedIndex;
				ofRunApp(window, app);
				ofRunMainLoop();
			}
			else {
				ofLog() << "No element at this index";
			}
		}
		else {
			ofLog() << "Error, only numbers";
		}
	}
	else if (argc == 3) {
		ofDirectory loopsDir("loops");
		loopsDir.allowExt("mp4");
		loopsDir.listDir();

		ofDirectory shadersDir("shaders/elements");
		shadersDir.allowExt("frag");
		shadersDir.listDir();

		std::string modeArg = argv[1];
		std::string indexArg = argv[2];
		bool indexArgCheck = isDigits(indexArg);
		bool modeArgCheck = isDigits(modeArg);
		if (indexArgCheck && modeArgCheck) {
			int receivedIndex = std::stoi(indexArg);
			int receivedModeIndex = std::stoi(modeArg);
			int maxSize;
			if (receivedModeIndex < 3) {
				switch (receivedModeIndex) {
				case 0: maxSize = 22; break;
				case 1: maxSize = loopsDir.size() - 1; break;
				case 2: maxSize = shadersDir.size() - 1; break;
				default: break;
				}
				app->modeIndex = receivedModeIndex;
				app->index = receivedIndex;
				ofRunApp(window, app);
				ofRunMainLoop();
			}
			else {
				ofLog() << "2 is the maximum of mode indices";
			}
		}
		else {
			ofLog() << "Error, only numbers";
		}
	}
}