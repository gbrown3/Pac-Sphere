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
using namespace pacsphere;

App::App(int argc, char** argv) : VRApp(argc, argv)
{
    _curFrameTime = 0.0;
    
    dir = vec3(0.0);
    mazeFrame = mat4(1.0);

    pacFrame = translate(mat4(1), vec3(0, 0, MAZE_RADIUS + PAC_RADIUS));
    
    inkyFrame = rotate(mat4(1.0), radians(90.0f), vec3(1, 0, 0));
    pinkyFrame = rotate(mat4(1.0), radians(180.0f), vec3(1, 0, 0));
    blinkyFrame = rotate(mat4(1.0), radians(45.0f), vec3(1, 0, 0));
    clydeFrame = rotate(mat4(1.0), radians(-90.0f), vec3(1, 0, 0));

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
		_curFrameTime = event.getValue();
	}


}

void App::onButtonDown(const VRButtonEvent &event) {
    // This routine is called for all Button_Down events.  Check event->getName()
    // to see exactly which button has been pressed down.

    string name = event.getName();
    
    if (name == "KbdUp_Down") {
        
        // Update maze rotation direction
        dir = vec3(0,-MOVEMENT_SPEED,0);
        
        // Orient pacman
        pacFrame = translate(mat4(1), vec3(0, 0, MAZE_RADIUS + PAC_RADIUS));
    }
    else if (name == "KbdDown_Down") {
        
        // Update maze rotation direction
        dir = vec3(0,MOVEMENT_SPEED,0);
        
        // Orient pacman
        mat4 startingTransform = translate(mat4(1), vec3(0, 0, MAZE_RADIUS + PAC_RADIUS));
        mat4 rotation = rotate(mat4(1), radians(180.0f), vec3(0, 0, 1));
        
        pacFrame = startingTransform * rotation;
    }
    else if (name == "KbdLeft_Down") {
        
        // Update maze rotation direction
        dir = vec3(MOVEMENT_SPEED,0,0);
        dirXFlipped = false;
        
        // Orient pacman
        mat4 startingTransform = translate(mat4(1), vec3(0, 0, MAZE_RADIUS + PAC_RADIUS));
        mat4 rotation = rotate(mat4(1), radians(90.0f), vec3(0, 0, 1));
        
        pacFrame = startingTransform * rotation;
    }
    else if (name == "KbdRight_Down") {
        
        // Update maze rotation direction
        dir = vec3(-MOVEMENT_SPEED,0,0);
        dirXFlipped = false;
        
        // Orient pacman
        mat4 startingTransform = translate(mat4(1), vec3(0, 0, MAZE_RADIUS + PAC_RADIUS));
        mat4 rotation = rotate(mat4(1), radians(-90.0f), vec3(0, 0, 1));
        
        pacFrame = startingTransform * rotation; //startingTransform * rotation; //startingTransform * rotation;
    }
    
    // Reset maze rotation
    else if (name == "KbdSpace_Down") {
        dir = vec3(0,0,0);
        mazeFrame = mat4(1.0);
        pacFrame = translate(mat4(1), vec3(0, 0, MAZE_RADIUS + PAC_RADIUS));
    }
    
    // Enable zooming in and out
    else if (name == "KbdEqual_Down") {
        
        cameraOffset += vec3(0, 0, -ZOOM_INCREMENT);
    }
    else if (name == "KbdMinus_Down") {
        
        cameraOffset += vec3(0, 0, ZOOM_INCREMENT);
    }
    
    // Enable/Disable joint animation
    else if (name == "KbdJ_Down") {
        
        useJointAnimations = !useJointAnimations;
    }
    
    // Switch between maze sphere and test sphere
    else if (name == "KbdM_Down") {
        
        renderTestSphere = false;
    }
    else if (name == "KbdT_Down") {
        
        renderTestSphere = true;
    }

    // Toggle rendering cylinder that indicates which direction pacman is facing
    else if (name == "KbdC_Down") {
        renderTestCylinder = !renderTestCylinder;
    }

    // Enable/disable maze walls
    else if (name == "KbdW_Down") {
        
        renderMazeWalls = !renderMazeWalls;
    }

    
    cout << "Button presed: " << name << endl << endl;
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
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LESS);
		glDepthRange(0.0f, 0.2f);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		glEnable(GL_MULTISAMPLE);

		// This sets the background color that is used to clear the canvas
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

		// This load shaders from disk, we do it once when the program starts up.
		reloadShaders();

        // Setup maze
        maze.reset(new pacsphere::Sphere(vec3(0), MAZE_RADIUS, vec4(1, 0, 0, 1), MAZE_TEXTURE_PATH));

        test_sphere.reset(new basicgraphics::Sphere(vec3(0), MAZE_RADIUS, vec4(1, 1, 1, 1)));
        test_cylinder.reset(new basicgraphics::Cylinder(vec3(0), vec3(0, 10, 0), 1.0f, vec4(0, 1, 0, 1)));
        
        
        
        // Set up Pacman
        pacman.reset(new pacsphere::Pacman(vec3(0, 0, 0)));
        

        
        // Setup the ghosts
        inky.reset(new pacsphere::Ghost(vec3(0, 0, MAZE_RADIUS + PAC_RADIUS), pacsphere::INKY));
        pinky.reset(new pacsphere::Ghost(vec3(0, 0, MAZE_RADIUS + PAC_RADIUS), pacsphere::PINKY));
        blinky.reset(new pacsphere::Ghost(vec3(0, 0, MAZE_RADIUS + PAC_RADIUS), pacsphere::BLINKY));
        clyde.reset(new pacsphere::Ghost(vec3(0, 0, MAZE_RADIUS + PAC_RADIUS), pacsphere::CLYDE));
    }

    // Rotate maze
    vec3 rotationAxis = cross(dir, vec3(0, 0, 1));
    float rotationAngle = radians(-MOVEMENT_SPEED);
    mat4 rotation;

    if (rotationAxis != vec3(0, 0, 0)) {
        if (abs(dir.x) > 0) {
            if (dir.x > 0) {
                rotationAxis = -mazeY;
            }
            else {
                rotationAxis = mazeY;
            }
        }
        
        if (mazeY.y < 0 && !dirXFlipped && dir.x != 0) {
            dir.x = -dir.x;
            dirXFlipped = true;
        }

        rotation = rotate(mat4(1.0), rotationAngle * dir.length(), rotationAxis);

        // If pacman is not colliding then keep rotating the sphere
        if (!pacmanColliding(rotation * mazeFrame)) {
            mazeFrame = rotation * mazeFrame;
            mazeY = vec3(rotation * vec4(mazeY, 0));
        }
    }


    // Animate pacman
    pacman->animate(_curFrameTime * 1000);
}

