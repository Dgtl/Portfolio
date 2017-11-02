// John Jervis
// CSC4400
// Assignment One
#pragma once

#define BUFFER_OFFSET(offset) ((void *)(offset))
#define GLUT_DISABLE_ATEXIT_HACK

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <random>

#include "glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "GL\glew.h"
#include "GL\freeglut.h"
//#include "GL\glut.h"

#include "AABB.h"

//FORWARD FUNCTION DECLARATIONS
GLuint loadShaderFromFile(std::string path, GLenum shaderType);
std::vector< glm::vec3 > loadModels(std::string);

//draw functions for project 4
void drawModels();
void drawHouse();
void drawCar();
void drawPlane();
void drawText();
void drawPlayerCar(); // for player control
void carMotion(int, int); //car and camera mouse control

void printVerts(std::vector<glm::vec3>);
GLuint initShaders();
GLuint initTextShaders();

//global state values
std::vector<GLuint> VAOs{ 0, 1, 2, 3 }; //Holds vertex array names
std::vector<GLuint> VBOs{ 0, 1, 2, 3 }; //Hold vertex buffer names
GLuint NumVertices = 0; //how many total vertices to be rendered

GLdouble dim = 7.0;
GLint height = 900;
GLint width = 1600;

GLfloat yaw = 0.0f; // azimuth view angle
GLfloat pitch = 0.0f; // elevation of view angle

GLint objID = 0;
GLint objSlice = 16;
GLint objStacks = 16;

//WIP
GLfloat sunZLocation = -300.0f;
GLfloat  lightPos[] = { 0.0f, 0.0f, -300.0f, 1.0f };
GLfloat  lightPos2[] = { 0.0f, 0.0f, 300.0f, 1.0f };
int sphereLatitudalSegments = 100;
int sphereLongitudalSegments = 100;

GLubyte r = 0;
GLubyte g = 0;
GLubyte b = 0;

GLboolean isRed = false;
GLboolean isGreen = false;
GLboolean isBlue = false;

GLfloat worldX = 0.0f;
GLfloat worldY = 0.0f;
GLfloat worldZ = 0.0f;

GLboolean isReverse = false;

//shader program
GLuint programID = 0;
GLuint textProgramID = 0;

//camera vectors
glm::mat4 cameraViewMat;

