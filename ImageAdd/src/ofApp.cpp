#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ImageSrc.load("images/star1.png");//画像の読み込み
    ImageSrc.setImageType(OF_IMAGE_GRAYSCALE);//グレースケールへ変換
    
    int imgW = ImageSrc.getWidth();
    int imgH = ImageSrc.getHeight();
    ImageDst.allocate(imgW,imgH,OF_IMAGE_GRAYSCALE); //幅と高さの画像割り当てる
    
    unsigned char* srcArray = ImageSrc.getPixels().getData();
    unsigned char* dstArray = ImageDst.getPixels().getData();
    
    int nPixels = imgW*imgH;
    for(int i=0; i<nPixels; i++)
    {
        unsigned char srcValue = srcArray[i];
        dstArray[i] = min(255,(int)srcValue + 100);//オーバーフローを起こすため制約を設ける
    }
    
    ImageDst.update();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(255);
    ofSetColor(255);

    ImageSrc.draw ( 20,20, 120,160);
    ImageDst.draw (160,20, 120,160);

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
