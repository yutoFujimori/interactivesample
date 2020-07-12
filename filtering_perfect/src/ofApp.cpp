#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    //メモリ確保
    videoGrabber.initGrabber(320, 240);
    originalImage.allocate(320, 240);
    grayImage.allocate(320, 240);
    binaryImage.allocate(320, 240);
    gaussianblurImage.allocate(320, 240);
    contrastImage.allocate(320, 240);
    cannyImage.allocate(320, 240);
    invertImage.allocate(320, 240);
    dilateImage.allocate(320,240);
    erodeImage.allocate(320,240);
    

}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofSetColor(255);
    
    videoGrabber.update();
    if(videoGrabber.isFrameNew())
    {
        originalImage.setFromPixels(videoGrabber.getPixels());
        grayImage = originalImage;
    }
    
    //閾値処理
    binaryImage = originalImage;
    binaryImage.threshold(mouseX);
    
    //ガウシアンフィルタ処理
    gaussianblurImage = originalImage;
    int blurValue = 16;
    gaussianblurImage.blurGaussian(blurValue);
    
    //コントラストを強める（明暗）
    contrastImage = originalImage;
    contrastImage.contrastStretch();
    
    //Canny法によるエッジ検出
    cvCanny(grayImage.getCvImage(), cannyImage.getCvImage(), 60, 150);
    cannyImage.flagImageChanged();
    
    //色の反転
    invertImage = originalImage;
    invertImage.invert();
    
    //膨張処理
    dilateImage = originalImage;
    dilateImage.dilate();
    
    //収縮処理
    erodeImage = originalImage;
    erodeImage.erode();
    
    //輪郭検出
    // 第1引数 輪郭検出対象画像
    // 第2引数 検出する最小の大きさ(20)
    // 第3引数 検出する最大の大きさ
    // 第4引数 検出する数
    // 第5引数 穴が空いたものを検出するかどうか trueで　検出する
    contourFinder.findContours(binaryImage,　20, 250000, 5, false);

}

//--------------------------------------------------------------
void ofApp::draw(){

    originalImage.draw(0, 0);
    grayImage.draw(320, 0);
    binaryImage.draw(620, 0);
    gaussianblurImage.draw(940, 0);
    contrastImage.draw(0, 250);
    cannyImage.draw(320, 250);
    invertImage.draw(620, 250);
    
    ofDrawBox(0, 0, ofGetWidth(), ofGetHeight());
    contourFinder.draw(940,250);
    
    dilateImage.draw(0,500);
    erodeImage.draw(320,500);
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
