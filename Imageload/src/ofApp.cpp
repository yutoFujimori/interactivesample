#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    myImage.load("lincoln.png");//openframeworks sorcefile name>apps>myApp>Imageload>lincoln.png
    //myImage.load("https:// ・・・");　//インターネットから画像を読み込む場合
    myImage.setImageType(OF_IMAGE_GRAYSCALE);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    ofSetColor(255);
    
    int imageWidth = myImage.getWidth();
    int imageHeight = myImage.getHeight();//
    
    //線形変換の拡大
    // "lincoln.png"を１０倍する。線形補間のため画像がぼやける
    //線形補間：画像拡大・縮小した分、画素数は増える・減る。そのため画素に隙間ができる。
    //隙間を周辺の輝度値を参考にし、追加する画素と周辺画素の距離から重み付けをして足し合わせ、補間する。
    //画像処理の場合、二次元の線形補間（バイリニア）を行なっている。
    //draw(表示位置x,表示位置y,画像サイズ幅*10,画像サイズ高さ*10)

    myImage.draw(10,10, imageWidth*10,imageHeight*10);

    
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