glm::vec3 cameraPos = glm::vec3(0.0f, 5.0f, -2.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

std::vector<glm::vec3> models; //to hold vertices from all models
std::vector<int> modelSizes;

GLfloat animCar = 0.0f; //for determining animation
GLfloat animPlane = 0.0f; //for determining animation
GLfloat animRotation = 0.0f; //for flipping models
GLfloat cameraSpeed = 0.3f;

GLint oldTime = 0; //delta time

/*TEST BOUNDING BOX*/
GLfloat moveBoundX = 0.0f;
GLfloat moveBoundZ = 0.0f;

//AABB car1;
//AABB car2;

//PRIME DIRECTIVE: All OpenGL does is render triangles into a unit cube. That's it. For everything else, get a library.

void init(void)
{
	//SETTINGS

	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);

	glClearDepth(1.0f);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	//glCullFace(GL_BACK);

	//glEnable(GL_CULL_FACE);

	glLineWidth(2.0f);

	//MATERIAL

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//textProgramID = initTextShaders(); //for text display
	programID = initShaders(); //program has been linked with shaders at this point, so I can define uniform variables

	//parse .obj files and store in vectors
	//std::vector<glm::vec3> model1 = loadModels("../res/test3.obj");
	//std::vector<glm::vec3> model2 = loadModels("../res/world.obj");

	std::vector<glm::vec3> model1 = loadModels("../res/world2-2.obj"); //houses
	std::vector<glm::vec3> model2 = loadModels("../res/car.obj"); //car
	//std::vector<glm::vec3> model3 = loadModels("../res/plane.obj"); //plane

	//CODE FOR DISABLING CAR AND PLANE

	glm::vec3 temp(0.0f, 0.0f, 0.0f);

	//std::vector<glm::vec3> model2;//car
	//model2.push_back(temp);

	std::vector<glm::vec3> model3; //plane
	model3.push_back(temp);

	//models.insert(models.end(), model1.begin(), model1.end()); //append model 1 to models
	//models.insert(models.end(), model2.begin(), model2.end()); //model 2
	//models.insert(models.end(), model3.begin(), model3.end());

	//track number of verts
	modelSizes.push_back(model1.size()); //car
	modelSizes.push_back(model2.size()); //houses
	modelSizes.push_back(model3.size()); //plane

	NumVertices = models.size();

	//NumVertices = model1.size();

	//This function stores all the links between shader attributes and VBOs
	//a vertex array object is like a macro in that it remember what has been done to the vertex buffer
	/*The VAO remembers stuff like...
	glEnableClientState(GL_VERTEX_ARRAY); glVertexPointer...; glEnableClientState(GL_NORMAL_ARRAY); glNormalPointer...
	which I am not currently using, but when binding an already created VAO, a bunch of vertex attribute data is recovered without a lot of messy code*/
	//glBindVertexArray() replays that same macro
	glGenVertexArrays(1, &VAOs[0]); //return NumVAOs unused names as VAOs into array VAOs
	glBindVertexArray(VAOs[0]); //3 things: If VAOs index is NOT 0, create new VAO and assign that name
										//  If VAOs index has already been created, make it active
										//  If VAOs index is 0, stop using VAOs and return to default state for vertex arrays

										//ATTRIBUTES

										//if you create a shader attribute, you need to get it's location like below, and store it's index, then define it's interaction with glVertexAttribPointer

										//position

	//this is where vertex data is ACTUALLY stored
	glGenBuffers(1, &VBOs[0]);  //return NumBuffers unused names as VBOs into array Buffers, names need not be continuous integers
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);  /* 3 things:  If Buffers index is NOT 0, create new VBO and assign that name
																		If Buffers index has already been created, make it active
																		If Buffers index is 0, stop using buffer objects for target (parameter 1)*/

																		//This needs to execute AFTER shader is compiled, and now it is
																		//This function also stores the current VBO so it does not need to be binded when drawing begins
																		/* Specifies where and how data for posAttrib, which is an index, which is a shader attribute location, can be accessed */
	//glVertexAttribPointer(posAttrib,  /* GLuint index, the shader attribute location being pointed to*/
	//	3,			/*GLint size, number of components to be updated per vertex
	//				can be 1,2,3,4 or GL_BGRA*/
	//	GL_FLOAT,	/*GLenum type, type of data in array*/
	//	GL_FALSE,	/*GLboolean normalized, should vertex data be normalized before being store?*/
	//	0,			/*GLsizei stride, byte offset between consecutive element in array, 0 means tightly packed*/
	//	BUFFER_OFFSET(0)); /*   GLvoid* pointer, is the offset from the start of the buffer object, in bytes,
	//					   for the first set of values in the array BUFFER_OFFSET(0) just means there is an offset of 0
	//					   The use of this macro explains the use of a buffer object (stored on GPU), as opposed to normal pointer*/

	//glEnableVertexAttribArray(posAttrib); //enables posAttrib attribute

	// transfer vertex data from my objects into the (active?) buffer object
	// allocates storage for vertex data AND copy data from client arrays to OPENGL server's memory
	glBufferData(
		GL_ARRAY_BUFFER, /* Targets:
						 GL_ARRAY_BUFFER for vertex attribute data
						 GL_ELEMENT_ARRAY_BUFFER for index data
						 GL_PIXEL_UNPACK_BUFFER for pixel data passed into OPENGL
						 GL_PIXEL_PACK_BUFFER for pixel data being retrieved from OPENGL
						 GL_COPY_READ_BUFFER  see below
						 GL_COPY_WRITE_BUFFER for copying between buffers
						 GL_TEXTURE_BUFFER for texture data stored as texture buffer
						 GL_UNIFORM_BUFFER for uniform variable values TODO find info on this*/
		sizeof(glm::vec3) * model1.size(), //How much storage required
		&model1.front(), /*   OGL is looking for a stream of data, this gives it the starting point
						 Can be either a pointer to client memory (which I'm using) or NULL to reserve storage for later*/
		GL_STATIC_DRAW); /* Provide hint as to how the data will be read and written after allocation*/

	/*TODO, implement element buffer kinda like this: ALSO, Use Uniform Buffer Objects and Index Buffer Objects

	GLuint ebo;
	glGenBuffers(1, &ebo);

	...

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
	sizeof(elements), elements, GL_STATIC_DRAW);

	Also use glDrawElements instead of glDrawArrays

	*/

	//time to buffer model2: Gen buffer ID, then bind it

	glGenBuffers(1, &VBOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * model2.size(), &model2.front(), GL_STATIC_DRAW);

	//buffer model3
	glGenBuffers(1, &VBOs[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * model3.size(), &model3.front(), GL_STATIC_DRAW);

	//NumVertices += model2.size(); //add total size for all models

	// TODO Vertices passed in to OGL here are normalized-device coordinates, I need to find out how to convert them

	//BEGIN MATRICE INIT

	//UNIFORMS ARE NOT SHADER ATTRIBUTES, attributes vary by vertex, uniforms are constant across all vertices

	//Create Model matrix

	//init model matrix. This is initialized as an identity matrix
	glm::mat4 modelMat;
	//modelMat = glm::rotate(modelMat, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	//pass model matrix to shader
	GLint modelUniform = glGetUniformLocation(programID, "vModel");
	glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(modelMat)); //glm::value_ptr gets pointer to beginning of matrix data, which effectively converts matrix to array of floats

	//Create View matrix

	//init view matrix
	glm::mat4 viewMat = glm::lookAt(
		glm::vec3(0.0f, 0.0f, -2.0f), //position
		glm::vec3(0.0f, 0.0f, 0.0f),  //vector to aim camera at
		glm::vec3(0.0f, 1.0f, 0.0f)   //up axis
	);

	GLint viewUniform = glGetUniformLocation(programID, "vView");
	glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(viewMat));

	//Create Perspective Projection Matrix

	//init projection matrix
	GLfloat aspectRatio = width / height;
	glm::mat4 projMat = glm::perspective(glm::radians(90.0f), aspectRatio, 0.2f, 1000.0f);

	GLint projUniform = glGetUniformLocation(programID, "vProj");
	glUniformMatrix4fv(projUniform, 1, GL_FALSE, glm::value_ptr(projMat));
}

