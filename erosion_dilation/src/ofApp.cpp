#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    Image.load("image.png");
    Image.setImageType(OF_IMAGE_GRAYSCALE);
    
    
    dilatedImage.allocate(Image.getWidth(),Image.getHeight());
    erodedImage.allocate(Image.getWidth(),Image.getHeight());
    
    dilatedImage = Image;
    erodedImage = Image;
    
    dilatedImage.dilate();//膨張処理
    erodedImage.erode();//収縮処理
    
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    dilatedImage.draw(0,0);
    erodedImage.draw(300,0);

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
