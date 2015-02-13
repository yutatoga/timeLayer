#include "WebCameraState.h"

string WebCameraState::getName(){
		return "WebCameraState";
}

void WebCameraState::setup(){
		//list of devices
		vector<ofVideoDevice> devices = videoGrabber.listDevices();
		for(int i = 0; i < devices.size(); i++){
				cout << devices[i].id << ": " << devices[i].deviceName;
				if( devices[i].bAvailable ){
						cout << endl;
				}else{
						cout << " - unavailable " << endl;
				}
		}
		videoGrabber.setDeviceID(0);
		videoGrabber.setDesiredFrameRate(60);
		cameraWidth = ofGetWidth();
		cameraHeight = ofGetHeight();
		videoGrabber.initGrabber(cameraWidth,cameraHeight);
}

void WebCameraState::update(){
		videoGrabber.update();
}

void drawDebug(){
		ofSetColor(0, 255, 255);
		float gridWidth = ofGetWidth()/10.0;
		float gridHeight = ofGetHeight()/10.0;
		for (int i = 1; i<10; i++) {
				ofLine(0, gridHeight*i, ofGetWidth(), gridHeight*i);
		}
		for (int i = 1; i<10; i++) {
				ofLine(gridWidth*i, 0, gridWidth*i, ofGetHeight());
		}
}

void WebCameraState::draw(){
		ofImage image;
		TS_START("myTimeSample");
		image.setFromPixels(videoGrabber.getPixelsRef());
		TS_STOP("myTimeSample");
		image.mirror(false, true);
		image.draw(0, 0);
		
//		for (int i = 0; i<ofGetHeight(); i++) {
//				for (int j = 0; j<ofGetWidth(); j++) {
//						ofSetColor(ofRandom(255), ofRandom(255), ofRandom(255));
//						ofRect(j, i, 1, 1);
//				}
//		}
//		drawDebug();
		
		// draw center point
		ofSetColor(ofColor::white);
		for (int i = 0; i<centerVector.size(); i++) {
//				ofCircle(centerVector[i], 2);
				ofLine(centerVector[i].x-15, centerVector[i].y, centerVector[i].x+15, centerVector[i].y);
				ofLine(centerVector[i].x, centerVector[i].y-15, centerVector[i].x, centerVector[i].y+15);
		}
}


void WebCameraState::mousePressed(int x, int y, int button){
		ofVec2f pressedPoint(x, y);
		centerVector.push_back(pressedPoint);
		pressedFrameNumber = ofGetFrameNum();
}

void WebCameraState::keyPressed(int key){
		
}