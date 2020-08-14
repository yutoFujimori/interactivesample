#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxFlowTools.h"

using namespace flowTools;

class ofApp : public ofBaseApp{
public:
	void	setup();
	void	update();
	void	draw();
	
    int		densityWidth, densityHeight, simulationWidth, simulationHeight;
	
    //オプティカルフロー（物体の動きをベクトルで表したもの）の設定
	vector< ftFlow* >		flows;
	ftOpticalFlow			opticalFlow;
	ftCombinedBridgeFlow 	combinedBridgeFlow;
	ftFluidFlow				fluidFlow;

	//ライブカメラ周りの設定
	ofVideoGrabber		simpleCam;
	ofFbo				cameraFbo;
};
