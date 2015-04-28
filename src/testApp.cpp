#include "testApp.h"

using namespace ofxCv;
using namespace cv;

//------------------------------------------------------------------------------------ SETUP
void testApp::setup() {
    //image.setup();
    ofSetVerticalSync(true);
    cam.initGrabber(1280, 960); //verandert schermgrootte
    
    tracker.setup(); //tracker.cc staat in libs/facetracker/src/libs
    tracker.setRescale(.5);
    ofSetFrameRate(60);
    
    opacity = 0;
    Uitbeeld = false;
    
    myFont.loadFont("keepcalm.ttf", 24);
}

//------------------------------------------------------------------------------------ UPDATE
void testApp::update() {
    cam.update();
    if(cam.isFrameNew()) {
        if(tracker.update(toCv(cam))) {
            classifier.classify(tracker);
        }
    }
    ofSetLineWidth(2);
    
    if (tracker.failed == true){
        opacity = opacity -10;
    }
    else{
        opacity = 255;
    }
    
    // -------------------------------------------------------- DRAWING LEFT EYE
    
    if(tekenLeftEye == true){
        ofSetLineWidth(3);
        if (ofGetMousePressed() == true){
            
            if (artmode == false){
                // first, make a point
                ofPoint pt;
                int mouseXreverse = 1280 - mouseX;
                pt.set(mouseXreverse, mouseY);
                //laatsteptX = mouseX;
                // laatsteptY = mouseY;
                // then add it to the line.
                lineLeft.addVertex(pt);
            }
            
        }
    }
    //-------------------------------verplaats tekening
    if (tracker.failed == false){
        for (int i = 0; i < lineLeft.getVertices().size(); i++){
            lineLeft.getVertices()[i].x += diffLeftEyeX;
            lineLeft.getVertices()[i].y += diffLeftEyeY;
            //             if (ofGetMousePressed() == true){
            //           ofPoint diff = ofPoint (mouseX, mouseY) - ofPoint(ofGetWidth()/2, ofGetHeight()/2);
            //           //ofPoint diff = ofPoint (laatsteptX, laatsteptY) - ofPoint(mouseX, mouseY);
            //            line.getVertices()[i].x -= diff.x * 0.05;
            //            line.getVertices()[i].y -= diff.y * 0.05;
            //             }
        }
        for (int i = 0; i < lines.size(); i++){
            lines[i].a.x -= diffLeftEyeX;
            // lines[i].b.y += diffLeftEyeX;
            
            lines[i].a.y += diffLeftEyeY;
            lines[i].b.x -= diffLeftEyeX;
            lines[i].b.y += diffLeftEyeY;
            
            
        }
        
        
        
        
        // ofLine( lines[i].a.x + diffNoseBaseX, lines[i].a.y + diffNoseBaseY, lines[i].b.x + diffNoseBaseX, lines[i].b.y + diffNoseBaseY);
    }
    
    
    
    
    // -------------------------------------------------------- DRAWING RIGHT EYE
    if(tekenRightEye == true){
        ofSetLineWidth(3);
        if (ofGetMousePressed() == true){
            // first, make a point
            if (artmode == false){
                ofPoint pt;
                int mouseXreverse = 1280 - mouseX;
                pt.set(mouseXreverse, mouseY);
                // then add it to the line.
                lineRight.addVertex(pt);
            }
        }
    }
    //-------------------------------verplaats tekening
    if (tracker.failed == false){
        for (int i = 0; i < lineRight.getVertices().size(); i++){
            lineRight.getVertices()[i].x += diffRightEyeX;
            lineRight.getVertices()[i].y += diffRightEyeY;
        }
    }
    
    // -------------------------------------------------------- DRAWING NOSE BASE
    if(tekenNoseBase == true){
        ofSetLineWidth(3);
        if (ofGetMousePressed() == true){
            // first, make a point
            if (artmode == false){
                ofPoint pt;
                int mouseXreverse = 1280 - mouseX;
                pt.set(mouseXreverse, mouseY);
                // then add it to the line.
                lineNose.addVertex(pt);
            }
        }
    }
    //-------------------------------verplaats tekening
    if (tracker.failed == false){
        for (int i = 0; i < lineNose.getVertices().size(); i++){
            lineNose.getVertices()[i].x += diffNoseBaseX;
            lineNose.getVertices()[i].y += diffNoseBaseY;
        }
    }
    // -------------------------------------------------------- DRAWING INNER MOUTH
    if(tekenInnerMouth == true){
        ofSetLineWidth(3);
        if (ofGetMousePressed() == true){
            // first, make a point
            if (artmode == false){
                ofPoint pt;
                int mouseXreverse = 1280 - mouseX;
                pt.set(mouseXreverse, mouseY);
                // then add it to the line.
                lineMouth.addVertex(pt);
            }
        }
    }
    //-------------------------------verplaats tekening
    if (tracker.failed == false){
        for (int i = 0; i < lineMouth.getVertices().size(); i++){
            lineMouth.getVertices()[i].x += diffInnerMouthX;
            lineMouth.getVertices()[i].y += diffInnerMouthY;
        }
    }
    // -------------------------------------------------------- DRAWING INNER MOUTH
    if(tekenJawLeft == true){
        if (ofGetMousePressed() == true){
            ofSetLineWidth(3);
            // first, make a point
            if (artmode == false){
                ofPoint pt;
                int mouseXreverse = 1280 - mouseX;
                pt.set(mouseXreverse, mouseY);
                // then add it to the line.
                lineJawLeft.addVertex(pt);
            }
        }
    }
    //-------------------------------verplaats tekening
    if (tracker.failed == false){
        for (int i = 0; i < lineJawLeft.getVertices().size(); i++){
            lineJawLeft.getVertices()[i].x += diffJawLeftX;
            lineJawLeft.getVertices()[i].y += diffJawLeftY;
        }
    }
}

