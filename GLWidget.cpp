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
#include <QDebug>
#include <qmath.h>


GLWidget::GLWidget(QWidget *parent) :
	QGLWidget(parent) {

	Matrix4fT init_transform =  { 1.0f, 0.0f, 0.0f, 0.0f,
								  0.0f, 1.0f, 0.0f, 0.0f,
								  0.0f, 0.0f, 1.0f, 0.0f,
								  0.0f, 0.0f, 0.0f, 1.0f};
	Transform = init_transform;
	Matrix3fT init_lastRot  = { 1.0f, 0.0f, 0.0f,
								 0.0f, 1.0f, 0.0f,
								 0.0f, 0.0f, 1.0f};
	LastRot = init_lastRot;
	Matrix3fT init_thisRot  = { 1.0f, 0.0f, 0.0f,
								 0.0f, 1.0f, 0.0f,
								 0.0f, 0.0f, 1.0f};
	ThisRot = init_thisRot;
	arc_ball = new ArcBallT(640.0f, 480.0f);

	shouldpaint = false;
	isDAT = false;
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

	arc_ball->setBounds((GLfloat)w, (GLfloat)h);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
	MousePt.s.X = event->x();
	MousePt.s.Y = event->y();

	LastRot = ThisRot;
	arc_ball->click(&MousePt);
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
	MousePt.s.X = event->x();
	MousePt.s.Y = event->y();

	Quat4fT ThisQuat;
	arc_ball->drag(&MousePt, &ThisQuat);
	Matrix3fSetRotationFromQuat4f(&ThisRot, &ThisQuat);
	Matrix3fMulMatrix3f(&ThisRot, &LastRot);
	Matrix4fSetRotationFromMatrix3f(&Transform, &ThisRot);

    updateGL();
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

		glPushMatrix();
		glMultMatrixf(Transform.M);

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

		if(isDAT){
			drawDAT();
		}else{
			drawCSV();
		}
		drawAxes();
		glPopMatrix();
	}
}

void GLWidget::setModelVector(QVector< QVector<float> > data_vector, float maxx, float minx, float maxy, float miny, float maxz, float minz, float d_x, float d_y, QString thedrawtype){
	drawtype = thedrawtype;
	points = data_vector;

	max_x = maxx;
	min_x = minx;
	max_y = maxy;
	min_y = miny;
	max_z = maxz;
	min_z = minz;
	dx = d_x;
	dy = d_y;
	isDAT = false;
//	QMessageBox::information(0, "error", QString::number(points.size()));
//	QMessageBox::information(0, "error", QString::number((*points)[1]));
//	QMessageBox::information(0, "error", QString::number((*points)[2]));
	shouldpaint = true;
	paintGL();
	updateGL();
}


void GLWidget::setDATModelVector(QVector< QVector<float> > data_vector, float max, float maxy, QString thedrawtype){
	drawtype = thedrawtype;

	QVector< QVector<float> > calculated_points = QVector< QVector<float> >();
	int i = 0;
	while(i < data_vector.size()){
		calculated_points.push_back(QVector<float>());
		i++;
	}

	float value_of_a_point = 2.0/data_vector[0].size();

	float step_x = (max*value_of_a_point);

	i = 0;
	while(i < data_vector.size()){
		int j = 0;
		float current_x = 0;
		while(j < data_vector[i].size()){
			int index = nearestIndex(current_x, data_vector[i]);

			calculated_points[i].push_back( (data_vector[i][index]/max)*2);
			calculated_points[i+1].push_back( (data_vector[i + 1][index]/max));
			qDebug() << "Hello";

			current_x = current_x + step_x;
			j++;
		}
		i = i + 2;
	}
	points = calculated_points;
	max_y = maxy;
	max_x = max;
	shouldpaint = true;
	isDAT = true;
	paintGL();
	updateGL();
}

