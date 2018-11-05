#include "App.h"

#define FONTSTASH_IMPLEMENTATION
#include <fontstash.h>
#define GLFONTSTASH_IMPLEMENTATION
#include <glfontstash.h>

#include <config/VRDataIndex.h>

#include <glm/gtx/orthonormalize.hpp>

#include "glm/ext.hpp"

using namespace basicgraphics;
using namespace std;
using namespace glm;

App::App(int argc, char** argv) : VRApp(argc, argv)
{
	_lastTime = 0.0;
    _curFrameTime = 0.0;
    
    dir = vec3(0.0);
    sphereFrame = mat4(1.0);
    
    mazeY = vec3(0, 1, 0);
    dirXFlipped = false;
}

App::~App()
{
	glfonsDelete(fs);
	shutdown();
}

void App::onAnalogChange(const VRAnalogEvent &event) {
    // This routine is called for all Analog_Change events.  Check event->getName()
    // to see exactly which analog input has been changed, and then access the
    // new value with event->getValue().
    
	if (event.getName() == "FrameStart") {
		_lastTime = _curFrameTime;
		_curFrameTime = event.getValue();
	}


}

void App::onButtonDown(const VRButtonEvent &event) {
    // This routine is called for all Button_Down events.  Check event->getName()
    // to see exactly which button has been pressed down.
	
	std::cout << "ButtonDown: " << event.getName() << std::endl;
    
    string name = event.getName();
    
    if (name == "KbdUp_Down") {
        dir = vec3(0,-MOVEMENT_SPEED,0);
    }
    else if (name == "KbdDown_Down") {
        dir = vec3(0,MOVEMENT_SPEED,0);
    }
    else if (name == "KbdLeft_Down") {
        dir = vec3(MOVEMENT_SPEED,0,0);
        dirXFlipped = false;
    }
    else if (name == "KbdRight_Down") {
        dir = vec3(-MOVEMENT_SPEED,0,0);
        dirXFlipped = false;
    }
    
    // If the ball rolls off the screen, you can press SPACEBAR to reset its position
    else if (name == "KbdSpace_Down") {
        dir = vec3(0,0,0);
        sphereFrame = mat4(1.0);
    }


}

void App::onButtonUp(const VRButtonEvent &event) {
    // This routine is called for all Button_Up events.  Check event->getName()
    // to see exactly which button has been released.

	//std::cout << "ButtonUp: " << event.getName() << std::endl;
}

void App::onCursorMove(const VRCursorEvent &event) {
	// This routine is called for all mouse move events. You can get the absolute position
	// or the relative position within the window scaled 0--1.
	
	//std::cout << "MouseMove: "<< event.getName() << " " << event.getPos()[0] << " " << event.getPos()[1] << std::endl;
}

void App::onTrackerMove(const VRTrackerEvent &event) {
    // This routine is called for all Tracker_Move events.  Check event->getName()
    // to see exactly which tracker has moved, and then access the tracker's new
    // 4x4 transformation matrix with event->getTransform().

	// We will use trackers when we do a virtual reality assignment. For now, you can ignore this input type.
}

void App::onRenderGraphicsContext(const VRGraphicsState &renderState) {
    // This routine is called once per graphics context at the start of the
    // rendering process.  So, this is the place to initialize textures,
    // load models, or do other operations that you only want to do once per
    // frame.
    
	// Is this the first frame that we are rendering after starting the app?
    if (renderState.isInitialRenderCall()) {

		//For windows, we need to initialize a few more things for it to recognize all of the
		// opengl calls.
		#ifndef __APPLE__
			glewExperimental = GL_TRUE;
			GLenum err = glewInit();
			if (GLEW_OK != err)
			{
				std::cout << "Error initializing GLEW." << std::endl;
			}
		#endif     


        glEnable(GL_DEPTH_TEST);
        glClearDepth(1.0f);
        glDepthFunc(GL_LEQUAL);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		glEnable(GL_MULTISAMPLE);

		// This sets the background color that is used to clear the canvas
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

		// This load shaders from disk, we do it once when the program starts up.
		reloadShaders();

		initializeText();
		shared_ptr<Texture> tex2 = Texture::create2DTextureFromFile(MAZE_TEXTURE_PATH);
		maze.reset(new pacsphere::Sphere(vec3(0), MAZE_RADIUS, vec4(1, 0, 0, 1), tex2));
        
        pacman.reset(new pacsphere::Sphere(vec3(0, 0, MAZE_RADIUS + PAC_RADIUS), PAC_RADIUS, vec4(1,1,0,1)));
        
        pinky.reset(new pacsphere::Ghost(vec3(0, 0, MAZE_RADIUS + PAC_RADIUS), pacsphere::PINKY));
    }
    
    vec3 rotationAxis = cross(dir, vec3(0, 0, 1));
    
    if (rotationAxis != vec3(0, 0, 0)) {
        
        float rotationAngle = radians(-0.25f);
        
        if (abs(dir.x) > 0) {
            if (dir.x > 0) {
                rotationAxis = -mazeY;
                //rotationAngle = -rotationAngle;
            }
            else {
                rotationAxis = mazeY;
                //rotationAngle = -rotationAngle;
            }
        }
        
        if (mazeY.y < 0 && !dirXFlipped && dir.x != 0) {
            dir.x = -dir.x;
            dirXFlipped = true;
        }
        
        mat4 rotation = rotate(mat4(1.0), rotationAngle * dir.length(), rotationAxis);
        sphereFrame = rotation * sphereFrame;
        mazeY = vec3(rotation * vec4(mazeY, 0));
        
    }
    
}