/**
 * Given the current rotation of the maze, returns true if pacman is in contact with one of the walls
 */
bool App::pacmanColliding(mat4 rotation) {
    // Because collision is not working properly yet, we always return false to avoid problems in the program
//    return false;

    // This is our attempt to calculate collision

    // Get the position where pacman will be in the next frame
	vec4 pos = rotation * vec4(0, 0, MAZE_RADIUS, 1.0);

	// Get the texture coordinate at that position
	vec2 texCoord = maze->getTexturePosition(pos);

    int width = maze->imageWidth;
    int height = maze->imageHeight;

    // Number of channels in one pixel. (r,g,b) == 3. (r,g,b,a) == 4
    int numChannels = maze->imageChannels;

    // Convert texture coords from 0-1 to row and column
    float column = texCoord.x * width;
    float row = texCoord.y * height;

    // Row-major order
    int index = numChannels * ((width * row) + column);
    // Column-major version below
    //int index = (numChannels * height * column) + (numChannels * row);

    int R = (int) maze->_image[index];
    int G = (int) maze->_image[index + 1];
    int B = (int) maze->_image[index + 2];

    // If the color of the pixel is black then pacman is colliding
	return R == 0 && G == 0 && B == 0;
};

void App::onRenderGraphicsScene(const VRGraphicsState &renderState) {
    // This routine is called once per eye/camera.  This is the place to actually
    // draw the scene.

	// clear the canvas and other buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Setup the view matrix to set where the camera is located in the scene
    vec3 mazeCenter = vec3(column(mazeFrame, 3));
    glm::vec3 eye_world = mazeCenter + cameraOffset;
    glm::mat4 view = glm::lookAt(eye_world, mazeCenter, glm::vec3(0,1,0));

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
	_shader.setUniform("eye_world", eye_world);
    
    _shader.setUniform("model_mat", mazeFrame);
    _shader.setUniform("normal_mat", mat3(transpose(inverse(mazeFrame))));
    
    
    // Draw cylinder indicating which direction pacman is facing
    if (renderTestCylinder) {
        test_cylinder->draw(_shader, pacFrame * translate(mat4(1), vec3(0, PAC_RADIUS, 0)));
    }

    // Draw maze sphere (or test sphere)
    if (renderTestSphere) {
        test_sphere->draw(_shader, mazeFrame);
    }
    else {
        maze->draw(_shader, mazeFrame);
    }

	_mazeShader.use();
	_mazeShader.setUniform("mazeHeight", 2.0f);
	_mazeShader.setUniform("view_mat", view);
	_mazeShader.setUniform("projection_mat", projection);
	_mazeShader.setUniform("model_mat", model);

    // Draw 3D maze walls
    if (renderMazeWalls) {
        
        maze->draw(_mazeShader, mazeFrame);
    }
    
    
    // Draw pacman
    _pacShader.use();
    
    _pacShader.setUniform("view_mat", view);
    _pacShader.setUniform("projection_mat", projection);
    
    _pacShader.setUniform("model_mat", model);
    _pacShader.setUniform("normal_mat", mat3(transpose(inverse(pacFrame))));
    _pacShader.setUniform("eye_world", eye_world);
    
    vector<shared_ptr<Joint>> joints = pacman->_mesh->getJoints();
    _pacShader.setUniform("centerJointRotation", joints[0]->_rotation);
    _pacShader.setUniform("rightJointRotation", joints[1]->_rotation);
    _pacShader.setUniform("leftJointRotation", joints[2]->_rotation);
    
    _pacShader.setUniform("useJoints", useJointAnimations);
    
    pacman->draw(_pacShader, pacFrame);
    _shader.use();
    pacman->_mesh->drawJoints(_shader, pacFrame);
    
    // Draw ghosts
    _ghostShader.use();
    _ghostShader.setUniform("view_mat", view);
    _ghostShader.setUniform("projection_mat", projection);
    _ghostShader.setUniform("eye_world", eye_world);
    
    _ghostShader.setUniform("model_mat", inkyFrame);
    _ghostShader.setUniform("normal_mat", mat3(transpose(inverse(inkyFrame))));
    inky->draw(_ghostShader, mazeFrame * inkyFrame);
    
    _ghostShader.setUniform("model_mat", pinkyFrame);
    _ghostShader.setUniform("normal_mat", mat3(transpose(inverse(pinkyFrame))));
    pinky->draw(_ghostShader, mazeFrame * pinkyFrame);
    
    _ghostShader.setUniform("model_mat", blinkyFrame);
    _ghostShader.setUniform("normal_mat", mat3(transpose(inverse(blinkyFrame))));
    blinky->draw(_ghostShader, mazeFrame * blinkyFrame);
    
    _ghostShader.setUniform("model_mat", clydeFrame);
    _ghostShader.setUniform("normal_mat", mat3(transpose(inverse(clydeFrame))));
    clyde->draw(_ghostShader, mazeFrame * clydeFrame);
}

void App::reloadShaders()
{
	_shader.compileShader("texture.vert", GLSLShader::VERTEX);
	_shader.compileShader("texture.frag", GLSLShader::FRAGMENT);
	_shader.link();
    
    _pacShader.compileShader("shaders/pacman.vert", GLSLShader::VERTEX);
    _pacShader.compileShader("shaders/pacman.frag", GLSLShader::FRAGMENT);
    _pacShader.link();

    _mazeShader.compileShader("shaders/maze.vert", GLSLShader::VERTEX);
    _mazeShader.compileShader("shaders/maze.geom", GLSLShader::GEOMETRY);
    _mazeShader.compileShader("shaders/maze.frag", GLSLShader::FRAGMENT);
    _mazeShader.link();

    _ghostShader.compileShader("texture.vert", GLSLShader::VERTEX);
    _ghostShader.compileShader("shaders/ghost.frag", GLSLShader::FRAGMENT);
    _ghostShader.link();
}
