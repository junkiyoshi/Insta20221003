#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofEnableDepthTest();
	ofSetLineWidth(1.5);

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->face.clear();
	this->line.clear();

	float phi_deg_step = 5;
	float theta_deg_step = 5;
	float noise_radius = 300;

	for (float radius = 100; radius <= 250; radius += 5) {

		for (float phi_deg = 0; phi_deg < 360; phi_deg += phi_deg_step) {

			for (float theta_deg = 0; theta_deg <= 180; theta_deg += theta_deg_step) {

				auto noise_value = ofNoise(
					noise_radius * cos(phi_deg * DEG_TO_RAD) * 0.01,
					noise_radius * sin(phi_deg * DEG_TO_RAD) * 0.01,
					noise_radius * cos(theta_deg * DEG_TO_RAD) * 0.005,
					radius * 0.005 - ofGetFrameNum() * 0.05);

				if (noise_value < 0.55) { continue; }

				auto noise_value_1 = ofNoise(
					noise_radius * cos(phi_deg * DEG_TO_RAD) * 0.01,
					noise_radius * sin(phi_deg * DEG_TO_RAD) * 0.01,
					noise_radius * cos((theta_deg - theta_deg_step) * DEG_TO_RAD) * 0.005,
					radius * 0.005 - ofGetFrameNum() * 0.05);
				auto noise_value_2 = ofNoise(
					noise_radius * cos((phi_deg + phi_deg_step) * DEG_TO_RAD) * 0.01,
					noise_radius * sin((phi_deg + phi_deg_step) * DEG_TO_RAD) * 0.01,
					noise_radius * cos(theta_deg * DEG_TO_RAD) * 0.005,
					radius * 0.005 - ofGetFrameNum() * 0.05);
				auto noise_value_3 = ofNoise(
					noise_radius * cos((phi_deg - phi_deg_step) * DEG_TO_RAD) * 0.01,
					noise_radius * sin((phi_deg - phi_deg_step) * DEG_TO_RAD) * 0.01,
					noise_radius * cos(theta_deg * DEG_TO_RAD) * 0.005,
					radius * 0.005 - ofGetFrameNum() * 0.05);
				auto noise_value_4 = ofNoise(
					noise_radius * cos(phi_deg * DEG_TO_RAD) * 0.01,
					noise_radius * sin(phi_deg * DEG_TO_RAD) * 0.01,
					noise_radius * cos((theta_deg + theta_deg_step) * DEG_TO_RAD) * 0.005,
					radius * 0.005 - ofGetFrameNum() * 0.05);

				auto index = this->face.getNumVertices();
				vector<glm::vec3> vertices;

				vertices.push_back(glm::vec3(
					radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * cos((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD)));
				vertices.push_back(glm::vec3(
					radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * cos((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD)));
				vertices.push_back(glm::vec3(
					radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * cos((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD)));
				vertices.push_back(glm::vec3(
					radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * cos((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD)));

				this->face.addVertices(vertices);

				this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 3);
				this->face.addIndex(index + 0); this->face.addIndex(index + 3); this->face.addIndex(index + 2);

				ofColor color = ofColor(ofMap(radius, 100, 250, 255, 0));
				this->face.addColor(color);
				this->face.addColor(color);
				this->face.addColor(color);
				this->face.addColor(color);

				color = ofColor(ofMap(radius, 100, 250, 0, 255));

				if (noise_value_1 < 0.55) {

					this->line.addVertex(vertices[0]); this->line.addVertex(vertices[1]);
					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);

					this->line.addColor(color); this->line.addColor(color);
				}

				if (noise_value_2 < 0.55) {

					this->line.addVertex(vertices[0]); this->line.addVertex(vertices[2]);
					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);

					this->line.addColor(color); this->line.addColor(color);
				}

				if (noise_value_3 < 0.55) {

					this->line.addVertex(vertices[1]); this->line.addVertex(vertices[3]);
					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);

					this->line.addColor(color); this->line.addColor(color);
				}

				if (noise_value_4 < 0.55) {

					this->line.addVertex(vertices[2]); this->line.addVertex(vertices[3]);
					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);

					this->line.addColor(color); this->line.addColor(color);
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(270);
	ofRotateZ(ofGetFrameNum() * 0.66666666666666);

	this->face.draw();
	this->line.draw();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}