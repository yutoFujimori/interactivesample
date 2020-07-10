#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    vidGrabber.setVerbose(true);
    vidGrabber.setup(320,240);

    colorImg.allocate(320,240);//画像バッファに幅と高さを割り当てる
    grayImage.allocate(320,240);
    grayBg.allocate(320,240);
    
    grayDiff.allocate(320,240);

    bLearnBakground = true;
    threshold = 80;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    ofBackground(100,100,100);

    bool bNewFrame = false;

    
    vidGrabber.update();
    bNewFrame = vidGrabber.isFrameNew();
    
    if (bNewFrame){

        colorImg.setFromPixels(vidGrabber.getPixels());


        grayImage = colorImg;
        if (bLearnBakground == true){
            grayBg = grayImage;        // the = sign copys the pixels from grayImage into grayBg (operator overloading)
            bLearnBakground = false;
        }

        // take the abs value of the difference between background and incoming and then threshold:
        grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(threshold);

        // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
        // also, find holes is set to true so we will get interior contours as well....
        // 輪郭を描く
        // 第1引数 輪郭検出対象
        // 第2引数 検出する最小の大きさ(20)
        // 第3引数 検出する最大の大きさ
        // 第4引数 検出する数
        // 第5引数 穴が空いたものを検出するかどうか trueで　検出する
        contourFinder.findContours(grayDiff, 20, (340*240)/3, 10, false);
        
        // find holes
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // draw the incoming, the grayscale, the bg and the thresholded difference
    ofSetHexColor(0xffffff);
    //colorImg.draw(20,20);
    //grayImage.draw(360,20);
    //grayBg.draw(20,280);
    grayDiff.draw(20,20);

    // then draw the contours:

    ofFill();
    ofSetHexColor(0x333333);
    ofDrawRectangle(360,200,320,240);
    ofSetHexColor(0xffffff);

    // we could draw the whole contour finder
    //contourFinder.draw(360,540);

    // or, instead we can draw each blob individually from the blobs vector,
    // this is how to get access to them:
    for (int i = 0; i < contourFinder.nBlobs; i++){
        contourFinder.blobs[i].draw(360,200);
        
        // draw over the centroid if the blob is a hole
        ofSetColor(255);
        if(contourFinder.blobs[i].hole){
            ofDrawBitmapString("hole",
                contourFinder.blobs[i].boundingRect.getCenter().x + 360,
                contourFinder.blobs[i].boundingRect.getCenter().y + 200);
        }
    }

    // finally, a report:
    ofSetHexColor(0xffffff);
    stringstream reportStr;
    reportStr << "bg subtraction and blob detection" << endl
              << "press ' ' to capture bg" << endl
              << "threshold " << threshold << " (press: t/-)" << endl
              << "num blobs found " << contourFinder.nBlobs << ", fps: " << ofGetFrameRate();
    ofDrawBitmapString(reportStr.str(), 20, 600);

}

//---------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch (key){
        case ' ':
            bLearnBakground = true;
            break;
        case 't':
            threshold ++;
            if (threshold > 255) threshold = 255;
            break;
        case '-':
            threshold --;
            if (threshold < 0) threshold = 0;
            break;
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
