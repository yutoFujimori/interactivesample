#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
    //  ウィンドウの設定
    ofBackground(255, 255, 255,50);
    ofSetWindowShape(640,480);
    //  box2dの設定
    world2d.init();
    world2d.setFPS(30.0);
    world2d.setGravity(0, 1);
    //  alphabet画像の読み込み
    alphabet.load("a.png");
    alphabet.setAnchorPercent(0.5, 0.5);
    //  地面の設定
    world2d.createGround(0, 480, 640,480);
    
    //webカメラの設定
    cam.initGrabber(640,480);
    
    gui.setup();
    gui.add(minArea.set("Min area", 10, 1, 100));
    gui.add(maxArea.set("Max area", 200, 1, 500));
    gui.add(threshold.set("Threshold", 128, 0, 255));
    gui.add(holes.set("Holes", false));
}
void ofApp::makeAlphabet(float x, float y, float size) {
    //  create a new circle
    ofPtr<ofxBox2dCircle> circle = ofPtr<ofxBox2dCircle>(new ofxBox2dCircle);
    //  set attributes to this circle (density, bounce, friction)
    circle.get()->setPhysics(1.0, 0.5, 0.1);
    circle.get()->setup(world2d.getWorld(), x, y, size);
    //  add this circle to "circles" vector
    circles.push_back(circle);
}

bool objectKiller(ofPtr<ofxBox2dBaseShape> shape) {
    float yPos = shape.get()->getPosition().y;
    return (yPos >= 300);
}

void ofApp::update() {
    
    //  アルファベット発生させる
    if (ofRandom(0, 200) < 40){
        makeAlphabet(ofRandom(-40, 680), -40, ofRandom(5, 10));
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
        if (contourFinder2.getPolyline(i).size()>2) {
        edges.push_back(new ofxBox2dEdge());
        edges.back()->setPhysics(3.0, 0.53, 0.1);
        edges.back()->addVertexes(contourFinder2.getPolyline(i));
        edges.back()->setPhysics(0.0, 0.5, 0.5);
        edges.back()->create(world2d.getWorld());

        }
    }
    
        
    world2d.update();
            
    
}

void ofApp::draw() {
    //  draw each circle


    for (int i = 0; i < circles.size(); i++) {
        ofPoint pos = circles[i].get()->getPosition();
        float size = circles[i].get()->getRadius();
        alphabet.draw(pos, size, size);
    }
    
    
    //cam.draw(0, 0);
    ofSetColor(140, 140, 200);
    ofFill();
    contourFinder2.draw();
    gui.draw();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == 'a') {
        //  create a new circle
        ofPtr<ofxBox2dCircle> circle = ofPtr<ofxBox2dCircle>(new ofxBox2dCircle);
        //  set attributes to this circle (density, bounce, friction)
        circle.get()->setPhysics(1.0, 0.5, 0.1);
        circle.get()->setup(world2d.getWorld(), mouseX, mouseY, ofRandom(10, 20));
        //  add this circle to "circles" vector
        circles.push_back(circle);
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
