#pragma once

#include "ofMain.h"
#include "ofxFaceTracker.h"
#include "formClass.h"

// ARTMODE
class line {
public:
    ofPoint a;
    ofPoint b;
};

class testApp : public ofBaseApp {
    
public:
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    
    void mouseDragged(int x, int y, int button);
    
    ofVideoGrabber cam;
    ofxFaceTracker tracker;
    ExpressionClassifier classifier;
    
    //----------------------------------------------values to store positions of face
    int leftEyeX;
    int prevLeftEyeX;
    int diffLeftEyeX;
    int leftEyeY;
    int prevLeftEyeY;
    int diffLeftEyeY;
    bool tekenLeftEye;
    
    int rightEyeX;
    int prevRightEyeX;
    int diffRightEyeX;
    int rightEyeY;
    int prevRightEyeY;
    int diffRightEyeY;
    bool tekenRightEye;
    
    int jawLeftX;
    int prevJawLeftX;
    int diffJawLeftX;
    int jawLeftY;
    int prevJawLeftY;
    int diffJawLeftY;
    bool tekenJawLeft;
    
    int innerMouthX;
    int prevInnerMouthX;
    int diffInnerMouthX;
    int innerMouthY;
    int prevInnerMouthY;
    int diffInnerMouthY;
    bool tekenInnerMouth;
    
    int noseBaseX;
    int prevNoseBaseX;
    int diffNoseBaseX;
    int noseBaseY;
    int prevNoseBaseY;
    int diffNoseBaseY;
    bool tekenNoseBase;
    
    
    
    int jawRightX;
    int jawRightY;
    
    //----------------------------------------------colors
    // rgb active circle
    int rActive = 51;
    int gActive = 150;
    int bActive = 255;
    
    //----------------------------------------------boolean values to determine in which state we are
    bool leftEyeActive = false;
    bool rightEyeActive = false;
    bool jawLeftActive = false;
    bool jawRightActive = false;
    bool noseBaseActive = false;
    bool innerMouthActive = false;
    
    bool doenLinks = false;
    bool doenRechts = false;
    bool doenKaakLinks = false;
    bool doenKaakRechts = false;
    bool doenNeus = false;
    bool doenMond = false;
    
    bool artmode = false;
    
    bool Uitbeeld;
    unsigned long long FailedTime;
    int opacity;
    
    //mousPOS
    int ox = 0;
    
    //formClass image;
    //formClass *myCircle;
    
    //DRAWING
    //int laatsteptX;
    //int laatsteptY;
    
    //lines voor tekentool
    ofPolyline lineLeft;
    ofPolyline lineRight;
    ofPolyline lineMouth;
    ofPolyline lineNose;
    ofPolyline lineJawLeft;
    
    ofTrueTypeFont myFont;
    
    // ---------------------------------------ARTMODE
    vector < ofPoint > drawnPoints;
    vector < line > lines;
    line lineTemp;
};
