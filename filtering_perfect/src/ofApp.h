#pragma once

#include "ofMain.h"

#include "ofxOpenCv.h"

class ofApp : public ofBaseApp{

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
    
        ofVideoGrabber videoGrabber;
        ofxCvColorImage originalImage;
        ofxCvGrayscaleImage grayImage;

        ofxCvGrayscaleImage binaryImage;//閾値処理（２値化）
        ofxCvColorImage gaussianblurImage;//ガウシアンフィルタ
        ofxCvGrayscaleImage contrastImage;//コントラストを強める
        ofxCvGrayscaleImage cannyImage;//エッジ検出Canny法
        ofxCvColorImage invertImage;//色の反転
        ofxCvColorImage dilateImage;//膨張処理
        ofxCvColorImage erodeImage;//収縮処理
        ofxCvContourFinder contourFinder;//輪郭検出

		
};
