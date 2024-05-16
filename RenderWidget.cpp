//
// copyright 2018 Palestine Polytechnic Univeristy
//
// This software can be used and/or modified for academich use as long as
// this commented part is listed
//
// Last modified by: Zein Salah, on 23.04.2024
//

#include "RenderWidget.h"
#include <GL/freeglut.h>
#include <QPainter>
#include <cmath>
#include <QMouseEvent>


RenderWidget::RenderWidget(QWidget *parent) : QOpenGLWidget(parent)
{
  m_ViewPoint.x = 5.0;
  m_ViewPoint.y = 5.0;
  m_ViewPoint.z = 5.0;
}

RenderWidget::~RenderWidget()
{
}

QSize RenderWidget::minimumSizeHint() const
{
  return QSize(100, 100);
}

QSize RenderWidget::sizeHint() const
{
  return QSize(600, 600);
}

void RenderWidget::initializeGL()
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
}

void RenderWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(m_ViewPoint.x, m_ViewPoint.y, m_ViewPoint.z, /* view point */
            0.0, 0.0, 0.0,                               /* ref point */
            0.0, 1.0, 0.0); 
                                         /* up direction is positive y-axis */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(m_FieldOfView, 1.0, 1.0, 100.0);

  // drawCube();
  drawCubeWithLighting();
}

void RenderWidget::resizeGL(int width, int height)
{
  int side = qMin(width, height);
  glViewport((width - side) / 2, (height - side) / 2, side, side);

  //  glViewport(0, 0, width, height);
}

