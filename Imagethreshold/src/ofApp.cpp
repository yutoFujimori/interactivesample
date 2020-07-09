#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofImage flowerOfImage;
    flowerOfImage.load("flowerimage.jpeg");//画像の読み込み
    flowerOfImage.setImageType(OF_IMAGE_GRAYSCALE);//画像のグレースケール化
    
    ofPixels & flowerPixels = flowerOfImage.getPixels();//ピクセル値を取得
    CvImageSrc.setFromPixels (flowerPixels);//imageSrcへピクセルの設定を行う

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(255);
    ofSetColor(255);

    CvImageDst = CvImageSrc;
    
    CvImageDst.threshold (mouseX);//閾値をマウスのx軸に設定
    
    CvImageSrc.draw ( 20,20,  320,240);
    CvImageDst.draw (360,20,  320,240);

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
