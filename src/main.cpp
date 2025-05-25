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
	ofBuffer fragmentShaderFile = ofBufferFromFile("fragment.frag");
	ofBuffer transitionShaderFile = ofBufferFromFile("transition.frag");
	std::string fragmentText = fragmentShaderFile.getText();
	std::string transitionText = transitionShaderFile.getText();
	std::string v = "var";
	std::string m = "mode";
	std::string lastFragmentLineWithVar, lastTransitionLineWithMode;
	std::string maxFragmentIndex, maxTransitionIndex;
	static int lastFragmentLineIndexWithVar, lastTransitionLineIndexWithMode;
	for (auto line : fragmentShaderFile.getLines()) {
		size_t pos = line.find(v);
		if (pos != std::string::npos) {
			lastFragmentLineWithVar = line;
		}
	}
	for (auto line : transitionShaderFile.getLines()) {
		size_t pos = line.find(m);
		if (pos != std::string::npos) {
			lastTransitionLineWithMode = line;
		}
	}
	for (char ch : lastFragmentLineWithVar) {
		if (ch >= 48 && ch <= 57) {
			maxFragmentIndex += ch;
		}
	}
	for (char ch : lastTransitionLineWithMode) {
		if (ch >= 48 && ch <= 57) {
			maxTransitionIndex += ch;
		}
	}

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
	app->maxShaderIndex = std::stoi(maxFragmentIndex);
	app->maxTransitionIndex = std::stoi(maxTransitionIndex);
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
		ofLog() << "Unknown third parameter. To define the mode, type e.g. --mode VIDEO";
	}
	else if (argc == 5) {
		std::string indexArgDef = argv[1];
		std::string indexArg = argv[2];
		std::string modeArgDef = argv[3];
		std::string modeArg = argv[4];
		bool indexArgDefCheck = indexArgDef == "--index" || indexArgDef == "-i";
		bool indexArgCheck = isDigits(indexArg);
		bool modeArgDefCheck = modeArgDef == "--mode" || modeArgDef == "-m";
		bool modeArgCheck = modeArg == "VIDEO" || modeArg == "SHADER" || modeArg == "3D";
		if (indexArgDefCheck && indexArgCheck && modeArgDefCheck && modeArgCheck) {
			int receivedIndex = std::stoi(indexArg);
			if (modeArg == "VIDEO") {
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
			else if (modeArg == "SHADER") {
				app->mode = static_cast<ofApp::Mode>(1);
				app->modeToSet = app->mode;
				if (receivedIndex <= app->maxShaderIndex) {
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
				if (receivedIndex <= 1) {
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
		ofLog() << "An error in definition. Example: -i 5 -m SHADER";
		}
	}

}
