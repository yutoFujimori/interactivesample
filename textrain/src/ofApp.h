#pragma once

#include "ofMain.h"

#include "ofxBox2d.h"

#include "ofxOpenCv.h"

#include "ofxCv.h"

#include "ofxGui.h"


class ofApp : public ofBaseApp{
    
    private:
    ofxBox2d world2d;
    vector <ofPtr<ofxBox2dCircle> > circles;
    ofImage alphabet;
    void makeAlphabet(float x, float y, float size);
    
    
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofVideoGrabber cam;
        //ofxCvColorImage originalImage;
        //ofxCvGrayscaleImage binaryImage;//閾値処理（２値化）
        //ofxCvContourFinder contourFinder;//輪郭検出
    
        //輪郭線の変更
        //int numContour;
        //ofPolyline findLines[MAX_BLOBS];
        //ofPtr<ofxBox2dPolygon> contour[MAX_BLOBS];
    
    
        //マウスで輪郭
        //vector <shared_ptr<ofxBox2dEdge> > edges;//edges
    
        //vector <ofPolyline> lines;
    
    
        ofxCv::ContourFinder contourFinder2;
        vector <ofxBox2dEdge*> edges;
        ofxPanel gui;
        ofParameter<float> minArea, maxArea, threshold;
        ofParameter<bool> holes;

    
    
};