void animate(int data) {
	glutTimerFunc(10, animate, -1);

	if (animCar < 100.0f) {
		animCar += 0.1f;
		animPlane += 0.1f;
	}
	else {
		//isReverse = true;
		//animRotation = 180;
		animCar = -100;
		animPlane = -100;
	}

	//if (isReverse) {
	//	animCar -= 0.1f;
	//	animPlane -= 0.1f;
	//	if (animCar <= -100) {
	//		isReverse = false;
	//		animRotation = 0;
	//	}
	//}

	glutPostRedisplay();
}

void display(void) {
	// clear image
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	//THIS is the function to switch between different collections of vertex ATTRIBUTES
	glBindVertexArray(VAOs[0]);

	//DRAW both wireframe and fill

	GLint colorAttrib = glGetAttribLocation(programID, "color");
	glVertexAttrib3f(colorAttrib, 0.7f, 0.0f, 0.0f); //set color to dark red for fill
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	drawModels();

	glVertexAttrib3f(colorAttrib, 1.0f, 1.0f, 1.0f); //set color to white for wireframe
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	drawModels();

	//drawText();

	//drawMonkeyHeads();
	//drawMonkeyDrill(20); //Monkey drill

				//glFinish() for measuring how long something takes DONT USE IN RELEASE
	glutSwapBuffers();
}

// called when window is resized
void reshape(int w, int h)
{
	double w2h = (height > 0) ? (double)width / height : 1;

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-dim*w2h, +dim*w2h, -dim, +dim, -dim * 5, +dim * 20);
	//gluPerspective(45, 1.0 * w2h, 1, 6);

	glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y) { //called on click of any mouse button
	switch (button) {
	case GLUT_RIGHT_BUTTON: //if right mouse button is pressed, go into a loop of mouseMotion until button is released

		//glutMotionFunc(mouseMotion); //for first person camera
		glutMotionFunc(carMotion); // for car camera
	}
}

