#include "ofApp.h"

// Based in asciiVideoExample
//--------------------------------------------------------------
void ofApp::setup() {

	ofBackground(0, 0, 0);

	camWidth = 1280;
	camHeight = 720;

	vidGrabber.setVerbose(true);
	vidGrabber.setup(camWidth, camHeight);

	// https://www.dafont.com/meeksa.font
	font.load("meeksa.ttf", ofRandom(10, 30));

	asciiCharacters = string("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

	ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::update() {
	vidGrabber.update();
}

//--------------------------------------------------------------
void ofApp::draw() {

	// change background video alpha value based on the cursor's x-position
	float videoAlphaValue = ofMap(mouseX, 0, ofGetWidth(), 0, 255);

	// set a white fill color with the alpha generated above
	ofSetColor(255, 255, 255, videoAlphaValue);

	// draw the raw video frame with the alpha value generated above
	vidGrabber.draw(0, 0);

	ofPixelsRef pixelsRef = vidGrabber.getPixels();

	std::vector<ofColor> colorPalette;

	for (int i = 0; i < 10; ++i) {
		ofColor color;
		color.r = ofRandom(155, 255);
		color.g = 0;
		color.b = 0;
		colorPalette.push_back(color);
	}

	for (int i = 0; i < camWidth; i += ofRandom(5, 15)) {

		for (int j = 0; j < camHeight; j += ofRandom(10, 25)) {
			// get the pixel and its lightness (lightness is the average of its RGB values)
			float lightness = pixelsRef.getColor(i, j).getLightness();

			// calculate the index of the character from our asciiCharacters array
			int character = powf(ofMap(lightness, 0, 255, 0, 1), 2.5) * asciiCharacters.size();

			// get a color from the palette based on the character index
			ofColor characterColor = colorPalette[character % colorPalette.size()];

			// set the color before drawing the character
			ofSetHexColor(characterColor.getHex());

			// draw the character at the correct location
			font.drawString(ofToString(asciiCharacters[character]), i, j);
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 's' || key == 'S') {
		vidGrabber.videoSettings();
	}

	// Change camera
	else if (key == '1')
	{
		vidGrabber.setDeviceID(0);
		vidGrabber.initGrabber(camWidth, camHeight);
	}
	else if (key == '2')
	{
		vidGrabber.setDeviceID(1);
		vidGrabber.initGrabber(camWidth, camHeight);
	}
}
