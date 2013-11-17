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
	glClearColor(0, 0, 0, 1);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);


	glLoadIdentity();
	//glOrtho(-50,50,-50,50,-2000,2000);
	gluPerspective(75,1,50,2000);

	glMatrixMode(GL_MODELVIEW);

	//Enabling the shading model
	glEnable(GL_LIGHTING);

	//Enabling normal vector normalization
	glEnable(GL_NORMALIZE);

	//Disabling global ambient light (In this example no ambient light will be present.)
	GLfloat globalAmbient[]={0,0,0};
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
//	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,globalAmbient);

	//Defining the position of the point light source GL_LIGHT0 at (x,y,z)=(0,0,40)
	GLfloat light0Position[]={-30,-30,90,1};
	glLightfv(GL_LIGHT0,GL_POSITION,light0Position);

	//Defining "diffuse" lighting properties for GL_LIGHT0
	GLfloat light0Diffuse[]={1,1,1};
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light0Diffuse);

	//Defining "specular" lighting properties for GL_LIGHT0
	GLfloat light0Specular[]={1,1,1};
	glLightfv(GL_LIGHT0,GL_SPECULAR,light0Specular);

	glEnable(GL_LIGHT0);
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

void GLWidget::drawAxes(){

	glPolygonMode(GL_BACK,GL_LINE);
	glPolygonMode(GL_FRONT,GL_LINE);
	glColor3f(0, 0, 1);
//	bottom
	glBegin(GL_POLYGON);
		glVertex3f(-1, -1, -1);
		glVertex3f( 1, -1, -1);
		glVertex3f( 1,  1, -1);
		glVertex3f(-1,  1, -1);
	glEnd();
//	front
	glBegin(GL_POLYGON);
		glVertex3f(-1,  1, -1);
		glVertex3f(-1,  1,  1);
		glVertex3f( 1,  1,  1);
		glVertex3f( 1,  1, -1);
	glEnd();
//	top
	glBegin(GL_POLYGON);
		glVertex3f(-1, -1,  1);
		glVertex3f( 1, -1,  1);
		glVertex3f( 1,  1,  1);
		glVertex3f(-1,  1,  1);
	glEnd();
	//	back
	glBegin(GL_POLYGON);
		glVertex3f(-1, -1, -1);
		glVertex3f( 1, -1, -1);
		glVertex3f( 1, -1,  1);
		glVertex3f(-1, -1,  1);
	glEnd();
	//	xy
	glBegin(GL_POLYGON);
		glVertex3f(-1, -1, 0);
		glVertex3f( 1, -1, 0);
		glVertex3f( 1,  1, 0);
		glVertex3f(-1,  1, 0);
	glEnd();


}

void GLWidget::draw(){
	if(shouldpaint){

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.0, 0.0, -10.0);
		glRotatef(rotationX, 1.0, 0.0, 0.0);
		glRotatef(rotationY, 0.0, 1.0, 0.0);
		glRotatef(rotationZ, 0.0, 0.0, 1.0);

		if(QString::compare(drawtype, "points") == 0){
			glPolygonMode(GL_BACK,GL_POINT);
			glPolygonMode(GL_FRONT,GL_POINT);
		}
		if(QString::compare(drawtype, "lines") == 0){
			glPolygonMode(GL_BACK,GL_LINE);
			glPolygonMode(GL_FRONT,GL_LINE);
		}
		if(QString::compare(drawtype, "shade") == 0){
			glPolygonMode(GL_BACK,GL_FILL);
			glPolygonMode(GL_FRONT,GL_FILL);
		}

		glColor3f(0, 1, 0);

		glDisable(GL_CULL_FACE);

		float ambient[4] = {0.5, 0.5, 0.5, 1};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);


		float x_interval = max_x - min_x;
		float y_interval = max_y - min_y;
		float z_interval = max_z - min_z;

		if(x_interval < 0){
			x_interval = x_interval * (-1);
		}
		if(y_interval < 0){
			y_interval = y_interval * (-1);
		}
		if(z_interval < 0){
			z_interval = z_interval * (-1);
		}

		float bigger = x_interval;
		if(y_interval > bigger){
			bigger = y_interval;
		}
		if(z_interval > bigger){
			bigger = z_interval;
		}

		float x_step = ((dx*bigger)/2) - 1 + min_x;
		float y_step = ((dy*bigger)/2) - 1 + min_y;

		float y = y_step - 1;
		int i = 1;
		while(y < 1){
		  float x = x_step - 1;
		  int j = 1;
		  while(x < 1){

			  float z = 0.0;
			  if(i < points.size() && j < points[0].size()){
				  z = ((points[i][j]*bigger)/2) - 1 + min_z;
			  }
			  if(z > 1){
				  z = 1;
			  }
			  if(z < -1){
				  z = -1;
			  }

			  float previous_x_z = z;
			  if(i < points.size() && (j - 1) < points[0].size()){
				  previous_x_z = ((points[i][j - 1]*bigger)/2) - 1 + min_z;
			  }
			  if(previous_x_z > 1){
				  previous_x_z = 1;
			  }
			  if(previous_x_z < -1){
				  previous_x_z = -1;
			  }

			  float previous_y_z = z;
			  if((i - 1) < points.size() && j < points[0].size()){
				  previous_y_z = ((points[i - 1][j]*bigger)/2) - 1 + min_z;
			  }
			  if(previous_y_z > 1){
				  previous_y_z = 1;
			  }
			  if(previous_y_z < -1){
				  previous_y_z = -1;
			  }

			  float previous_xy_z = z;
			  if((i - 1) < points.size() && (j - 1) < points[0].size()){
				  previous_xy_z = ((points[i - 1][j - 1]*bigger)/2) - 1 + min_z;
			  }
			  if(previous_xy_z > 1){
				  previous_xy_z = 1;
			  }
			  if(previous_xy_z < -1){
				  previous_xy_z = -1;
			  }


		//				  a = x_step , 0,                z - previous_x_z)
		//				  b = x_step , Y_step, z - previous_xy_z)


			  glBegin(GL_TRIANGLES);
			  glNormal3f( 0 - ((z - previous_x_z)*(y_step)), ((z - previous_x_z)*x_step)-(x_step*(z - previous_xy_z)), (x_step*y_step) );
			  glVertex3f(x,          y,          z            );
			  glVertex3f(x - x_step, y,          previous_x_z );
			  glVertex3f(x - x_step, y - y_step, previous_xy_z);
			  glEnd();

			  glBegin(GL_TRIANGLES);
		//				  glNormal3f( ((z - previous_x_z)*(y_step)), ((z - previous_x_z)*x_step)-(x_step*(z - previous_xy_z)), (x_step*y_step) );
		//				  glNormal3f( 0 - ((z - previous_x_z)*(y_step)), ((z - previous_x_z)*x_step)-(x_step*(z - previous_xy_z)), (x_step*y_step) );
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

		//		  drawAxes();
	}
}

void GLWidget::setModelVector(QVector< QVector<float> > data_vector, int maxx, int minx, int maxy, int miny, int maxz, int minz, float d_x, float d_z, QString thedrawtype){
	drawtype = thedrawtype;
	points = data_vector;

	max_x = maxx;
	min_x = minx;
	max_x = maxy;
	min_x = miny;
	max_x = maxz;
	min_x = minz;
	dx = d_x;
	dx = dy;
//	QMessageBox::information(0, "error", QString::number(points.size()));
//	QMessageBox::information(0, "error", QString::number((*points)[1]));
//	QMessageBox::information(0, "error", QString::number((*points)[2]));
	shouldpaint = true;
	paintGL();
	updateGL();
}



