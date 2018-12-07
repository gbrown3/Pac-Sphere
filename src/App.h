#ifndef APP_H
#define APP_H

#include <api/MinVR.h>
using namespace MinVR;

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#ifdef _WIN32
#include "GL/glew.h"
#include "GL/wglew.h"
#elif (!defined(__APPLE__))
#include "GL/glxew.h"
#endif

// OpenGL Headers
#if defined(WIN32)
#define NOMINMAX
#include <windows.h>
#include <GL/gl.h>
#elif defined(__APPLE__)
#define GL_GLEXT_PROTOTYPES
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#else
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#endif

#include <BasicGraphics.h>
#include "Pacman.h"
#include "Sphere.h"
#include "Ghost.h"
#include "Joint.h"
#include "Config.h"


class App : public VRApp {
public:
    
    /** The constructor passes argc, argv, and a MinVR config file on to VRApp.
     */
	App(int argc, char** argv);
    virtual ~App();
    
    
    static constexpr float MOVEMENT_SPEED = 0.3;

    
    /** USER INTERFACE CALLBACKS **/
    virtual void onAnalogChange(const VRAnalogEvent &state);
    virtual void onButtonDown(const VRButtonEvent &state);
    virtual void onButtonUp(const VRButtonEvent &state);
	virtual void onCursorMove(const VRCursorEvent &state);
    virtual void onTrackerMove(const VRTrackerEvent &state);
    
    
    /** RENDERING CALLBACKS **/
    virtual void onRenderGraphicsScene(const VRGraphicsState& state);
    virtual void onRenderGraphicsContext(const VRGraphicsState& state);
    
private:
    
    static constexpr float MAZE_RADIUS = 20;
	static constexpr float PAC_RADIUS = 1.0f;
    static constexpr float ZOOM_INCREMENT = 2.0f;

	double _lastTime;
	double _curFrameTime;
    
    std::unique_ptr<pacsphere::Sphere> maze;
    std::unique_ptr<pacsphere::Pacman> pacman;
    
    std::unique_ptr<pacsphere::Ghost> inky;
    std::unique_ptr<pacsphere::Ghost> pinky;
    std::unique_ptr<pacsphere::Ghost> blinky;
    std::unique_ptr<pacsphere::Ghost> clyde;
    
    std::unique_ptr<basicgraphics::Sphere> test_sphere;
    
    glm::vec3 cameraOffset = glm::vec3(0, 0, 60);  // direction to move camera from center of maze
    
    glm::vec3 dir;
    glm::mat4 mazeFrame;
    glm::mat4 pacFrame;
    
    vec3 mazeY;
    bool dirXFlipped;
    
    bool useJointAnimations = false;
    
    virtual void reloadShaders();
    basicgraphics::GLSLProgram _shader;
    basicgraphics::GLSLProgram _pacShader;
    basicgraphics::GLSLProgram _mazeShader;
    basicgraphics::GLSLProgram _ghostShader;

	void initializeText();
	void drawText(const std::string text, float xPos, float yPos, GLfloat windowHeight, GLfloat windowWidth);
	struct FONScontext* fs;
    basicgraphics::GLSLProgram _textShader;
};


#endif //APP_H
