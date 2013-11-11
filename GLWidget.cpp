/*
 * GLWidget.cpp
 *
 *  Created on: Nov 3, 2013
 *      Author: Misha
 */

#include "GLWidget.h"
#include <QMouseEvent>
#include <QColorDialog>
#include <qmessagebox.h>
#include <qdebug.h>
#include <qmath.h>


GLWidget::GLWidget(QWidget *parent) :
	QGLWidget(parent) {

	  rotationX = 0.5;
	  rotationY = 10;
	  rotationZ = 15;
	  shouldpaint = false;
}

void GLWidget::initializeGL(){
	glClearColor(0.2, 0.2, 0.2, 1);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	  glPolygonMode(GL_BACK,GL_LINE);
	  glPolygonMode(GL_FRONT,GL_LINE);
	  glColor3f(0, 1,0);
//	glEnable(GL_LIGHTING);
//	glEnable (GL_LIGHT0);
//
//	float ambient[4] = {0.5, 0.5, 0.5, 1};
//	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
//	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
}

void GLWidget::paintGL(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    draw();
}

void GLWidget::resizeGL(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat x = (GLfloat)w / h;
	glFrustum(-x, x, -1.0, 1.0, 6.0, 15.0);
	glMatrixMode(GL_MODELVIEW);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
  lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{

  GLfloat dx = (GLfloat)(event->x() - lastPos.x()) / width();
  GLfloat dy = (GLfloat)(event->y() - lastPos.y()) / height();

    rotationX += 180 * dy;
    rotationY += 180 * dx;
    updateGL();

  lastPos = event->pos();

}

//void GLWidget::mouseDoubleClickEvent(QMouseEvent *event)
//{
//  int face = faceAtPosition(event->pos());
//  if (face != -1) {
//    QColor color = QColorDialog::getColor(faceColors[face],
//                                          this);
//    if (color.isValid()) {
//      faceColors[face] = color;
//      updateGL();
//    }
//  }
//}

int GLWidget::faceAtPosition(const QPoint &pos)
{
  const int MaxSize = 512;
  GLuint buffer[MaxSize];
  GLint viewport[4];

  glGetIntegerv(GL_VIEWPORT, viewport);
  glSelectBuffer(MaxSize, buffer);
  glRenderMode(GL_SELECT);
  glInitNames();
  glPushName(0);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluPickMatrix((GLdouble)pos.x(),
                (GLdouble)(viewport[3] - pos.y()),
                5.0, 5.0, viewport);
  GLfloat x = (GLfloat)width() / height();
  glFrustum(-x, x, -1.0, 1.0, 4.0, 15.0);
  draw();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  if (!glRenderMode(GL_RENDER))
    return -1;
  return buffer[3];
}

void GLWidget::draw(){
	if(shouldpaint){

		  glMatrixMode(GL_MODELVIEW);
		  glLoadIdentity();
		  glTranslatef(0.0, 0.0, -10.0);
		  glRotatef(rotationX, 1.0, 0.0, 0.0);
		  glRotatef(rotationY, 0.0, 1.0, 0.0);
		  glRotatef(rotationZ, 0.0, 0.0, 1.0);

		  float ambient[4] = {0.5, 0.5, 0.5, 1};
		  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

		  float x_step = 2.0 / points.size();
		  float y_step = 2.0 / points[0].size();

		  float y = y_step - 1;
		  int i = 1;
		  while(y < 0.9){
			  float x = x_step - 1;
			  int j = 1;
			  while(x < 0.9){

				  float z = 0.0;
				  if(i < points.size() && j < points[0].size()){
					  z = points[i][j]/max_value;
				  }
				  if(z > 1){
					  z = 1;
				  }
				  if(z < -1){
					  z = -1;
				  }

				  float previous_x_z = z;
				  if(i < points.size() && (j - 1) < points[0].size()){
					  previous_x_z = points[i][j - 1]/max_value;
				  }
				  if(previous_x_z > 1){
					  previous_x_z = 1;
				  }
				  if(previous_x_z < -1){
					  previous_x_z = -1;
				  }

				  float previous_y_z = z;
				  if((i - 1) < points.size() && j < points[0].size()){
					  previous_y_z = points[i - 1][j]/max_value;
				  }
				  if(previous_y_z > 1){
					  previous_y_z = 1;
				  }
				  if(previous_y_z < -1){
					  previous_y_z = -1;
				  }

				  float previous_xy_z = z;
				  if((i - 1) < points.size() && (j - 1) < points[0].size()){
					  previous_xy_z = points[i - 1][j - 1]/max_value;
				  }
				  if(previous_xy_z > 1){
					  previous_xy_z = 1;
				  }
				  if(previous_xy_z < -1){
					  previous_xy_z = -1;
				  }

				  glDisable(GL_CULL_FACE);

//				  a = x_step , 0,                z - previous_x_z)
//				  b = x_step , Y_step, z - previous_xy_z)



				  glBegin(GL_TRIANGLES);
//				  glNormal3f( 0 - ((z - previous_x_z)*(y_step)), ((z - previous_x_z)*x_step)-(x_step*(z - previous_xy_z)), (x_step*y_step) );
  		    	  glVertex3f(x,          y,          z            );
  		    	  glVertex3f(x - x_step, y,          previous_x_z );
  		    	  glVertex3f(x - x_step, y - y_step, previous_xy_z);
				  glEnd();
//
//				  glMaterialfv(GL_FRONT, GL_DIFFUSE, front_color);
//				  glMaterialfv(GL_BACK, GL_DIFFUSE, back_color);
				  glDisable(GL_CULL_FACE);
				  glBegin(GL_TRIANGLES);
//				  glNormal3f( ((z - previous_x_z)*(y_step)), ((z - previous_x_z)*x_step)-(x_step*(z - previous_xy_z)), (x_step*y_step) );
  		    	  glVertex3f(x,          y         , z            );
  		    	  glVertex3f(x - x_step, y - y_step, previous_xy_z);
  		    	  glVertex3f(x         , y - y_step, previous_y_z );
				  glEnd();

				  x += x_step;
				  j += 1;
			  }
			  y += y_step;
			  i += 1;
		  }


	}
}

void GLWidget::setModelVector(QVector< QVector<float> > data_vector, int max, int min){
	points = data_vector;

	float mod_max = (max > 0) ? max : -max;
	float mod_min = (min > 0) ? min : -min;
	if(mod_max > mod_min){
		max_value = mod_max;
	}else{
		max_value = mod_min;
	}
//	QMessageBox::information(0, "error", QString::number(points.size()));
//	QMessageBox::information(0, "error", QString::number((*points)[1]));
//	QMessageBox::information(0, "error", QString::number((*points)[2]));
	shouldpaint = true;
	paintGL();
	updateGL();
}