void RenderWidget::zoomIn()
{

  //  m_ViewPoint.x *= 0.95;
  // m_ViewPoint.y *= 0.95;
  // m_ViewPoint.z *= 0.95;

  m_FieldOfView = std::max(m_FieldOfView - 1, 1.0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(m_FieldOfView, 1.0, 1.0, 100.0);

  glMatrixMode(GL_MODELVIEW);

  update();
}

void RenderWidget::zoomOut()
{
  //  std::cout << "Zooming Out..\n";

  // m_ViewPoint.x /= 0.95;
  // m_ViewPoint.y /= 0.95;
  // m_ViewPoint.z /= 0.95;

  m_FieldOfView = std::min(m_FieldOfView + 1, 179.0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(m_FieldOfView, 1.0, 1.0, 100.0);

  glMatrixMode(GL_MODELVIEW);

  update();
}

void RenderWidget::rotateAboutY()
{
  double angle = 5.0 / 180 * M_PI;

  //  std::cout << "Rotating about Y by " << angle << "\n";

  double newx = m_ViewPoint.x * cos(angle) + m_ViewPoint.z * sin(angle);
  double newz = -m_ViewPoint.x * sin(angle) + m_ViewPoint.z * cos(angle);

  m_ViewPoint.x = newx;
  m_ViewPoint.z = newz;

  update();
}

void RenderWidget::rotateAboutYM()
{
  double angle = -(5.0 / 180 * M_PI);

  //  std::cout << "Rotating about Y by " << angle << "\n";

  double newx = m_ViewPoint.x * cos(angle) + m_ViewPoint.z * sin(angle);
  double newz = -m_ViewPoint.x * sin(angle) + m_ViewPoint.z * cos(angle);

  m_ViewPoint.x = newx;
  m_ViewPoint.z = newz;

  update();
}

void RenderWidget::rotateAboutXP()
{
  double angle = (5.0 / 180 * M_PI);

  double newy = m_ViewPoint.y * cos(angle) + m_ViewPoint.z * sin(angle);
  double newz = -m_ViewPoint.y * sin(angle) + m_ViewPoint.z * cos(angle);

  m_ViewPoint.y = newy;
  m_ViewPoint.z = newz;

  update();
}

void RenderWidget::rotateAboutXM()
{
  double angle = -(5.0 / 180 * M_PI);

  double newy = m_ViewPoint.y * cos(angle) + m_ViewPoint.z * sin(angle);
  double newz = -m_ViewPoint.y * sin(angle) + m_ViewPoint.z * cos(angle);

  m_ViewPoint.y = newy;
  m_ViewPoint.z = newz;

  update();
}

void RenderWidget::rotateAboutZP()
{
  double angle = (5.0 / 180 * M_PI);

  double newx = m_ViewPoint.x * cos(angle) + m_ViewPoint.y * sin(angle);
  double newy = -m_ViewPoint.x * sin(angle) + m_ViewPoint.y * cos(angle);

  m_ViewPoint.x = newx;
  m_ViewPoint.y = newy;

  update();
}

void RenderWidget::rotateAboutZN()
{
  double angle = -(5.0 / 180 * M_PI);

  double newx = m_ViewPoint.x * cos(angle) + m_ViewPoint.y * sin(angle);
  double newy = -m_ViewPoint.x * sin(angle) + m_ViewPoint.y * cos(angle);

  m_ViewPoint.x = newx;
  m_ViewPoint.y = newy;

  update();
}

void RenderWidget::drawCube(void)
{
  GLfloat cubeCorner[8][3];

  cubeCorner[0][0] = -0.5;
  cubeCorner[0][1] = -0.5;
  cubeCorner[0][2] = -0.5;
  cubeCorner[1][0] = 0.5;
  cubeCorner[1][1] = -0.5;
  cubeCorner[1][2] = -0.5;
  cubeCorner[2][0] = 0.5;
  cubeCorner[2][1] = 0.5;
  cubeCorner[2][2] = -0.5;
  cubeCorner[3][0] = -0.5;
  cubeCorner[3][1] = 0.5;
  cubeCorner[3][2] = -0.5;
  cubeCorner[4][0] = -0.5;
  cubeCorner[4][1] = -0.5;
  cubeCorner[4][2] = 0.5;
  cubeCorner[5][0] = 0.5;
  cubeCorner[5][1] = -0.5;
  cubeCorner[5][2] = 0.5;
  cubeCorner[6][0] = 0.5;
  cubeCorner[6][1] = 0.5;
  cubeCorner[6][2] = 0.5;
  cubeCorner[7][0] = -0.5;
  cubeCorner[7][1] = 0.5;
  cubeCorner[7][2] = 0.5;

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glLineWidth(3);
  glBegin(GL_QUADS);

  glColor3f(0.0, 0.0, 0.0); // blue
  glVertex3fv(cubeCorner[3]);
  glVertex3fv(cubeCorner[2]);
  glVertex3fv(cubeCorner[1]);
  glVertex3fv(cubeCorner[0]);

  glColor3f(1.0, 1.0, 0.0); // yellow
  glVertex3fv(cubeCorner[1]);
  glVertex3fv(cubeCorner[5]);
  glVertex3fv(cubeCorner[4]);
  glVertex3fv(cubeCorner[0]);

  glColor3f(0.0, 1.0, 1.0);
  glVertex3fv(cubeCorner[3]);
  glVertex3fv(cubeCorner[7]);
  glVertex3fv(cubeCorner[6]);
  glVertex3fv(cubeCorner[2]);

  glColor3f(1.0, 0.0, 0.0); // red
  glVertex3fv(cubeCorner[4]);
  glVertex3fv(cubeCorner[5]);
  glVertex3fv(cubeCorner[6]);
  glVertex3fv(cubeCorner[7]);

  glColor3f(1.0, 0.0, 1.0);
  glVertex3fv(cubeCorner[4]);
  glVertex3fv(cubeCorner[7]);
  glVertex3fv(cubeCorner[3]);
  glVertex3fv(cubeCorner[0]);

  glColor3f(0.0, 1.0, 0.0); // green
  glVertex3fv(cubeCorner[2]);
  glVertex3fv(cubeCorner[6]);
  glVertex3fv(cubeCorner[5]);
  glVertex3fv(cubeCorner[1]);
  glEnd();

  glFlush();
}

void RenderWidget::drawCubeWithLighting(void){
  GLfloat cubeCorner[8][3];

  cubeCorner[0][0] = -0.5; cubeCorner[0][1] = -0.5; cubeCorner[0][2] = -0.5;cubeCorner[1][0] = 0.5; 
  cubeCorner[1][1] = -0.5; cubeCorner[1][2] = -0.5;cubeCorner[2][0] = 0.5; cubeCorner[2][1] = 0.5; 
  cubeCorner[2][2] = -0.5; cubeCorner[3][0] = -0.5; cubeCorner[3][1] = 0.5; cubeCorner[3][2] = -0.5;
  cubeCorner[4][0] = -0.5; cubeCorner[4][1] = -0.5; cubeCorner[4][2] = 0.5; cubeCorner[5][0] = 0.5;
  cubeCorner[5][1] = -0.5; cubeCorner[5][2] = 0.5; cubeCorner[6][0] = 0.5;cubeCorner[6][1] = 0.5;
  cubeCorner[6][2] = 0.5;cubeCorner[7][0] = -0.5; cubeCorner[7][1] = 0.5; cubeCorner[7][2] = 0.5;

  GLfloat light_position[] = {200.0, 200.0, 200.0, 0.0};
  GLfloat light_ambient[] = {0.15, 0.15, 0.15, 1.0};
  GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};

  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);


  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glLineWidth(3);

  glBegin(GL_QUADS);

  GLfloat jade_ambient[] = {0.135f, 0.2225f, 0.1575f, 0.95f};
  GLfloat jade_diffuse[] = {0.54f, 0.89f, 0.63f, 0.95f};
  GLfloat jade_specular[] = {0.316228f, 0.316228f, 0.316228f, 0.95f};
  GLfloat jade_shininess[] = {12.8f};

  glMaterialfv(GL_FRONT, GL_AMBIENT, jade_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, jade_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, jade_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, jade_shininess);

  //Jade
  glNormal3fv(cubeCorner[3]);
  glVertex3fv(cubeCorner[3]);
  glNormal3fv(cubeCorner[2]);
  glVertex3fv(cubeCorner[2]);
  glNormal3fv(cubeCorner[1]);
  glVertex3fv(cubeCorner[1]);
  glNormal3fv(cubeCorner[0]);
  glVertex3fv(cubeCorner[0]);

  GLfloat obsidian_ambient[] = {0.05375f, 0.05f, 0.06625f, 0.82f};
  GLfloat obsidian_diffuse[] = {0.18275f, 0.17f, 0.22525f, 0.82f};
  GLfloat obsidian_specular[] = {0.332741f, 0.328634f, 0.346435f, 0.82f};
  GLfloat obsidian_shininess[] = {38.4f};

  glMaterialfv(GL_FRONT, GL_AMBIENT, obsidian_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, obsidian_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, obsidian_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, obsidian_shininess);

  // Obsidian
  glNormal3fv(cubeCorner[1]);
  glVertex3fv(cubeCorner[1]);
  glNormal3fv(cubeCorner[5]);
  glVertex3fv(cubeCorner[5]);
  glNormal3fv(cubeCorner[4]);
  glVertex3fv(cubeCorner[4]);
  glNormal3fv(cubeCorner[0]);
  glVertex3fv(cubeCorner[0]);

  GLfloat pearl_ambient[] = {0.25f, 0.20725f, 0.20725f, 0.922f};
  GLfloat pearl_diffuse[] = {1.0f, 0.829f, 0.829f, 0.922f};
  GLfloat pearl_specular[] = {0.296648f, 0.296648f, 0.296648f, 0.922f};
  GLfloat pearl_shininess[] = {11.264f};

  glMaterialfv(GL_FRONT, GL_AMBIENT, pearl_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, pearl_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, pearl_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, pearl_shininess);

  //Pearl
  glNormal3fv(cubeCorner[3]);
  glVertex3fv(cubeCorner[3]);
  glNormal3fv(cubeCorner[7]);
  glVertex3fv(cubeCorner[7]);
  glNormal3fv(cubeCorner[6]);
  glVertex3fv(cubeCorner[6]);
  glNormal3fv(cubeCorner[2]);
  glVertex3fv(cubeCorner[2]);

  GLfloat ruby_ambient[] = {0.1745f, 0.01175f, 0.01175f, 0.55f};
  GLfloat ruby_diffuse[] = {0.61424f, 0.04136f, 0.04136f, 0.55f};
  GLfloat ruby_specular[] = {0.727811f, 0.626959f, 0.626959f, 0.55f};
  GLfloat ruby_shininess[] = {76.8f};

  glMaterialfv(GL_FRONT, GL_AMBIENT, ruby_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, ruby_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, ruby_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, ruby_shininess);

  // Ruby
  glNormal3fv(cubeCorner[4]);
  glVertex3fv(cubeCorner[4]);
  glNormal3fv(cubeCorner[5]);
  glVertex3fv(cubeCorner[5]);
  glNormal3fv(cubeCorner[6]);
  glVertex3fv(cubeCorner[6]);
  glNormal3fv(cubeCorner[7]);
  glVertex3fv(cubeCorner[7]);

  GLfloat turquoise_ambient[] = {0.1f, 0.18725f, 0.1745f, 0.8f};
  GLfloat turquoise_diffuse[] = {0.396f, 0.74151f, 0.69102f, 0.8f};
  GLfloat turquoise_specular[] = {0.297254f, 0.30829f, 0.306678f, 0.8f};
  GLfloat turquoise_shininess[] = {12.8f};

  glMaterialfv(GL_FRONT, GL_AMBIENT, turquoise_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, turquoise_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, turquoise_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, turquoise_shininess);

  // Turquoise
  glNormal3fv(cubeCorner[4]);
  glVertex3fv(cubeCorner[4]);
  glNormal3fv(cubeCorner[7]);
  glVertex3fv(cubeCorner[7]);
  glNormal3fv(cubeCorner[3]);
  glVertex3fv(cubeCorner[3]);
  glNormal3fv(cubeCorner[0]);
  glVertex3fv(cubeCorner[0]);


  GLfloat emerald_ambient[] = {0.0215f, 0.1745f, 0.0215f, 0.55f};
  GLfloat emerald_diffuse[] = {0.07568f, 0.61424f, 0.07568f, 0.55f};
  GLfloat emerald_specular[] = {0.633f, 0.727811f, 0.633f, 0.55f};
  GLfloat emerald_shininess[] = {76.8f};

  glMaterialfv(GL_FRONT, GL_AMBIENT, emerald_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, emerald_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, emerald_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, emerald_shininess);

  // Emerald
  glNormal3fv(cubeCorner[2]);
  glVertex3fv(cubeCorner[2]);
  glNormal3fv(cubeCorner[6]);
  glVertex3fv(cubeCorner[6]);
  glNormal3fv(cubeCorner[5]);
  glVertex3fv(cubeCorner[5]);
  glNormal3fv(cubeCorner[1]);
  glVertex3fv(cubeCorner[1]);
  glEnd();

  glFlush();
}