//for car control and camera
void carMotion(int x, int y) { //glut detects when no mouse buttons are pressed and exits this function
	width = glutGet(GLUT_WINDOW_WIDTH);
	height = glutGet(GLUT_WINDOW_HEIGHT);

	GLint wMid = width / 2;
	GLint hMid = height / 2;

	GLint newTime = glutGet(GLUT_ELAPSED_TIME);
	GLint delta = newTime - oldTime;
	oldTime = newTime;

	GLboolean xCentered = false;
	GLboolean yCentered = false;
	GLboolean isMouseCentered = false;

	if (x > wMid - 2 && x < wMid + 2) xCentered = true;
	if (y > hMid - 2 && y < hMid + 2) yCentered = true;

	if (xCentered && yCentered) // if mouse is already centered
		isMouseCentered = true;
	else
		isMouseCentered = false;

	if (!isMouseCentered) {
		if (x > wMid) { yaw += 1.5; } //rotate right
		else if (x < wMid) { yaw -= 1.5; } //rotate left

		if (y < hMid) { pitch += 1.5; } //rotate up
		else if (y > hMid) { pitch -= 1.5; } //rotate down

											 //limit pitch to not break camera
		if (pitch > 89.9) pitch = 89.9;
		if (pitch < -89.9) pitch = -89.9;

		//avoid huge angles
		if (yaw > 360 || yaw < -360) yaw = 0;

		//Create View matrix

		//init view matrix

		glm::vec3 front;

		//calculate forward vector position using trig
		front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
		front.y = sin(glm::radians(pitch));
		front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

		//std::cout << "Pitch: " << pitch << " ";
		//std::cout << "Yaw: " << yaw << " ";
		//std::cout << "x: " << x << " ";
		//std::cout << "wMid: " << wMid << " ";
		//std::cout << "y: " << y << " ";
		//std::cout << "hMid: " << hMid << " " << std::endl;
		//if(xCentered && yCentered) std::cout << "THIS SHOULD NOT HAPPEN" << std::endl;

		//std::cout << "x: " << front.x << " ";
		//std::cout << "y: " << front.y << " ";
		//std::cout << "z: " << front.z << std::endl;

		//cameraPos = glm::vec3(0.0f, 0.0f, -2.0f);
		cameraFront = glm::normalize(front);
		//cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

		glm::vec3 normFront = glm::normalize(front);

		cameraViewMat = glm::lookAt(
			cameraPos, //position
			cameraPos + cameraFront,  //vector to aim camera at. Position vector + view direction (front) = where the camera is actually looking
			cameraUp   //up axis
		);

		GLint viewUniform = glGetUniformLocation(programID, "vView");
		glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(cameraViewMat));

		glFlush();

		glutWarpPointer(wMid, hMid); // warp pointer to center of window
	}
}

//car keyboard control
void carKeyboard(GLubyte key, int x, int y) {
	GLfloat cameraHeight = 5.0f;

	//Cross product of the camera FRONT (if looking down Z axis) vector and the camera UP vector (Y axis) gives a direction ORTHOGONAL to both axis (x axis), which lets me strafe the camera NEAT
	switch (key) {
		// notice that to move the camera right with D, the world moves left
	case 'd':
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp))  * cameraSpeed; //normalize to remove speed changes based on camera orientation. Sets result of cross to length of 1
		cameraPos.y = cameraHeight;
		break;

	case 'a':
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp))  * cameraSpeed;
		cameraPos.y = cameraHeight;
		break;

	case 'w':
		cameraPos += cameraSpeed * cameraFront; // adding the front vector to position vector makes sense here because
		cameraPos.y = cameraHeight;            // we want to travel in the same direction that the camera is pointing, so they are indeed the same
		cameraSpeed += 0.05f;
		break;

	case 's':
		cameraPos -= cameraSpeed * cameraFront;
		cameraPos.y = cameraHeight;
		break;
	case '=':
		cameraSpeed += 0.1f;
		break;
	case '-':
		cameraSpeed -= 0.1f;
		break;
	}

	//apply changes to view matrix
	glm::mat4 viewMat = glm::lookAt(
		cameraPos, //position
		cameraPos + cameraFront,  //vector to aim camera at
		cameraUp   //up axis
	);

	GLint viewUniform = glGetUniformLocation(programID, "vView");
	glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(viewMat));

	glutPostRedisplay();
}

//special keyboard input (F1, ESC, etc...)
void specKeyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_F1: exit(0); //exit program on F1
	case GLUT_KEY_F2:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glutPostRedisplay();
		break;
	case GLUT_KEY_F3:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP:
		moveBoundZ += 0.5f;
		break;
	case GLUT_KEY_DOWN:
		moveBoundZ -= 0.5f;
		break;
	case GLUT_KEY_RIGHT:
		moveBoundX -= 0.5f;
		break;
	case GLUT_KEY_LEFT:
		moveBoundX += 0.5f;
		break;
	}
}

int main(int argc, char ** argv) {
	//GFX boilerplate
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // type of window
	glutInitWindowSize(width, height);
	glutInitContextVersion(3, 3); // OpenGL context version 3.3
	glutInitContextProfile(GLUT_CORE_PROFILE); // This controls the available features

	glutCreateWindow("MONKEY DRILL EXTREME!"); //actually creates the window

	glewExperimental = GL_TRUE;
	if (glewInit()) {
		std::cerr << "Unable to initialize GLEW ... exiting" << std::endl;
		exit(EXIT_FAILURE);
	}

	init();

	//resize
	glutReshapeFunc(reshape); //select function for reshaping window

	// normal display
	glutDisplayFunc(display); //select function for displaying graphics

	animate(1); //smooth

	glutSpecialFunc(specKeyboard); // listen for special input

	//glutKeyboardFunc(keyboard); // listen for flying camera keyboard
	glutKeyboardFunc(carKeyboard); // listen for car keyboard input

	glutMouseFunc(mouse);

	glutMainLoop(); //infinite loop
}

