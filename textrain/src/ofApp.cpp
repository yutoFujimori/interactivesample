#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
    //  ウィンドウの設定
    ofBackground(255, 255, 255);
    ofSetWindowShape(640,480);
    
    ofEnableAlphaBlending();
    ofSetBackgroundAuto(false);
    
    
    
    //  box2dの設定
    world2d.init();
    world2d.setFPS(30.0);
    world2d.setGravity(0, 1);
    //  alphabet画像の読み込み
 
    alphabet_a.load("a_black.png");
    alphabet_a.setAnchorPercent(0.5, 0.5);
    
    //  地面の設定
    world2d.createGround(0, 480, 640,480);
    
    //webカメラの設定
    cam.initGrabber(640,480);
    
    gui.setup();
    gui.add(minArea.set("Min area", 10, 1, 100));
    gui.add(maxArea.set("Max area", 400, 1, 500));
    gui.add(threshold.set("Threshold", 128, 0, 255));
    gui.add(holes.set("Holes", false));
    
    // 摩擦係数を設定
    friction = 0.002;
    // パーティクルを初期化
    setInit(ofVec2f(ofGetWidth()/2, ofGetHeight()/2));
    
}
void ofApp::makeAlphabet(float x, float y, float size) {
    //  新しい円を作成
    ofPtr<ofxBox2dCircle> circle = ofPtr<ofxBox2dCircle>(new ofxBox2dCircle);
    //  set attributes to this circle (density, bounce, friction)
    circle.get()->setPhysics(1.0, 0.5, 0.1);
    circle.get()->setup(world2d.getWorld(), x, y, size);
    //  add this circle to "circles" vector
    circles.push_back(circle);
}

bool objectKiller(ofPtr<ofxBox2dBaseShape> shape) {
    float yPos = shape.get()->getPosition().y;
    return (yPos >= 400); //座標が400
}

void ofApp::update() {
    
    //  40%の確率でアルファベット発生させる
    if (ofRandom(0, 100) < 40){
        makeAlphabet(ofRandom(-40, 640), -40, ofRandom(1, 5));
    }
    ofRemove(circles, objectKiller);
    

    cam.update();
    if(cam.isFrameNew()) {
        contourFinder2.setMinAreaRadius(minArea);
        contourFinder2.setMaxAreaRadius(maxArea);
        contourFinder2.setThreshold(threshold);
        contourFinder2.findContours(cam);
        contourFinder2.setFindHoles(holes);
    }
    

    //Edgeで物体が反発する処理
    for (int i=0; i<edges.size(); i++) {
        if(edges[i]->isBody()) edges[i]->destroy();
    }
    edges.clear();

    for (int i=0; i<contourFinder2.size(); i++) {
        if (contourFinder2.getPolyline(i).size()>1) {
        edges.push_back(new ofxBox2dEdge());
        edges.back()->setPhysics(3.0, 0.53, 0.1);
        edges.back()->addVertexes(contourFinder2.getPolyline(i));
        edges.back()->setPhysics(0.0, 0.5, 0.5);
        edges.back()->create(world2d.getWorld());

        }
    }
    
    // 力をリセット
    resetForce();
    // 重力を加える
    addForce(ofVec2f(0, 0.25));
    // 力の更新 (摩擦)
    updateForce();
    // パーティクルの座標を全て更新
    updatePos();
    // 画面からはみ出たらバウンドさせる
    bounceOffWalls();

    world2d.update();
   
}

void ofApp::draw() {
    
    ofSetColor(255, 255, 255, 15);
    ofDrawBox(0, 0, ofGetWidth(), ofGetHeight());
    
    //円を画像として描画する
    for (int i = 0; i < circles.size(); i++) {
        
        ofPoint pos = circles[i].get()->getPosition();
        float size = circles[i].get()->getRadius()*5.0;
 
        float yPos = circles[i].get()->getPosition().y;
        alphabet_a.draw(pos, size, size);
        
    // 座標が400以上の場合、現在の座標を中心として円の数だけ描画
        if(yPos>=400){
            for (int i = 0; i < CIRCLE_NUM; i++) {
                ofSetColor(0, 120, 100, 15);
                ofDrawCircle(position[i],1);
            }
            setInit(pos);
        }
    }

  
    //cam.draw(0, 0);
    ofSetColor(255, 255, 255);
    ofSetLineWidth(10);
    contourFinder2.draw();
    //gui.draw();
    

    ofDrawBitmapStringHighlight("Framerate : "+ofToString(ofGetFrameRate()), 10, 20);    
}

void ofApp::setInit(ofVec2f initPos){
    // 画面内のランダムな場所と速度をパーティクルの数だけ指定
    
    for (int i = 0; i < CIRCLE_NUM; i++) {
        position[i].x = initPos.x;
        position[i].y = initPos.y;
        float length = ofRandom(20);
        float angle = ofRandom(PI * 2);
        velocity[i].x = cos(angle) * length;
        velocity[i].y = sin(angle) * length;
        force[i].set(0, 0);
    }
}

//--------------------------------------------------------------
void ofApp::resetForce(){
    // 力をリセット
    for (int i = 0; i < CIRCLE_NUM; i++) {
        force[i].set(0, 0);
    }
}

//--------------------------------------------------------------
void ofApp::addForce(ofVec2f _force){
    // 力を加える
    for (int i = 0; i < CIRCLE_NUM; i++) {
        force[i] += _force;
    }
}

//--------------------------------------------------------------
void ofApp::updateForce(){
    // 力の更新 (摩擦)
    for (int i = 0; i < CIRCLE_NUM; i++) {
        force[i] -= velocity[i] * friction;
    }
}

//--------------------------------------------------------------
void ofApp::updatePos(){
    // パーティクルの座標を全て更新
    for (int i = 0; i < CIRCLE_NUM; i++) {
        velocity[i] += force[i];
        position[i] += velocity[i];
    }
}

//--------------------------------------------------------------
// 画面の端でバウンドする
void ofApp::bounceOffWalls(){
    float minx = 0;
    float miny = 0;
    float maxx = ofGetWidth();
    float maxy = ofGetHeight();
    for (int i = 0; i < CIRCLE_NUM; i++) {
        if (position[i].x > maxx){
            position[i].x = maxx;
            velocity[i].x *= -1;
        }
        if (position[i].x < minx){
            position[i].x = minx;
            velocity[i].x *= -1;
        }
        
        if (position[i].y > maxy){
            position[i].y = maxy;
            velocity[i].y *= -1;
        }
        if (position[i].y < miny){
            position[i].y = miny;
            velocity[i].y *= -1;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
   //キーボードを押しても描画される
    if (key == 'a') {
        makeAlphabet(ofRandom(-40, 680), -40, ofRandom(5, 10));
    }
    
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