void App::onRenderGraphicsScene(const VRGraphicsState &renderState) {
    // This routine is called once per eye/camera.  This is the place to actually
    // draw the scene.
    
	// clear the canvas and other buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Setup the view matrix to set where the camera is located in the scene
    vec3 ballPos = vec3(column(sphereFrame, 3));
    glm::vec3 eye_world = ballPos + glm::vec3(0,0,60);
    glm::mat4 view = glm::lookAt(eye_world, ballPos, glm::vec3(0,1,0));

	// Setup the projection matrix so that things are rendered in perspective
	GLfloat windowHeight = renderState.index().getValue("FramebufferHeight");
	GLfloat windowWidth = renderState.index().getValue("FramebufferWidth");
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), windowWidth / windowHeight, 0.01f, 100.0f);
	
	// Setup the model matrix
	glm::mat4 model = glm::mat4(1.0);
    
	// Tell opengl we want to use this specific shader.
	_shader.use();
	
	_shader.setUniform("view_mat", view);
	_shader.setUniform("projection_mat", projection);
	
	_shader.setUniform("model_mat", model);
	_shader.setUniform("normal_mat", mat3(transpose(inverse(model))));
	_shader.setUniform("eye_world", eye_world);
    
    _shader.setUniform("model_mat", sphereFrame);
    _shader.setUniform("normal_mat", mat3(transpose(inverse(sphereFrame))));
    
    maze->draw(_shader, sphereFrame);
    //pacman->draw(_shader, model); 
    pinky->draw(_shader, model);
}

void App::drawText(const std::string text, float xPos, float yPos, GLfloat windowHeight, GLfloat windowWidth) {
	//float lh = 0;
	//fonsVertMetrics(fs, NULL, NULL, &lh);
	//double width = fonsTextBounds(fs, text.c_str(), NULL, NULL) + 40;
	//double height = lh + 40;

	_textShader.use();
	_textShader.setUniform("projection_mat", glm::ortho(0.f, windowWidth, windowHeight, 0.f, -1.f, 1.f));
	_textShader.setUniform("view_mat", glm::mat4(1.0));
	_textShader.setUniform("model_mat", glm::mat4(1.0));
	_textShader.setUniform("lambertian_texture", 0);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	fonsDrawText(fs, xPos, yPos, text.c_str(), NULL);

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	_shader.use();

}

void App::reloadShaders()
{
	_shader.compileShader("texture.vert", GLSLShader::VERTEX);
	_shader.compileShader("texture.frag", GLSLShader::FRAGMENT);
	_shader.link();
	_shader.use();
}

void App::initializeText() {
	int fontNormal = FONS_INVALID;
	fs = nullptr;

	fs = glfonsCreate(512, 512, FONS_ZERO_TOPLEFT);
	if (fs == NULL) {
		assert(false);//Could not create stash
	}

	fontNormal = fonsAddFont(fs, "sans", "DroidSansMono.ttf");
	if (fontNormal == FONS_INVALID) {
		assert(false);// Could not add font normal.
	}

	unsigned int black = glfonsRGBA(0, 0, 0, 255);

	fonsClearState(fs);
	fonsSetSize(fs, 20);
	fonsSetFont(fs, fontNormal);
	fonsSetColor(fs, black);
	fonsSetAlign(fs, FONS_ALIGN_LEFT | FONS_ALIGN_TOP);

	_textShader.compileShader("textRendering.vert", GLSLShader::VERTEX);
	_textShader.compileShader("textRendering.frag", GLSLShader::FRAGMENT);
	_textShader.link();
}
