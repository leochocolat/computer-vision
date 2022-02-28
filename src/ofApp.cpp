#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    clearColor.r = 0;
    clearColor.g = 0;
    clearColor.b = 0;
    clearColor.a = clearAlpha;

    camera.setup(640, 480);

    color.allocate(camera.getWidth(), camera.getHeight());
    gray.allocate(camera.getWidth(), camera.getHeight());
    background.allocate(camera.getWidth(), camera.getHeight());
    difference.allocate(camera.getWidth(), camera.getHeight());

    haar.setup("haarcascade_frontalface_default.xml");
    haar.setScaleHaar(2);

    fbo.allocate(ofGetWidth(), ofGetHeight());
    fbo.begin();
    // ofClear();
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::update()
{
    camera.update();

    if (camera.isFrameNew())
    {
        // updateHaar();
        updateContours();
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    clearFbo();

    fbo.draw(0, 0);

    fbo.begin();
    contour.draw(0, 0);
    fbo.end();

    // color.draw(0, 0);

    // drawHaar();

    // contour.draw(0, 0);
    // difference.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch (key)
    {
    case OF_KEY_UP:
        threshold++;
        clearAlpha++;
        break;
    case OF_KEY_DOWN:
        threshold--;
        clearAlpha--;
        break;

    default:
        break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}

void ofApp::updateContours()
{
    color.setFromPixels(camera.getPixels());
    gray = color;

    if (learn)
    {
        background = gray;
        learn = false;
    }

    difference.absDiff(background, gray);
    difference.threshold(threshold);

    contour.findContours(difference, 10, camera.getWidth() * camera.getHeight(), 10, false);
}

void ofApp::updateHaar()
{
    color.setFromPixels(camera.getPixels());
    gray = color;
    haar.findHaarObjects(gray);
}

void ofApp::drawHaar()
{
    for (int i = 0; i < haar.blobs.size(); i++)
    {
        ofSetColor(255);
        ofNoFill();
        ofDrawRectangle(haar.blobs[i].boundingRect);
    }
}

void ofApp::clearFbo()
{
    clearColor.a = clearAlpha;

    fbo.begin();
    ofSetColor(clearColor);
    ofDrawRectangle(0, 0, 0, ofGetWidth(), ofGetHeight());
    fbo.end();
}
