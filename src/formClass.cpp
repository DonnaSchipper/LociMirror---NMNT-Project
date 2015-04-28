//
//  formClass.cpp
//  ofApp
//
//  Created by Donna Schipper on 15/04/15.
//
//

#include "formClass.h"
//#invluce "ofxCv"

formClass::formClass(float _xpos, float _ypos){
    xpos = _xpos;
    ypos = _ypos;
}


void formClass::setup() {
    }

void formClass::update() {
    
}

void formClass::draw() {
    
    //ofSetColor(51,150,255);
    //ofEllipse(xpos,ypos,30,30);
    
    ofSetColor(255,255,255);
    ofRect(xpos, ypos, 70,100);
}