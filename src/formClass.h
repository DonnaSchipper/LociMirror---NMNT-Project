//
//  formClass.h
//  ofApp
//
//  Created by Donna Schipper on 15/04/15.
//
//

#ifndef __ofApp__formClass__
#define __ofApp__formClass__

#include "ofMain.h"
#include "ofxFaceTracker.h"

class formClass {
    
public:
    
    //methods
    void setup();
    void update();
    void draw();
    
    //constructor
    //formClass(float xpos, float ypos);
    formClass(float xpos, float ypos);
    
    //variables
    int xpos;
    int ypos;

};

#endif /* defined(__ofApp__formClass__) */

