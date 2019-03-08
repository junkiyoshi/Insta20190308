#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofNoFill();
	ofSetLineWidth(1.5);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(150, 2);
	this->triangles = ico_sphere.getMesh().getUniqueFaces();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum());

	vector<glm::vec3> noise_locations;
	for (int i = 0; i < 3; i++) {

		noise_locations.push_back(glm::vec3(ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.01), 0, 1, -500, 500), ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.01), 0, 1, -500, 500), ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.01), 0, 1, -200, 200)));
	}

	for (int x = -400; x <= 400; x += 400) {

		for (int y = -400; y <= 400; y += 400) {

			for(auto& triangle : this->triangles){

				auto avg_location = glm::vec3();
				vector<glm::vec3> vertices;
				for (int j = 0; j < 3; j++) {

					glm::vec3 location(x + triangle.getVertex(j).x, y + triangle.getVertex(j).y, triangle.getVertex(j).z);
					vertices.push_back(location);

					avg_location += location;
				}
				avg_location /= 3;

				bool draw_flag = true;
				for (auto& noise_location : noise_locations) {
				
					float distance = glm::distance(noise_location, avg_location);
					if (distance < 200) {

						draw_flag = false;
						break;
					}
				}

				if (draw_flag) {

					ofFill();
					ofSetColor(39);

					ofBeginShape();
					ofVertices(vertices);
					ofEndShape(true);

					ofNoFill();
					ofSetColor(239);

					ofBeginShape();
					ofVertices(vertices);
					ofEndShape(true);
				}
			}
		}
	}

	ofSetColor(39);
	for (auto& noise_location : noise_locations) {
	
		ofDrawSphere(noise_location, 10);
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}