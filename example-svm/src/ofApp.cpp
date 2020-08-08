#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetWindowShape(1280, 720);
    
    ofSetBackgroundAuto(false);
    
    learned_functions = vector<pfunct_type>(4);

    // Load SVM data model
    dlib::deserialize(ofToDataPath("data_ecstatic_smile.func")) >> learned_functions[0];
    dlib::deserialize(ofToDataPath("data_small_smile.func")) >> learned_functions[1];
    dlib::deserialize(ofToDataPath("data_o.func")) >> learned_functions[2];
    dlib::deserialize(ofToDataPath("data_neutral.func")) >> learned_functions[3];
    
    // Setup value filters for the classifer
    neutralValue.setFc(0.04);
    bigSmileValue.setFc(0.04);
    smallSmileValue.setFc(0.04);
    oValue.setFc(0.04);

    // All examples share data files from example-data, so setting data path to this folder
    // This is only relevant for the example apps
    ofSetDataPathRoot(ofFile(__BASE_FILE__).getEnclosingDirectory()+"../../model/");
    
    // Setup grabber
    grabber.setup(1280,720);
    
    // Setup tracker
    tracker.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
    if(grabber.isFrameNew()){
        tracker.update(grabber);
        
        if(tracker.size() > 0){
            // Run the classifiers and update the filters
            bigSmileValue.update(learned_functions[0](makeSample()));
            smallSmileValue.update(learned_functions[1](makeSample()));
            oValue.update(learned_functions[2](makeSample()));
            neutralValue.update(learned_functions[3](makeSample()));
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(0,0,0,15);
    
    //grabber.draw(0, 0);
    tracker.drawDebug();
    
    //特徴点の位置を順番に数字で表す
    for(int i = 0; i < tracker.getInstances().size(); i++){
        for(int j = 0; j < tracker.getInstances()[i].getLandmarks().getImagePoints().size(); j++){
            glm::vec2 pos = tracker.getInstances()[i].getLandmarks().getImagePoints()[j];
            ofSetColor(255);
            ofDrawCircle(pos, 5);
            ofSetColor(255,0,0);
            ofDrawBitmapString(ofToString(i*tracker.getInstances().size() + j),pos.x,pos.y);
            
  //          ofLog(OF_LOG_NOTICE) << " i: " << i;
  //          ofLog(OF_LOG_NOTICE) << " j: " << j;
  //          ofLog(OF_LOG_NOTICE) << " i*tracker.getInstances().size() + j: " << i*tracker.getInstances().size() + j;
  //          ofLog(OF_LOG_NOTICE) << " position: " << pos;
            
            //口角の高さによって円の大きさが変わる
   //         if( i*tracker.getInstances().size() + j == 48)
   //         {
   //             int instance_r=50;
   //
   //             ofSetColor(255,0,0);
   //             ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2,instance_r+pos.y*0.1);//<--これだと円の大きさが小さくなる座標系の問題
   //         }
            
        }
    }

    
#ifndef __OPTIMIZE__
    ofSetColor(ofColor::red);
    ofDrawBitmapStringHighlight("Framerate : "+ofToString(ofGetFrameRate()), 10, 20);

#endif
    
    //感情の度量を横棒グラフで表現
    //
    ofPushMatrix();
    ofTranslate(0, 100);
    for (int i = 0; i < 4; i++) {
        ofSetColor(255);
        
        string str;
        float val;
        switch (i) {
            case 0:
                str = "BIG SMILE";
                val = bigSmileValue.value();
                break;
            case 1:
                str = "SMALL SMILE";
                val = smallSmileValue.value();
                break;
            case 2:
                str = "OOO MOUTH";
                val = oValue.value();
                break;
            case 3:
                str = "NEUTRAL MOUTH";
                val = neutralValue.value();
                break;
        }
        
   //     ofDrawBitmapStringHighlight(str, 20, 0);
   //     ofDrawRectangle(20, 20, 300*val, 30);
        
        ofLog(OF_LOG_NOTICE) << "value:" << val;
        
        
        ofNoFill();
    //    ofDrawRectangle(20, 20, 300, 30);
        ofFill();       
        
        ofTranslate(0, 70);
    }
    
    //表情の種類と強さによって描画される三角形や
    
    float bsvalue = bigSmileValue.value()*1000;
    
    float ssvalue = smallSmileValue.value()*1000;
    
    float neuvalue = neutralValue.value()*1000;
    
    ofVec2f shapePos(ofGetWidth()/2,45);
    
    int numTriangles = 10;
    int minOffset = 5;
    int maxOffset = 70;
    int alpha = 150;
    
    
    for (int t=0; t<numTriangles; t++) {
        
        float offsetDistance_bigsmile = ofRandom(minOffset+bsvalue, maxOffset+bsvalue);
        
        float offsetDistance_smallsmile = ofRandom(minOffset+ssvalue, maxOffset+ssvalue);
        
        float offsetDistance_neutral = ofRandom(minOffset+neuvalue, maxOffset+neuvalue);
        
        
        ofVec2f tri1_p1(0, 25.0);
        ofVec2f tri1_p2(100, 0);
        ofVec2f tri1_p3(0, -25.0);
        
        ofVec2f tri2_p1(0, 25.0);
        ofVec2f tri2_p2(100, 0);
        ofVec2f tri2_p3(0, -25.0);
        
        ofVec2f tri3_p1(0, 25.0);
        ofVec2f tri3_p2(100, 0);
        ofVec2f tri3_p3(0, -25.0);
        
        
        float rotation = ofRandom(360); // The rotate function uses degrees!
        //生成した三角形の鋭利な方を外側に向ける
        tri1_p1.rotate(rotation);
        tri1_p2.rotate(rotation);
        tri1_p3.rotate(rotation);
        
        tri2_p1.rotate(rotation);
        tri2_p2.rotate(rotation);
        tri2_p3.rotate(rotation);
        
        tri3_p1.rotate(rotation);
        tri3_p2.rotate(rotation);
        tri3_p3.rotate(rotation);
        
        ofVec2f triangleOffset_bigsmile(offsetDistance_bigsmile, 0.0);
        triangleOffset_bigsmile.rotate(rotation);
        
        ofVec2f triangleOffset_smallsmile(offsetDistance_smallsmile, 0.0);
        triangleOffset_smallsmile.rotate(rotation);
        
        ofVec2f triangleOffset_neutral(offsetDistance_neutral, 0.0);
        triangleOffset_neutral.rotate(rotation);

        
        tri1_p1 += shapePos + triangleOffset_bigsmile;
        tri1_p2 += shapePos + triangleOffset_bigsmile;
        tri1_p3 += shapePos + triangleOffset_bigsmile;
        
        tri2_p1 += shapePos + triangleOffset_smallsmile;
        tri2_p2 += shapePos + triangleOffset_smallsmile;
        tri2_p3 += shapePos + triangleOffset_smallsmile;
        
        tri3_p1 += shapePos + triangleOffset_neutral;
        tri3_p2 += shapePos + triangleOffset_neutral;
        tri3_p3 += shapePos + triangleOffset_neutral;
        

        ofSetColor(255, alpha);
        ofDrawTriangle(tri1_p1, tri1_p2, tri1_p3);
        
        ofSetColor(10, 10, 255, alpha);
        ofDrawTriangle(tri2_p1, tri2_p2, tri2_p3);
        
        ofSetColor(0, 0, 0, alpha);
        ofDrawTriangle(tri3_p1, tri3_p2, tri3_p3);
    }
    
  ofPopMatrix();

}


// Function that creates a sample for the classifier containing the mouth and eyes
sample_type ofApp::makeSample(){
    auto outer = tracker.getInstances()[0].getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::OUTER_MOUTH);
    auto inner = tracker.getInstances()[0].getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::INNER_MOUTH);
    
    auto lEye = tracker.getInstances()[0].getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::LEFT_EYE);
    auto rEye = tracker.getInstances()[0].getLandmarks().getImageFeature(ofxFaceTracker2Landmarks::RIGHT_EYE);
    
    ofVec2f vec = rEye.getCentroid2D() - lEye.getCentroid2D();
    float rot = vec.angle(ofVec2f(1,0));
    
    vector<ofVec2f> relativeMouthPoints;
    
    ofVec2f centroid = outer.getCentroid2D();
    for(ofVec2f p : outer.getVertices()){
        p -= centroid;
        p.rotate(rot);
        p /= vec.length();
        
        relativeMouthPoints.push_back(p);
    }
    
    for(ofVec2f p : inner.getVertices()){
        p -= centroid;
        p.rotate(rot);
        p /= vec.length();
        
        relativeMouthPoints.push_back(p);
    }
    
    sample_type s;
    for(int i=0;i<20;i++){
        s(i*2+0) = relativeMouthPoints[i].x;
        s(i*2+1) = relativeMouthPoints[i].y;
    }
    return s;
}
