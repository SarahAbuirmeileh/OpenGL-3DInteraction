# OpenGL 3D Interaction Module 🧊

## Overview 🎯
The OpenGL 3D Interaction Module is a custom component designed for rendering and interacting with 3D graphics using OpenGL. It offers functionalities for zooming, rotating and mouse interaction. As shown here:

![image](https://github.com/SarahAbuirmeileh/SarahAbuirmeileh/assets/127017088/dc5a2885-e252-41b3-84f3-f225744de0b1) <br>


## Usage 👩🏻‍💻
To integrate the OpenGL 3D Interaction Module into your project, include the header file OpenGLInteraction.h. Then, instantiate an object of the module within your user interface. You can interact with the module by invoking its functions and handling mouse events.

## Dependencies 📌
* Qt Framework: This module relies on the Qt framework, specifically utilizing QOpenGLWidget for OpenGL rendering and event handling.
* OpenGL (GLUT): OpenGL is used for rendering 3D graphics, and some functionalities require the OpenGL Utility Toolkit (GLUT).


## Features 💻
1. Zooming: Supports zooming in and out of the scene using the zoomIn() and zoomOut() functions in two different ways (POV & FOV).
2. Rotation: Allows rotation around the X, Y, and Z axes through specific rotation functions like rotateAboutX() and rotateAboutY(), using mouse and buttons.
3. Mouse Interaction: Responds to mouse events such as press, release, and movement, enabling interactive manipulation of the view.


## Functionality  ⚙️✨
* Initialization: Initializes OpenGL settings in the initializeGL() function, configuring the viewport and projection matrix.
* Rendering: Graphics are rendered in the paintGL() function, where OpenGL commands draw the cube.
Event Handling: Mouse events (press, release, move) are handled in the corresponding event functions (mousePressEvent(), mouseReleaseEvent(), mouseMoveEvent()).
* Cube Drawing: Draws a cube using OpenGL commands within the drawCube() function, specifying vertex coordinates and colors.
