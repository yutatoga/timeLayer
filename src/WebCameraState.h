#include "ofxStateMachine.h"
#include "ofxTimeMeasurements.h"
class WebCameraState : public itg::ofxState<>{
public:
		string getName();
		void setup();
		void update();
		void draw();
		void mousePressed(int x, int y, int button);
		void keyPressed(int key);
		
		//camera
		ofVideoGrabber videoGrabber;
		int cameraWidth;
		int cameraHeight;
		vector<ofVec2f> centerVector;
		float pressedFrameNumber;
};