std::vector< glm::vec3 > loadModels(std::string path) {
	//init
	std::vector< glm::vec3 > vertices; //for storing indexed verts
	std::vector< glm::vec3 > outVertices; //for storing unindexed verts
	std::vector< unsigned int > vertexIndices;
	std::ifstream source;
	source.open(path);

	if (source.is_open())
		std::cout << "FILE SUCCESS" << std::endl;
	else
		std::cout << "FILE FAILURE" << std::endl;

	//ignore comments
	//ignore mtllib
	//ignore o
	//record v float float float
		//getline
		//check if line begins with a v
			//if FALSE, get next line
		//if TRUE parse float values into vertices vector
	//ignore vn (vertice normal)?
	//record f because I need to unindex the vertices because OGL is awful

	//REMEMBER .obj starts index at 1 NOT 0

	for (std::string buffer; std::getline(source, buffer); ) {
		if (buffer[0] == 'v' && buffer[1] != 'n') { // if vertex
			//append to vertices
			//std::cout << buffer << std::endl;
			std::stringstream ss(buffer); //use stringstream to "tokenize" buffer instead of ifstream which... doesn't... I guess.
			glm::vec3 v;

			ss.clear();
			ss << " "; //allows stringstream to understand the string WHY?
			ss >> v.x >> v.y >> v.z;

			vertices.push_back(v);

			//std::cout << v.x << v.y << v.z;
		}
		else if (buffer[0] == 'f') { // if face
			unsigned int vertexIndex[3], normalIndex[3];
			std::stringstream ss(buffer);

			ss.clear();
			ss << " ";

			for (int i = 0; i < 3; ++i) {
				ss >> vertexIndex[i];
				ss.ignore(2); //ignore 2 forward slashes
				ss >> normalIndex[i];
			}

			/*ss >> vertexIndex[0] >> normalIndex[0] //store indices from stream, not using normal right now, only vertex
				>> vertexIndex[1] >> normalIndex[1]
				>> vertexIndex[2] >> normalIndex[2];*/

			vertexIndices.push_back(vertexIndex[0]); //store each vertexIndex too OpenGlize the actual vertices
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
		}
	}

	//convert vector to GLfloat array
	//const int numVerts = vertices.size() * 3;
	//GLfloat tempVert[NumVertices][3];
	//GLfloat tempVert[numVerts];

	//for (auto i : vertices) {
	//}

	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i]; //store index
		glm::vec3 vertex = vertices[vertexIndex - 1]; //convert from obj index to C++ "start at 0" index
		outVertices.push_back(vertex); //push the copied vertex into the final OpenGL compatible vector
	}

	source.close();

	return outVertices;
}

//read shader from file from http://lazyfoo.net/tutorials/OpenGL/30_loading_text_file_shaders/index.php
//slightly edited by me
GLuint loadShaderFromFile(std::string path, GLenum shaderType) {
	//Open file
	GLuint shaderID = 0;
	std::string shaderString;
	std::ifstream sourceFile(path.c_str());

	//Source file loaded
	if (sourceFile) {
		//Get shader source
		shaderString.assign((std::istreambuf_iterator< char >(sourceFile)), std::istreambuf_iterator< char >());
		sourceFile.close();
		if (sourceFile.is_open()) std::cout << "File DID NOT CLOSE" << std::endl;
	}

	//Create shader ID
	shaderID = glCreateShader(shaderType);
	if (shaderID == 0)
		std::cout << "Error creating shader" << std::endl;

	//Set shader source
	const GLchar* shaderSource = shaderString.c_str();
	glShaderSource(shaderID, 1, (const GLchar**)&shaderSource, NULL);

	//print contents of shaderSource
	std::cout << shaderSource << std::endl;

	//Compile shader source
	glCompileShader(shaderID);

	//Check shader for errors
	GLint shaderCompiled = GL_FALSE;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shaderCompiled);

	if (shaderCompiled != GL_TRUE) {
		printf("Unable to compile shader %d!\n\nSource:\n%s\n", shaderID, shaderSource);

		//get max length of log
		GLint maxlength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxlength);

		//get actual log, store at [0] of log vector
		std::vector<GLchar> log(maxlength);
		glGetShaderInfoLog(shaderID, maxlength, NULL, &log[0]);

		//print log
		for (auto i : log) {
			std::cout << i;
		}

		glDeleteShader(shaderID);
		shaderID = 0;

		return -1;
	}

	return shaderID;
}

