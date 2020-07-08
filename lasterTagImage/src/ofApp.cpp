#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    laserTagImage.load("images/laser_tag.jpg"); //ofImageで画像読み込み
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(255);
    
    int w = laserTagImage.getWidth(); //画像の横幅を取得
    int h = laserTagImage.getHeight(); //画像の縦幅を取得
    
    float maxBrightness = 0;
    int maxBrightnessx = 0;
    int maxBrightnessy = 0;
    
    for(int y=0; y<h; y++)
    {
        for(int x=0; x<w; x++)
        {
            ofColor colorAtXY = laserTagImage.getColor(x,y);
            float brightnessOfColorAtXY = colorAtXY.getBrightness();
            if(brightnessOfColorAtXY > maxBrightness)
            {
                
                maxBrightness = brightnessOfColorAtXY;
                maxBrightnessx = x;
                maxBrightnessy = y;
            
            }
        }
    }
    
    ofSetColor(255);
    laserTagImage.draw(0,0);
    
    ofNoFill();
    ofDrawEllipse(maxBrightnessx, maxBrightnessy, 40,40);
    
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
