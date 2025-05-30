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

	ofDirectory natureClipDir("nature");
	natureClipDir.allowExt("mp4");
	natureClipDir.listDir();

	ofDirectory threeDDir("3D");
	threeDDir.allowExt("mp4");
	threeDDir.listDir();

	auto window = ofCreateWindow(settings);
	auto app = make_shared<ofApp>();
	if (argc == 2) {
		std::string indexArg = argv[1];
		int receivedIndex = std::stoi(indexArg);
		bool indexArgCheck = isDigits(indexArg);
		if (indexArgCheck) {
			if (receivedIndex < loopsDir.size()) {
				app->index = receivedIndex;
				app->mode = static_cast<ofApp::Mode>(0);
				app->modeToSet = app->mode;
				ofRunApp(window, app);
				ofRunMainLoop();
			}
			else {
				ofLog() << "No element at this index";
			}
		} else {
			ofLog() << "Error, only numbers";
		}
	}
	else if (argc == 3) {
		std::string indexArgDef = argv[1];
		std::string indexArg = argv[2];
		bool indexArgDefCheck = indexArgDef == "--index" || indexArgDef == "-i";
		bool indexArgCheck = isDigits(indexArg);
		int receivedIndex = std::stoi(indexArg);
		if (indexArgDefCheck && indexArgCheck) {
			if (receivedIndex < loopsDir.size()) {
				app->index = receivedIndex;
				app->mode = static_cast<ofApp::Mode>(0);
				app->modeToSet = app->mode;
				ofRunApp(window, app);
				ofRunMainLoop();
			}
			else {
				ofLog() << "No element at this index";
			}
		}
		else if (!indexArgDefCheck && indexArgCheck) {
			ofLog() << "Not correct definition for index. Use -i or --index";
		}
		else if (indexArgDefCheck && !indexArgCheck) {
			ofLog() << "Incorrect format of index, only numbers";
		}
		else if (!indexArgDefCheck && !indexArgCheck) {
			ofLog() << "Unknown parameters. Use e.g. -i 10 or --index 3";
		}
	}
	else if (argc == 4) {
		ofLog() << "Unknown third parameter. To define the mode, type e.g. --mode LOOPS";
	}
	else if (argc == 5) {
		std::string indexArgDef = argv[1];
		std::string indexArg = argv[2];
		std::string modeArgDef = argv[3];
		std::string modeArg = argv[4];
		bool indexArgDefCheck = indexArgDef == "--index" || indexArgDef == "-i";
		bool indexArgCheck = isDigits(indexArg);
		bool modeArgDefCheck = modeArgDef == "--mode" || modeArgDef == "-m";
		bool modeArgCheck = modeArg == "LOOPS" || modeArg == "NATURE" || modeArg == "3D";
		if (indexArgDefCheck && indexArgCheck && modeArgDefCheck && modeArgCheck) {
			int receivedIndex = std::stoi(indexArg);
			if (modeArg == "LOOPS") {
				app->mode = static_cast<ofApp::Mode>(0);
				app->modeToSet = app->mode;
				if (receivedIndex < loopsDir.size()) {
					app->index = receivedIndex;
					ofRunApp(window, app);
					ofRunMainLoop();
				}
				else {
					ofLog() << "No video at this index";
				}
			}
			else if (modeArg == "NATURE") {
				app->mode = static_cast<ofApp::Mode>(1);
				app->modeToSet = app->mode;
				if (receivedIndex < natureClipDir.size()) {
					app->index = receivedIndex;
					ofRunApp(window, app);
					ofRunMainLoop();
				}
				else {
					ofLog() << "No shader variation at this index";
				}
			}
			else if (modeArg == "3D") {
				app->mode = static_cast<ofApp::Mode>(2);
				if (receivedIndex < threeDDir.size()) {
					app->index = receivedIndex;
					app->modeToSet = app->mode;
					ofRunApp(window, app);
					ofRunMainLoop();
				}
				else {
					ofLog() << "No shader variation for 3D objects at this index";
				}
			}
		}
		else {
		ofLog() << "An error in definition. Example: -i 6 -m LOOPS";
		}
	}

}