//returns programID
GLuint initShaders() {
	/*  Create shader object
		Compile shader source into object
		Verify compilation

		For multiple shader objects into a program:
		Create shader program
		Attach appropriate shader objects to program
		Link shader program
		Verify link phase
		use shaders*/
		/*  GLSL type modifiers const, in, out, uniform(constant across a given primitive, calculated on GPU?),
			buffer(AKA shader storage buffer, specifies read-write memory shared with application),
			shared(variables ahred within local work group, only used in compute shaders
			GLSL parameter access modifiers, if one is not present, in is implicitly added, modifiers are: in, const in, out, inout
			uniform variables "form a bridge between shader and application" and can be initialized with glBufferData
			glGetUniformBlockIndex(GLuint program const char* uniformBlockName) - return index of named block, else returns GL_INVALID_INDEX
			glGetActiveUniformBlockiv() returns GL_UNIFORM_BLOCK_DATA_SIZE, which is size of block as generated by compiler
			glBindBufferRange() for associating buffer object with a block, or glBindBufferBase() to use ALL buffer storage
			glGetUniformIndices() to get indices of a named uniform variable
			glGetActiveUniformiv() to get offset and size for that index*/

			//SHADERS
		//	GLuint vShaderID = loadShaderFromFile("mine.vert", GL_VERTEX_SHADER);
		//	GLuint fShaderID = loadShaderFromFile("mine.frag", GL_FRAGMENT_SHADER);

			//PASSTHROUGH LOAD
	GLuint vShaderID = loadShaderFromFile("pass.vert", GL_VERTEX_SHADER);
	GLuint fShaderID = loadShaderFromFile("pass.frag", GL_FRAGMENT_SHADER);

	if (vShaderID == -1 || fShaderID == -1) {
		std::cout << "Error loading shaders. Aborting..." << std::endl;
		return -1;
	}
	GLuint programID = glCreateProgram();
	if (programID == 0)
		std::cout << "Error creating program" << std::endl;

	glAttachShader(programID, vShaderID);
	glAttachShader(programID, fShaderID);

	/*  attempt to link shaders into program and check for success
		Creates a table of all uniform variables, obtain index with glGetUniformLocation
		glGetUniformLocation(GLuint program, const char* name) - returns index of (a uniform variable) name associated with program, returns -1 if name does not match
		glUniform{1234}{fdi ui} - sets value for uniform variable at some index*/
	glLinkProgram(programID);

	GLint isProgramLinked = GL_FALSE;
	glGetProgramiv(programID, GL_LINK_STATUS, &isProgramLinked);
	if (isProgramLinked == GL_FALSE)
		std::cout << "Error linking program" << std::endl;

	glUseProgram(programID);

	return programID;
}

GLuint initTextShaders() {
	//PASSTHROUGH LOAD
	GLuint vShaderID = loadShaderFromFile("text.vert", GL_VERTEX_SHADER);
	GLuint fShaderID = loadShaderFromFile("text.frag", GL_FRAGMENT_SHADER);
	GLuint gShaderID = loadShaderFromFile("text.geom", GL_GEOMETRY_SHADER);

	if (vShaderID == -1 || fShaderID == -1 || gShaderID == -1) {
		std::cout << "Error loading shaders. Aborting..." << std::endl;
		return -1;
	}

	GLuint programID = glCreateProgram();
	if (programID == 0)
		std::cout << "Error creating program" << std::endl;

	glAttachShader(programID, vShaderID);
	glAttachShader(programID, fShaderID);
	glAttachShader(programID, gShaderID);

	/*  attempt to link shaders into program and check for success
	Creates a table of all uniform variables, obtain index with glGetUniformLocation
	glGetUniformLocation(GLuint program, const char* name) - returns index of (a uniform variable) name associated with program, returns -1 if name does not match
	glUniform{1234}{fdi ui} - sets value for uniform variable at some index*/
	glLinkProgram(programID);

	GLint isProgramLinked = GL_FALSE;
	glGetProgramiv(programID, GL_LINK_STATUS, &isProgramLinked);
	if (isProgramLinked == GL_FALSE)
		std::cout << "Error linking program" << std::endl;

	glUseProgram(programID);

	return programID;
}