//------------------------------------------------------------------------------------ DRAW
void testApp::draw() {
    
    //mirror canvas
    ofScale( -1, 1, 1 );
    ofTranslate( -ofGetWidth(), 0, 0 );
    
    //cam and tracker
    ofSetColor(255, 255, 255);
    cam.draw(0, 0);
    //tracker.draw(); //draws the standard outline of the face registered
    //cout << "failed: " << tracker.failed << endl; //print detection status
    
    int w = 100; //wat is dit?
    int h = 12;
    
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(5, 10);//move the coordinate system to position 5,10
    
    ofPolyline leftEye, rightEye, leftEyebrow, rightEyebrow, noseBase, innerMouth, jaw;
    
    leftEye = tracker.getImageFeature(ofxFaceTracker::LEFT_EYE);
    rightEye = tracker.getImageFeature(ofxFaceTracker::RIGHT_EYE);
    leftEyebrow = tracker.getImageFeature(ofxFaceTracker::LEFT_EYEBROW);
    rightEyebrow = tracker.getImageFeature(ofxFaceTracker::RIGHT_EYEBROW);
    //    noseBridge = tracker.getImageFeature(ofxFaceTracker::NOSE_BRIDGE);
    noseBase = tracker.getImageFeature(ofxFaceTracker::NOSE_BASE);
    innerMouth = tracker.getImageFeature(ofxFaceTracker::INNER_MOUTH);
    //    outerMouth = tracker.getImageFeature(ofxFaceTracker::OUTER_MOUTH);
    jaw = tracker.getImageFeature(ofxFaceTracker::JAW);
    
    ofEnableAntiAliasing();
    ofSetColor(255,255,255, opacity);
    
    //DRAWING TOOL
    ofSetColor(90,200,90, opacity);
    lineLeft.draw();
    ofSetColor(77,170,144, opacity);
    lineRight.draw();
    ofSetColor(255,280,0, opacity);
    lineNose.draw();
    ofSetColor(255,17,17, opacity);
    lineMouth.draw();
    ofSetColor(210,100,10, opacity);
    lineJawLeft.draw();
    
    ofScale( -1, 1, 1 );
    ofTranslate( -ofGetWidth(), 0, 0 );
    
    if (artmode== true){
        ofEnableAlphaBlending();
        ofSetLineWidth(2);
        ofSetColor(255, 255, 255, 50);
        
        
        for (int i = 0; i < lines.size(); i++){
            ofLine( lines[i].a.x, lines[i].a.y, lines[i].b.x, lines[i].b.y);
            // ofLine( lines[i].a.x + diffNoseBaseX, lines[i].a.y + diffNoseBaseY, lines[i].b.x + diffNoseBaseX, lines[i].b.y + diffNoseBaseY);
        }
    }
    ofScale( -1, 1, 1 );
    ofTranslate( -ofGetWidth(), 0, 0 );
    
    //..................................................................................................................
    //    In this part of the code, we draw objects on certain face positions (leftEye, rightEye etc.) We draw a small circle as indicator at the initial state (active == false). We draw a text input-fiel (currently just a white rectangle) when user clicked on the circle. (active == true)
    //..................................................................................................................
    
    //set object characteristics
    ofSetColor(rActive, gActive, bActive);
    ofNoFill();
    ofSetLineWidth(3);
    
    //---------------------------------------------------------------------------- RIGHT-EYE
    prevRightEyeX = rightEyeX;
    prevRightEyeY = rightEyeY;
    
    vector<ofPoint> rightEyeVertices = rightEye.getVertices();
    for (int i=0; i <rightEyeVertices.size(); i++) {
        ofPoint p = rightEyeVertices[1];
        rightEyeX = p.x; //store position for rightEyeX
        rightEyeY = p.y;
        
        diffRightEyeX = rightEyeX - prevRightEyeX;
        diffRightEyeY = rightEyeY - prevRightEyeY;
        //cout << "diffrightEyeX: " << diffRightEyeX << endl;
        //cout << "diffrightEyeY: " << diffRightEyeY << endl;
        
        //White circle
        if (rightEyeActive == true){ //check if user clicked in area of rightEye circle
            ofFill();
            ofSetColor(77,170,144);
            ofEllipse(p.x, p.y, 20, 20); //draw a white circle
            doenRechts = true;}
        //Red circle
        if(rightEyeActive == false){
            ofNoFill();
            ofSetColor(77,170,144);
            ofEllipse(p.x, p.y, 20, 20);
            doenRechts = false;}
    }
    
    //---------------------------------------------------------------------------- LEFT-EYE
    ofSetColor(255,25,25);
    prevLeftEyeX = leftEyeX;
    prevLeftEyeY = leftEyeY;
    
    vector<ofPoint> leftEyeVertices = leftEye.getVertices();
    for (int i=0; i <leftEyeVertices.size(); i++) {
        ofPoint p = leftEyeVertices[1];
        leftEyeX = p.x; //store position
        leftEyeY = p.y;
        
        diffLeftEyeX = leftEyeX - prevLeftEyeX;
        diffLeftEyeY = leftEyeY - prevLeftEyeY;
        //cout << "diffleftEyeX: " << diffLeftEyeX << endl;
        //cout << "diffleftEyeY: " << diffLeftEyeY << endl;
        
        //White circle
        if (leftEyeActive == true){
            ofFill();
            ofSetColor(90,200,90);
            //ofSetColor(rActive, gActive, bActive);
            ofEllipse(p.x, p.y, 20, 20);
            doenLinks = true;}
        //Red circle
        if(leftEyeActive == false){
            ofSetColor(90,200,90);
            ofNoFill();
            ofEllipse(p.x, p.y, 20, 20);
            doenLinks = false;}
    }
    
    //---------------------------------------------------------------------------- NOSE-BASE
    prevNoseBaseX = noseBaseX;
    prevNoseBaseY = noseBaseY;
    
    vector<ofPoint> noseBaseVertices = noseBase.getVertices();
    for (int i=0; i <noseBaseVertices.size(); i++) {
        ofPoint p = noseBaseVertices[2];
        noseBaseX = p.x; //store position
        noseBaseY = p.y-20;
        
        diffNoseBaseX = noseBaseX - prevNoseBaseX;
        diffNoseBaseY = noseBaseY - prevNoseBaseY;
        
        //White circle
        if (noseBaseActive == true){
            ofFill();
            ofSetColor(255,280,0);
            ofEllipse(p.x, p.y-20, 20, 20);
            doenNeus = true;}
        //Red circle
        if(noseBaseActive == false){
            ofSetColor(255,280,0);
            ofNoFill();
            ofEllipse(p.x, p.y-20, 20, 20);
            doenNeus = false;}
    }
    
    //---------------------------------------------------------------------------- INNER-MOUTH
    prevInnerMouthX = innerMouthX;
    prevInnerMouthY = innerMouthY;
    
    vector<ofPoint> innerMouthVertices = innerMouth.getVertices();
    for (int i=0; i <innerMouthVertices.size(); i++) {
        ofPoint p = innerMouthVertices[2];
        innerMouthX = p.x; //store position
        innerMouthY = p.y + 5;
        
        diffInnerMouthX = innerMouthX - prevInnerMouthX;
        diffInnerMouthY = innerMouthY - prevInnerMouthY;
        
        //White circle
        if (innerMouthActive == true){
            ofFill();
            ofSetColor(255,17,17);
            ofEllipse(p.x, p.y+5, 20, 20);
            doenMond = true;}
        //Red circle
        if(innerMouthActive == false){
            ofSetColor(255,17,17);
            ofNoFill();
            ofEllipse(p.x, p.y+5, 20, 20);
            doenMond = false;}
    }
    
    //---------------------------------------------------------------------------- JAW LINKS
    prevJawLeftX = jawLeftX;
    prevJawLeftY = jawLeftY;
    
    vector<ofPoint> jawVertices = jaw.getVertices();
    for (int i=0; i <jawVertices.size(); i++) {
        ofPoint p = jawVertices[8];
        jawLeftX = p.x; //store position
        jawLeftY = p.y;
        
        diffJawLeftX = jawLeftX - prevJawLeftX;
        diffJawLeftY = jawLeftY - prevJawLeftY;
        
        //White circle
        if (jawLeftActive == true){
            ofFill();
            ofSetColor(210,100,10);
            ofEllipse(p.x, p.y, 20, 20);
            doenKaakLinks = true;}
        //Red circle
        if(jawLeftActive == false){
            ofSetColor(210,100,10);
            ofNoFill();
            ofEllipse(p.x, p.y, 20, 20);
            doenKaakLinks = false;}
    }
    
    //reset object characteristics
    ofFill();
    ofSetLineWidth(1);
    
    //dit was om een class uit te proberen:
    // ofSetColor(255,40,240);
    //image.draw();
    
    //new list button
    ofSetColor(20, 230, 200);
    ofRectRounded(30, 20, 130, 60, 10);
    ofSetColor(255);
    //mirror canvas
    ofScale( -1, 1, 1 );
    ofTranslate( -ofGetWidth(), 0, 0 );
    myFont.drawString("NEW", 1145,64);
    
    if(artmode == true){
        ofFill();
    }
    if(artmode == false){
        ofNoFill();
    }
    //mirror canvas
    ofScale( -1, 1, 1 );
    ofTranslate( -ofGetWidth(), 0, 0 );
    //new list button
    ofSetLineWidth(2);
    ofSetColor(200, 200, 200);
    ofRectRounded(30, 100, 230, 60, 10);
    ofSetColor(255);
    //mirror canvas
    ofScale( -1, 1, 1 );
    ofTranslate( -ofGetWidth(), 0, 0 );
    myFont.drawString("ART MODE", 1038,143);
    
}