void GLWidget::drawCSV(){
	float bigger = 0;
	float max_x_mod = max_x;
	if(max_x_mod < 0){
		max_x_mod = max_x_mod*(-1);
	}
	float min_x_mod = min_x;
	if(min_x_mod < 0){
		min_x_mod = max_x_mod*(-1);
	}
	float max_y_mod = max_y;
	if(max_y_mod < 0){
		max_y_mod = max_y_mod*(-1);
	}
	float min_y_mod = min_y;
	if(min_y_mod < 0){
		min_y_mod = max_y_mod*(-1);
	}
	float max_z_mod = max_z;
	if(max_z_mod < 0){
		max_z_mod = max_z_mod*(-1);
	}
	float min_z_mod = min_z;
	if(min_z_mod < 0){
		min_z_mod = max_z_mod*(-1);
	}

	if(max_x_mod > bigger){
		bigger = max_x_mod;
	}
	if(min_x_mod > bigger){
		bigger = min_x_mod;
	}
	if(max_y_mod > bigger){
		bigger = max_y_mod;
	}
	if(min_y_mod > bigger){
		bigger = min_y_mod;
	}
	if(max_z_mod > bigger){
		bigger = max_z_mod;
	}
	if(min_z_mod > bigger){
		bigger = min_z_mod;
	}

	float x_step = ((dx)*2.0/bigger);
	float y_step = ((dy)*2.0/bigger);

	for(int i = 1; i < points.size(); i++){

	  float y = (i * y_step) - 1.0;

		if(y < -1){
		  y = -1;
		  break;
	  }

	  for(int j = 1; j < points[i].size(); j++){


		  float x = (j * x_step) - 1.0;

		  float z = 0.0;
		  if(i < points.size() && j < points[0].size()){
			  z = ((points[i][j])/bigger);
		  }

		  if(z > 1){
			  z = 1;
		  }
		  if(z < -1){
			  z = -1;
			  break;
		  }
		  if(x > 1){
			  x = 1;
		  }
		  if(x < -1){
			  x = -1;
			  break;
		  }
		  if(y > 1){
			  y = 1;
		  }
		  if(y < -1){
			  y = -1;
			  break;
		  }

		  float previous_x_z = z;
		  if(i < points.size() && (j - 1) < points[0].size()){
			  previous_x_z = ((points[i][j - 1])/bigger);
		  }
		  if(previous_x_z > 1){
			  previous_x_z = 1;
		  }
		  if(previous_x_z < -1){
			  previous_x_z = -1;
		  }

		  float previous_y_z = z;
		  if((i - 1) < points.size() && j < points[0].size()){
			  previous_y_z = ((points[i - 1][j])/bigger);
		  }
		  if(previous_y_z > 1){
			  previous_y_z = 1;
		  }
		  if(previous_y_z < -1){
			  previous_y_z = -1;
		  }

		  float previous_xy_z = z;
		  if((i - 1) < points.size() && (j - 1) < points[0].size()){
			  previous_xy_z = ((points[i - 1][j - 1])/bigger);
		  }
		  if(previous_xy_z > 1){
			  previous_xy_z = 1;
		  }
		  if(previous_xy_z < -1){
			  previous_xy_z = -1;
		  }

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

	  }
	}
}


void GLWidget::drawDAT(){
	float step_y = 2.0/(points.size()/2);

	float current_y = step_y - 1.0;
	int i = 2;
	while(i < points.size()){
		int j = 1;
		while(j < points[i].size()){

			float x = points[i][j];
			if(x < -1){
				x = -1;
			}else if(x > 1){
				x = 1;
			}
			float y = current_y;
			if(y < -1){
				y = -1;
			}else if(y > 1){
				y = 1;
			}
			float z = (points[i+1][j] * max_x)/max_y;
			if(z < -1){
				z = -1;
			}else if(z > 1){
				z = 1;
			}

			float prev_x = points[i][j-1];
			if(prev_x < -1){
				prev_x = -1;
			}else if(prev_x > 1){
				prev_x = 1;
			}
			float prev_x_z = (points[i+1][j-1]*max_x)/max_y;
			if(prev_x_z < -1){
				prev_x_z = -1;
			}else if(prev_x_z > 1){
				prev_x_z = 1;
			}
			float prev_y_z = (points[i-1][j]*max_x)/max_y;
			if(prev_y_z < -1){
				prev_y_z = -1;
			}else if(prev_y_z > 1){
				prev_y_z = 1;
			}
			float prev_y = current_y - step_y;
			if(prev_y < -1){
				prev_y = -1;
			}else if(prev_y > 1){
				prev_y = 1;
			}
			float prev_xy_z = (points[i-1][j-1]*max_x)/max_y;
			if(prev_xy_z < -1){
				prev_xy_z = -1;
			}else if(prev_xy_z > 1){
				prev_xy_z = 1;
			}

//			a = (prev_x - x, 0,         prev_x_z - z)
//			b = (prev_x -x , prev_y -y, prev_xy_z - z)

			glBegin(GL_TRIANGLES);
				glNormal3f( (0)-((prev_x_z - z)*(prev_y -y)), ((prev_x_z - z)*(prev_x -x))-((prev_x - x)*(prev_xy_z - z)) ,((prev_x - x)*(prev_y -y))-(0) );
				glVertex3f(x     , y,          z            );
				glVertex3f(prev_x, y,          prev_x_z );
				glVertex3f(prev_x, prev_y,  prev_xy_z);
			glEnd();

			glBegin(GL_TRIANGLES);
			glNormal3f( (0)-((prev_x_z - z)*(prev_y -y)), ((prev_x_z - z)*(prev_x -x))-((prev_x - x)*(prev_xy_z - z)) ,((prev_x - x)*(prev_y -y))-(0) );
			glVertex3f(x,          y         , z            );
			glVertex3f(prev_x, prev_y, prev_xy_z);
			glVertex3f(x         , prev_y, prev_y_z );
			glEnd();

			j++;
		}
		current_y = current_y + step_y;
		i = i+2;
	}


//	QMessageBox::information(0, "error", QString::number(l_x));


}


int GLWidget::nearestIndex(float value, QVector<float> data_array){
	int index = 0;
	float last_difference = absolute(value - data_array[0]);
	int i = 1;
	while(i < data_array.size()){
		float difference = absolute(value - data_array[i]);
		if(difference < last_difference){
			last_difference = difference;
			index = i;
		}
		i++;
	}
	return index;
}

float GLWidget::absolute(float number){
    if (number < 0)
        return -number;
    else
        return number;
}