void drawText() {
	//constants

	glUseProgram(textProgramID);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 999);
	GLuint charAttrib = glGetAttribLocation(textProgramID, "Character");
	glEnableVertexAttribArray(charAttrib);

	//glGenTextures();
	glBindTexture(GL_TEXTURE_2D, 3); //GLuint texture

	glUniform3f(glGetUniformLocation(textProgramID, "TextColor"), 1, 1, 1);
	glUniform2f(glGetUniformLocation(textProgramID, "CellSize"), 1.0f / 16, (300.0f / 384) / 6);
	glUniform2f(glGetUniformLocation(textProgramID, "CellOffset"), 0.5 / 256.0, 0.5 / 256.0);
	glUniform2f(glGetUniformLocation(textProgramID, "RenderSize"), 0.75 * 16 / width / 2, 0.75 * 33.33 / height / 2);
	//glUniform2f(glGetUniformLocation(textProgramID, "RenderSize"), 100.0f, 100.0f);
	glUniform2f(glGetUniformLocation(textProgramID, "RenderOrigin"), -0.96, 0.9);

	const char* text = "Hello world.";

	glVertexAttribIPointer(charAttrib, 1, GL_UNSIGNED_BYTE, 1, text);
	glDrawArrays(GL_POINTS, 0, strlen(text));

	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(programID);
}

void printVerts(std::vector<glm::vec3> pVert) {
	for (auto i : pVert) {
		printf(" % 0.6f ", i.x);
		printf(" % 0.6f ", i.y);
		printf(" % 0.6f \n", i.z);
	}
}

void drawModels() {
	drawHouse();
	//drawCar();
	drawPlayerCar();
	drawPlane();
}

void drawHouse() {
	GLint posAttrib = glGetAttribLocation(programID, "vPosition");
	glm::mat4 modelMat;
	GLint modelUniform = glGetUniformLocation(programID, "vModel");

	GLfloat distance = 70.0f;
	GLint numHouses = 10;
	GLfloat boundSize = distance * numHouses;

	//Draw enviornment
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]); //switch to model1
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(posAttrib);

	for (GLfloat i = 0; i < numHouses; i++) {
		modelMat = glm::translate(modelMat, glm::vec3(distance * i, 0.0f, 0.0f));
		glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(modelMat));
		glDrawArrays(GL_TRIANGLES, 0, modelSizes[0]);
		modelMat = glm::mat4(); //set model matrix to identity matrix to prepare for next translation
	}

	//Draw Bounds

	glm::mat4x4 houseMat = glm::mat4();
	houseMat = glm::translate(houseMat, glm::vec3(0.0f, 0.0f, -24.0f));
	glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(houseMat));

	AABB houseAABB = AABB(glm::vec3(0.0f, -10.0f, 0.0f), glm::vec3(boundSize, 10.0f, 10.0f));
	houseAABB.scale(1.0f);
	houseAABB.transform(houseMat);
	houseAABB.draw(houseMat);

	houseMat = glm::mat4();
	houseMat = glm::translate(houseMat, glm::vec3(0.0f, 0.0f, 11.0f));
	glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(houseMat));

	AABB houseAABB2 = AABB(glm::vec3(0.0f, -10.0f, 0.0f), glm::vec3(boundSize, 10.0f, 10.0f));
	houseAABB2.scale(1.0f);
	houseAABB2.transform(houseMat);
	houseAABB2.draw(houseMat);

	/*RECREATE CAR BOUNDING BOX WITHOUT DRAWING ANYTHING FOR COLLISION TESTING*/
	AABB carAABB = AABB(glm::vec3(-4.5f, -1.5f, -3.0f), glm::vec3(4.5f, 4.5f, 3.0f));

	//rotate the TRANSLATION of the car so it faces the right way
	modelMat = glm::rotate(glm::translate(modelMat, glm::vec3(cameraPos.x + 5.0f, cameraPos.y - 5.0f, cameraPos.z)), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(modelMat));

	//draw bounding box
	glm::vec3 boundVec(0.0f, 0.0f, 0.0f); // to align with car
	modelMat = glm::translate(modelMat, boundVec);

	carAABB.scale(0.5f);
	carAABB.transform(modelMat);

	//pass identity
	houseMat = glm::mat4();
	glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(houseMat));

	if (carAABB.intersects(houseAABB) || carAABB.intersects(houseAABB2)) {
		std::cout << "COLLISION" << std::endl;
		//assert(false && "You crashed more than just the car!");
	}
	else std::cout << "NOT COLLIDING" << '\r';
}

