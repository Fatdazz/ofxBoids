#include "ofMain.h"
#include "ofApp.h"
#include "parametersGUI.h"
#include "ofAppGLFWWindow.h"
//========================================================================
int main( ){
    //ofSetupOpenGL(600,600,OF_WINDOW);			// <-------- setup the GL context
    
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    
    //ofRunApp(new ofApp());
    
    
    
    //	Windows	////////////////////////////////////////////////////////////////////////////
    ofGLFWWindowSettings settings;
    int topMargin = 30;
    int leftMargin = 10;
    
    //	Flocks windows	//
    settings.width = 1920;
    settings.height = 1080;
    settings.setPosition(ofVec2f(leftMargin*2 + 600, topMargin));
    settings.resizable = true;
    shared_ptr<ofAppBaseWindow> flocksWindow = ofCreateWindow(settings);
    
    //	Parameters window	//
    settings.width = 240;
    settings.height = 500;
    settings.setPosition(ofVec2f(leftMargin+300, topMargin));
    settings.resizable = true;
    shared_ptr<ofAppBaseWindow> parametersWindow = ofCreateWindow(settings);
    
    
    // Shared data	///////////////////////////////////////////////////////////////////////
    shared_ptr<ofApp> flocksApp(new ofApp);
    shared_ptr<ParametersGUI> flocksGroupsParametersGUI(new ParametersGUI);
    
    
    flocksApp->boids.parametersGui = flocksGroupsParametersGUI;
    
    
    //	Run	///////////////////////////////////////////////////////////////////////////////
    ofRunApp(parametersWindow, flocksGroupsParametersGUI);
    ofRunApp(flocksWindow, flocksApp);
    ofRunMainLoop();
    
    
}
