#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);//垂直同期（フレーム数と実際の描画回数を同期させるもの）
    
    ofSetBackgroundColor(50, 50, 50);
	
    //サイズの初期値設定
	densityWidth = 1280;
	densityHeight = 720;
	simulationWidth = densityWidth / 2;
	simulationHeight = densityHeight / 2;

	opticalFlow.setup(simulationWidth, simulationHeight);
    
    combinedBridgeFlow.setup(simulationWidth, simulationHeight, densityWidth, densityHeight);
    fluidFlow.setup(simulationWidth, simulationHeight, densityWidth, densityHeight);
	
	simpleCam.setup(densityWidth, densityHeight, true);
	cameraFbo.allocate(densityWidth, densityHeight);
	ftUtil::zero(cameraFbo);

	
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofSetFrameRate(60);
    float dt = 1.0 / max(ofGetFrameRate(), 1.f); // more smooth as 'real' deltaTime.
    
    simpleCam.update();
    if (simpleCam.isFrameNew()) {
        cameraFbo.begin();
        simpleCam.draw(cameraFbo.getWidth(), 0, -cameraFbo.getWidth(), cameraFbo.getHeight());  // draw flipped
        cameraFbo.end();
        
        opticalFlow.setInput(cameraFbo.getTexture());
    }
    
    opticalFlow.update();
    
    combinedBridgeFlow.setVelocity(opticalFlow.getVelocity());
    combinedBridgeFlow.setDensity(cameraFbo.getTexture());
    combinedBridgeFlow.update(dt);
    
    fluidFlow.addVelocity(combinedBridgeFlow.getVelocity());
    fluidFlow.addDensity(combinedBridgeFlow.getDensity());
    fluidFlow.addTemperature(combinedBridgeFlow.getTemperature());
    fluidFlow.update(dt);

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(50, 50, 50, 50);
    ofDrawRectangle(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    
   // cameraFbo.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    ofSetColor(255, 255, 255);
    opticalFlow.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    
    combinedBridgeFlow.drawVelocity(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    
    combinedBridgeFlow.drawDensity(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    
    fluidFlow.drawObstacle(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    
    fluidFlow.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    
}

//--------------------------------------------------------------