void drawCar() {
	GLint posAttrib = glGetAttribLocation(programID, "vPosition");
	glm::mat4x4 modelMat;
	GLint modelUniform = glGetUniformLocation(programID, "vModel");
	AABB carAABB = AABB(glm::vec3(-4.5f, -1.5f, -3.0f), glm::vec3(4.5f, 4.5f, 3.0f));

	//Draw car
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]); //select car model stored at VBOs[1]
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(posAttrib);

	//if (animRotation == 180) modelMat = glm::rotate(modelMat, glm::radians(animRotation), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec3 animVec(-animCar, 0.0f, 0.0f);
	modelMat = glm::translate(modelMat, animVec);

	glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(modelMat));
	glDrawArrays(GL_TRIANGLES, 0, modelSizes[1]);

	//draw bounding box
	glm::vec3 boundVec(0.0f, 0.0f, 0.0f); // to align with car
	modelMat = glm::translate(modelMat, boundVec);

	carAABB.scale(0.5f);
	carAABB.transform(modelMat);
	carAABB.draw(modelMat);

	//pass identity
	modelMat = glm::mat4();
	glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(modelMat));
}

void drawPlayerCar() {
	GLint posAttrib = glGetAttribLocation(programID, "vPosition");
	glm::mat4x4 modelMat;
	GLint modelUniform = glGetUniformLocation(programID, "vModel");
	AABB carAABB = AABB(glm::vec3(-4.5f, -1.5f, -3.0f), glm::vec3(4.5f, 4.5f, 3.0f));

	//Draw car
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]); //select car model stored at VBOs[1]
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(posAttrib);

	//rotate the TRANSLATION of the car so it faces the right way
	modelMat = glm::rotate(glm::translate(modelMat, glm::vec3(cameraPos.x + 5.0f, cameraPos.y - 5.0f, cameraPos.z)), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(modelMat));
	glDrawArrays(GL_TRIANGLES, 0, modelSizes[1]);

	//draw bounding box
	glm::vec3 boundVec(0.0f, 0.0f, 0.0f); // to align with car
	modelMat = glm::translate(modelMat, boundVec);

	carAABB.scale(0.5f);
	carAABB.transform(modelMat);
	carAABB.draw(modelMat);

	//pass identity
	modelMat = glm::mat4();
	glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(modelMat));
}

void drawPlane() {
	GLint posAttrib = glGetAttribLocation(programID, "vPosition");
	glm::mat4 modelMat;
	GLint modelUniform = glGetUniformLocation(programID, "vModel");

	//Draw plane
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(posAttrib);

	//if (animRotation == 180) modelMat = glm::rotate(modelMat, glm::radians(animRotation), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMat = glm::translate(modelMat, glm::vec3(0.0f, 100.0f, animPlane));

	glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(modelMat));
	glDrawArrays(GL_TRIANGLES, 0, modelSizes[2]);
	modelMat = glm::mat4();
}

void testBoundingBoxes() {
	/*----------------------------------------------------------------------------------------------------*/
	GLint modelUniform = glGetUniformLocation(programID, "vModel");
	//TEST BB for collision
	glm::mat4x4 testMat = glm::mat4();
	testMat = glm::translate(testMat, glm::vec3(moveBoundX, 2.0f, moveBoundZ));
	glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(testMat));

	AABB testAABB = AABB(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(5.0f, 4.0f, 4.0f));
	testAABB.scale(2.0f);
	testAABB.transform(testMat);
	testAABB.draw(testMat);

	//TEST 2 BB for collision
	glm::mat4x4 testMat2 = glm::mat4();
	testMat2 = glm::translate(testMat2, glm::vec3(0.0f, 2.0f, 0.0f));
	glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(testMat2));

	AABB testAABB2 = AABB(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(4.0f, 4.0f, 4.0f));
	testAABB2.scale(2.0f);
	testAABB2.transform(testMat2);
	testAABB2.draw(testMat2);

	//if (carAABB.intersects(testAABB)) std::cout << "COLLISION" << std::endl;
	//else std::cout << "NOT COLLIDING" << std::endl;

	//TEST COLLISION OUTPUT
	if (testAABB.intersects(testAABB2)) std::cout << "COLLISION" << '\r';
	else std::cout << "NOT COLLIDING" << '\r';
	/*----------------------------------------------------------------------------------------------------*/

	testMat = glm::mat4();
	testMat2 = glm::mat4();
	glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(testMat));
}