//------------------------------------------------------------------------------------ KEY PRESSED
void testApp::keyPressed(int key) {
    if (key == OF_KEY_BACKSPACE){
        //lineLeft.clear();
    }
}

//..................................................................................................................
//  In this part of the code, we check the mouse input of the user. There are two states currently for every part of the
//  face. (leftEyeActive == false and leftEyeactive == true. rightEyeActive == false and rightEyeActive == true etc. etc.).
//  In the beginning, all states are false. When user clicks on a part of the face (the circle that is appearing there), the
//  state becomes active. When the user clicks on the rectangle that appears, the state becomes inactive again (false).
//..................................................................................................................

//------------------------------------------------------------------------------------ MOUSE PRESSED
void testApp::mousePressed(int x, int y, int button){ //When user clicks, this function is activated.
    
    
    
    ox = 1280-x;
    cout << "MouseX = " << ox << endl;
    
    //------------------------------------------------------------DISTANCE TO MOUSECLICK
    if(ox > 30 && ox < 360 && y > 100 && y < 160 ){
        if (artmode == false)
        {
            artmode = true;
        }
        else if (artmode == true)
        {
            artmode = false;
        }
        cout << "artmode: " << artmode << endl;
        
        //    if(ox > 30 && ox < 360 && y > 100 && y <90 && artmode == true){
        //                artmode = false;
        //            }
    }
    
    
    //is click on CLEAR?
    if(ox > 30 && ox <160 && y > 20 && y <80 ){
        lineLeft.clear();
        lineRight.clear();
        lineNose.clear();
        lineMouth.clear();
        lineJawLeft.clear();
        lines.clear();
        
        cout << "clear" << endl;
    }
    
    int distanceRightEye = ofDist(rightEyeX, rightEyeY, ox, y); //Dist to rightEye
    cout << "rightEyedist" << distanceRightEye << endl;
    
    int distanceLeftEye = ofDist(leftEyeX, leftEyeY, ox, y); //Dist to leftEye
    cout << "leftEyedist" << distanceLeftEye << endl;
    
    int distanceNoseBase = ofDist(noseBaseX, noseBaseY, ox, y); //Dist to noseBase
    cout << "noseBasedist" << distanceNoseBase << endl;
    
    int distanceInnerMouth = ofDist(innerMouthX, innerMouthY, ox, y); //Dist to innerMouth
    cout << "innerMouthdist" << distanceInnerMouth<< endl;
    
    int distanceJawLeft = ofDist(jawLeftX, jawLeftY, ox, y); //Dist to jawLeft
    cout << "jawLeftdist" << distanceJawLeft << endl;
    
    //-- 2. We check if these distances are smaller than the radius of the circles, again for every part of the face:
    
    //----------------------------------------------------------------------- ACTIVE = FALSE
    
    //Right-eye
    if((distanceRightEye < 20) && (rightEyeActive == false) && (doenRechts == false)){
        rightEyeActive = true;
        cout << "rightEyeActive = true" << endl;
    }
    //Left-eye
    if((distanceLeftEye < 20) && (leftEyeActive == false) && (doenLinks == false)){
        leftEyeActive = true;
        cout << "leftEyeActive = true" << endl;
    }
    //Nose-base
    if((distanceNoseBase < 20) && (noseBaseActive == false) && (doenNeus == false)){
        noseBaseActive = true;
        cout << "noseBaseActive = true" << endl;
    }
    //Innermouth
    if((distanceInnerMouth < 20) && (innerMouthActive == false) && (doenMond == false)){
        innerMouthActive = true;
        cout << "innermouthActive = true" << endl;
    }
    //Jaw-links
    if((distanceJawLeft < 20) && (jawLeftActive == false) && (doenKaakLinks == false)){
        jawLeftActive = true;
        cout << "jawLeftActive = true" << endl;
    }
    
    
    //----------------------------------------------------------------------- ACTIVE = TRUE
    
    //Right-eye
    if((distanceRightEye < 20) && (rightEyeActive == true) && (doenRechts == true)){
        rightEyeActive = false;
        cout << "rightEyeActive = false" << endl;
    }
    //Left-eye
    if((distanceLeftEye < 20) && (leftEyeActive == true) && (doenLinks == true)){
        leftEyeActive = false;
        cout << "leftEyeActive = false" << endl;
    }
    //Nose-Base
    if((distanceNoseBase < 20) && (noseBaseActive == true) && (doenNeus == true)){
        noseBaseActive = false;
        cout << "noseBaseActive = false" << endl;
    }
    //Inner-Mouth
    if((distanceInnerMouth < 20) && (innerMouthActive == true) && (doenMond == true)){
        innerMouthActive = false;
        cout << "innerMouthActive = false" << endl;
    }
    //Jaw-Left
    if((distanceJawLeft < 20) && (jawLeftActive == true) && (doenKaakLinks == true)){
        jawLeftActive = false;
        cout << "jawLeftActive = false" << endl;
    }
    
    // ----------------------------------------------------------------TEKENEN OF NIET?
    //tekenen starten?
    if(leftEyeActive == true){
        if(distanceLeftEye < 20){
            tekenLeftEye = true;
        }
    }
    if(rightEyeActive == true){
        if(distanceRightEye < 20){
            tekenRightEye = true;
            cout << "tekenRIGHT " << tekenRightEye << endl;
        }
    }
    if(noseBaseActive == true){
        if(distanceNoseBase < 20){
            tekenNoseBase = true;
            cout << "tekenNose " << tekenNoseBase << endl;
        }
    }
    if(innerMouthActive == true){
        if(distanceInnerMouth < 20){
            tekenInnerMouth = true;
            cout << "tekenInnerMouth " << tekenInnerMouth << endl;
        }
    }
    if(jawLeftActive == true){
        if(distanceJawLeft < 20){
            tekenJawLeft = true;
            cout << "tekenjawLeft " << tekenJawLeft << endl;
        }
    }
}

//------------------------------------------------------------------------------------ MOUSE RELEASED
void testApp::mouseReleased(int x, int y, int button){
    if(tekenLeftEye == true){
        tekenLeftEye = false;
        leftEyeActive = false;
        doenLinks = false;
    }
    if(tekenRightEye == true){
        tekenRightEye = false;
        rightEyeActive = false;
        doenRechts = false;
    }
    if(tekenInnerMouth == true){
        tekenInnerMouth = false;
        innerMouthActive = false;
        doenMond = false;
    }
    if(tekenNoseBase == true){
        tekenNoseBase = false;
        noseBaseActive = false;
        doenNeus = false;
    }
    if(tekenJawLeft == true){
        tekenJawLeft = false;
        jawLeftActive = false;
        doenKaakLinks = false;
    }
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
    if (artmode == true)
    {
        for (int i = 0; i < drawnPoints.size(); i++){
            ofPoint mouse;
            mouse.set(x,y);
            float dist = (mouse - drawnPoints[i]).length();
            if (dist < 30){
                lineTemp;
                lineTemp.a = mouse;
                lineTemp.b = drawnPoints[i];
                lines.push_back(lineTemp);
            }
        }
        
        drawnPoints.push_back(ofPoint(x,y));
    }
}
