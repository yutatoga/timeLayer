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

    // images
    mixFrameNumber = 3;
    waitingTime = 1.0;
    
    vector<int> testVector;
    testVector.push_back(1);
    testVector.push_back(42);
    testVector.push_back(100);
    testVector.erase(testVector.begin());
    testVector.push_back(22);

    ofLogNotice("test:\n"+ofToString(testVector));
    ofEnableAlphaBlending();
}

void WebCameraState::update(){
    videoGrabber.update();
    if (ofGetElapsedTimef()-lastShootingTime > waitingTime) {
        // shooting
        shootPhoto();
        lastShootingTime = ofGetElapsedTimef();
    }
    
}

void WebCameraState::shootPhoto(){
    ofLogNotice("shoot photo!");
    if (images.size() > mixFrameNumber) {
        images.erase(images.begin());
    }
    ofImage newImage;
    newImage.setFromPixels(videoGrabber.getPixelsRef());
    newImage.mirror(false, true);
    images.push_back(newImage);
}

void WebCameraState::drawDebug(){
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
    ofSetColor(255, 255, 255, 255/(float)mixFrameNumber+1);
    for (int i=0; i<images.size(); i++) {
        images[i].draw(0, 0, ofGetWidth(), ofGetHeight());
    }
    ofImage currentImage;
    currentImage.setFromPixels(videoGrabber.getPixelsRef());
    currentImage.mirror(false, true);
    currentImage.draw(0, 0, ofGetWidth(), ofGetHeight());
}


void WebCameraState::mousePressed(int x, int y, int button){
    ofVec2f pressedPoint(x, y);
    centerVector.push_back(pressedPoint);
    pressedFrameNumber = ofGetFrameNum();
}

void WebCameraState::keyPressed(int key){
    
}