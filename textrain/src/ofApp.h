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
    
    ofImage alphabet_a;
    
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
        ofxCv::ContourFinder contourFinder2;
    
        vector <ofxBox2dEdge*> edges;
        ofxPanel gui;
        ofParameter<float> minArea, maxArea, threshold;
        ofParameter<bool> holes;
    
        // 初期設定
        void setInit(ofVec2f initPos);
        // 力をリセット
        void resetForce();
        // 力を加える
        void addForce(ofVec2f force);
        // 力を更新
        void updateForce();
        // 位置の更新
        void updatePos();
        // 画面からはみ出たらバウンドさせる
        void bounceOffWalls();
        
        // 描画するパーティクルの数を指定
        static const int CIRCLE_NUM = 10000;
        
        // 位置ベクトルの配列
        ofVec2f position[CIRCLE_NUM];
        
        // 速度ベクトルの配列
        ofVec2f velocity[CIRCLE_NUM];
        
        // 力ベクトルの配列
        ofVec2f force[CIRCLE_NUM];
        
        // 摩擦係数
        float friction;
    

    
    
};