void RenderWidget::rotateAboutY(double angle)
{
  angle = angle / 180 * M_PI;

 // std::cout << "Rotating about Y by " << angle << "\n";

  double newx = m_ViewPoint.x*cos(angle) + m_ViewPoint.z*sin(angle);
  double newz = -m_ViewPoint.x*sin(angle) + m_ViewPoint.z*cos(angle);

  m_ViewPoint.x = newx;
  m_ViewPoint.z = newz;

  update();
}

void RenderWidget::rotateAboutX(double angle)
{
  angle = angle / 180 * M_PI;

  double newy = m_ViewPoint.y * cos(angle) + m_ViewPoint.z * sin(angle);
  double newz = -m_ViewPoint.y * sin(angle) + m_ViewPoint.z * cos(angle);

  m_ViewPoint.y = newy;
  m_ViewPoint.z = newz;

  update();
}


void RenderWidget::mouseReleaseEvent(QMouseEvent *event)
{
  IS_LeftButton = IS_MiddleButton = IS_RightButton = false;
}


void RenderWidget::mousePressEvent(QMouseEvent *event)
{
  m_LastMouseX = event->x();
  m_LastMouseY = event->y();

 // std::cout << "Mouse pressed buttom is: " << event->button() << std::endl;

  if (event->button() == LeftButton)    IS_LeftButton = true;
  if (event->button() == MiddleButton)  IS_MiddleButton = true;
  if (event->button() == RightButton)   IS_RightButton = true;
};


void RenderWidget::mouseMoveEvent(QMouseEvent *event)
{
  int dx = event->x() - m_LastMouseX;
  int dy = event->y() - m_LastMouseY;

  if (IS_LeftButton && !IS_MiddleButton)
  {
    rotateAboutY(-(double)dx / 2);
    rotateAboutX(-(double)dy / 2);
  }

  m_LastMouseX = event->x();
  m_LastMouseY = event->y();
};


void RenderWidget::wheelEvent(QWheelEvent * event)
{

};