/*
 * GLWidget.cpp
 *
 *  Created on: Nov 3, 2013
 *      Author: Misha
 */

#include "GLWidget.h"
#include <QMouseEvent>
#include <qmessagebox.h>
#include <QDebug>
#include <qmath.h>
#include <qrgb.h>



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

	gradient = false;
	draw_axes = false;

	drawtype = "lines";
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
	GLfloat light0Position[]={-90,-90,40,1};
	glLightfv(GL_LIGHT0,GL_POSITION,light0Position);

	//Defining "diffuse" lighting properties for GL_LIGHT0
	GLfloat light0Diffuse[]={1,1,1};
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light0Diffuse);

	//Defining "specular" lighting properties for GL_LIGHT0
	GLfloat light0Specular[]={1,1,1};
	glLightfv(GL_LIGHT0,GL_SPECULAR,light0Specular);

	glEnable(GL_LIGHT0);

	glPointSize(1.8);
	scale = 1.0;
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

void GLWidget::wheelEvent(QWheelEvent* e){
	scale = scale + e->delta()/1500.0;
	if(scale > 4){
		scale = 4.0;
		e->ignore();
	}else if(scale < 0.4){
		scale = 0.4;
		e->ignore();
	}else{
		e->accept();
	}
	paintGL();
	updateGL();
}

void GLWidget::drawAxes(float bigger, boolean draw_x, boolean draw_y, boolean draw_z){
	if(draw_axes){
		GLfloat materialColor[] = { 1.0, 1.0, 1.0, 0.2 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, materialColor);
	//	glLineWidth(5.0f);

		float step = bigger/2;
		float glstep = (step)/bigger;

		if(draw_z){
			glBegin(GL_LINES);
				glVertex3f( -1, -1, -1);
				glVertex3f( -1, -1, 1);
			glEnd();

			float current_glvalue = -1.0;
			float current_value = -bigger;
			while(current_glvalue < 1.0){
				glBegin(GL_LINES);
					glVertex3f( -1, -1, current_glvalue);
					glVertex3f( -0.99, -0.99, current_glvalue);
				glEnd();
				_draw_text( -0.99, -0.99, current_glvalue, QString::number(round(current_value)), Qt::white);
				current_glvalue += glstep;
				current_value += step;
			}
			_draw_text( -1.0f, -1.0f, 1.0f, "Z(nm)", Qt::red);
		}

		if(draw_y){
			glBegin(GL_LINES);
				glVertex3f( -1, -1, -1);
				glVertex3f(  1, -1, -1);
			glEnd();

			float current_glvalue = -1.0;
			float current_value = -bigger;
			while(current_glvalue < 1.0){
				glBegin(GL_LINES);
					glVertex3f( current_glvalue, -1, -1);
					glVertex3f( current_glvalue, -0.99, -0.99);
				glEnd();
				_draw_text( current_glvalue, -0.99, -0.99, QString::number(round(current_value)), Qt::white);
				current_glvalue += glstep;
				current_value += step;
			}
			_draw_text( 1.0f, -1.0f, -1.0f, "Y(nm)", Qt::red);
		}

		if(draw_x){
			glBegin(GL_LINES);
				glVertex3f( -1, -1, -1);
				glVertex3f( -1, 1, -1);
			glEnd();

			float current_glvalue = -1.0;
			float current_value = -bigger;
			while(current_glvalue < 1.0){
				glBegin(GL_LINES);
					glVertex3f( -1, current_glvalue, -1);
					glVertex3f( -0.99, current_glvalue, -0.99);
				glEnd();
				_draw_text( -0.99, current_glvalue, -0.99, QString::number(round(current_value)), Qt::white);
				current_glvalue += glstep;
				current_value += step;
			}
			_draw_text( -1.0f, 1.0f, -1.0f, "X(nm)", Qt::red);
		}


	//draw grid
		GLfloat materialColor2[] = { 0.4, 0.4, 0.4, 0.2 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, materialColor2);
	//	x0-axe
		glBegin(GL_LINES);
			glVertex3f( -1, -1, 0);
			glVertex3f(  1, -1, 0);
		glEnd();
	//	y0-axe
		glBegin(GL_LINES);
			glVertex3f( -1, -1, 0);
			glVertex3f( -1, 1, 0);
		glEnd();

		glBegin(GL_LINES);
			glVertex3f(  1,  1, 0);
			glVertex3f(  1, -1, 0);
		glEnd();
	//	y0-axe
		glBegin(GL_LINES);
			glVertex3f( -1, 1, 0);
			glVertex3f(  1, 1, 0);
		glEnd();

	}
}

void GLWidget::draw(){
	if(shouldpaint){
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.0, 0.0, -10.0);

		glPushMatrix();
		glMultMatrixf(Transform.M);
		glScalef( scale, scale, scale);

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

		glDisable(GL_CULL_FACE);

		float ambient[4] = {0.5, 0.5, 0.5, 1};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);


		GLfloat specularity = 0.1f;
		GLfloat emissivity = 0.05f;
		int shininess = 0;
		//The specular (shiny) component of the material
		GLfloat materialSpecular[] = {specularity, specularity, specularity, 1.0f};
		//The color emitted by the material
		GLfloat materialEmission[] = {emissivity, emissivity, emissivity, 1.0f};

		//The color of the sphere
		if(!gradient){
			GLfloat materialColor[] = { color.redF(), color.greenF(), color.blueF(), color.alphaF() };
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, materialColor);
		}
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, materialEmission);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess); //The shininess parameter


		if(isDAT){
			drawDAT();
		}else{
			drawCSV();
		}
		glPopMatrix();
	}
}

void GLWidget::setModelVector(QVector< QVector<float> > data_vector, float maxx, float minx, float maxy, float miny, float maxz, float minz, float d_x, float d_y){
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
	shouldpaint = true;
	paintGL();
	updateGL();
}


void GLWidget::setDATModelVector(QVector< QVector<float> > data_vector, float max, float maxy){
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
		float current_x = -1;
		while(j < data_vector[i].size()){
			int index = nearestIndex(current_x, data_vector[i]);

			calculated_points[i].push_back( ((data_vector[i][index]/max)*2) - 1);
			calculated_points[i+1].push_back( (data_vector[i + 1][index]/max) - 1);

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
	float max_x_mod = abs(max_x);
	float min_x_mod = abs(min_x);
	float max_y_mod = abs(max_y);
	float min_y_mod = abs(min_y);
	float max_z_mod = abs(max_z);
	float min_z_mod = abs(min_z);

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

	  float y = fit_to_size((i * y_step) - 1.0);

	  for(int j = 1; j < points[i].size(); j++){

		  float x = fit_to_size((j * x_step) - 1.0);

		  float z = 0.0;
		  if(i < points.size() && j < points[0].size()){
			  z = fit_to_size((points[i][j])/bigger);
		  }

		  float previous_x_z = z;
		  if(i < points.size() && (j - 1) < points[0].size()){
			  previous_x_z = fit_to_size((points[i][j - 1])/bigger);
		  }

		  float previous_y_z = z;
		  if((i - 1) < points.size() && j < points[0].size()){
			  previous_y_z = fit_to_size((points[i - 1][j])/bigger);
		  }

		  float previous_xy_z = z;
		  if((i - 1) < points.size() && (j - 1) < points[0].size()){
			  previous_xy_z = fit_to_size((points[i - 1][j - 1])/bigger);
		  }

			if(gradient){
				GLfloat h = abs(z);
				GLfloat materialColor[] = { h, 0, 1.0 - h, 1 };
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, materialColor);
			}

		  glBegin(GL_TRIANGLES);
		  glNormal3f( 0 - ((z - previous_x_z)*(y_step)), ((z - previous_x_z)*x_step)-(x_step*(z - previous_xy_z)), (x_step*y_step) );
		  glVertex3f(x,          y,          z            );
		  glVertex3f(x - x_step, y,          previous_x_z );
		  glVertex3f(x - x_step, y - y_step, previous_xy_z);
		  glEnd();

		  glBegin(GL_TRIANGLES);
		  glNormal3f( 0 - ((z - previous_x_z)*(y_step)), ((z - previous_x_z)*x_step)-(x_step*(z - previous_xy_z)), (x_step*y_step) );
		  glVertex3f(x,          y         , z            );
		  glVertex3f(x - x_step, y - y_step, previous_xy_z);
		  glVertex3f(x         , y - y_step, previous_y_z );
		  glEnd();

	  }
	}

	drawAxes(bigger, true, true, true);
}


void GLWidget::drawDAT(){

	float bigger = 0;
	float max_x_mod = abs(max_x);
	float min_x_mod = abs(min_x);
	float max_y_mod = abs(max_y);
	float min_y_mod = abs(min_y);
	float max_z_mod = abs(max_z);
	float min_z_mod = abs(min_z);

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

	if(QString::compare(drawtype, "lines") == 0){
		glLineWidth(5.0f);
		float step_y = 2.0/(points.size()/2);

		float current_y = step_y - 1.0;
		int i = 2;
		while(i < points.size()){
			int j = 1;
			while(j < points[i].size()){

				float x = fit_to_size(points[i][j]);
				float y = fit_to_size(current_y);
				float z = fit_to_size((points[i+1][j] * max_x)/max_y);

				float prev_x    = fit_to_size(points[i][j-1]);
				float prev_x_z  = fit_to_size((points[i+1][j-1]*max_x)/max_y);
				float prev_y_z  = fit_to_size((points[i-1][j]*max_x)/max_y);
				float prev_y    = fit_to_size(current_y - step_y);
				float prev_xy_z = fit_to_size((points[i-1][j-1]*max_x)/max_y);

				if(gradient){
					GLfloat h = abs(z);
					GLfloat materialColor[] = { h, 0, 1.0 - h, 1 };
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, materialColor);
				}

				glBegin(GL_LINES);
					glVertex3f(x,      y,       z        );
					glVertex3f(prev_x, y,       prev_x_z );
				glEnd();

				j++;
			}
			current_y = current_y + step_y;
			i = i+2;
		}
	}else{
		float step_y = 2.0/(points.size()/2);

		float current_y = step_y - 1.0;
		int i = 2;
		while(i < points.size()){
			int j = 1;
			while(j < points[i].size()){

				float x = fit_to_size(points[i][j]);
				float y = fit_to_size(current_y);
				float z = fit_to_size((points[i+1][j] * max_x)/max_y);

				float prev_x    = fit_to_size(points[i][j-1]);
				float prev_x_z  = fit_to_size((points[i+1][j-1]*max_x)/max_y);
				float prev_y_z  = fit_to_size((points[i-1][j]*max_x)/max_y);
				float prev_y    = fit_to_size(current_y - step_y);
				float prev_xy_z = fit_to_size((points[i-1][j-1]*max_x)/max_y);

				if(gradient){
					GLfloat h = abs(z);
					GLfloat materialColor[] = { h, 0, 1.0 - h, 1 };
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, materialColor);
				}

				glBegin(GL_TRIANGLES);
					glNormal3f( (0)-((prev_x_z - z)*(prev_y -y)), ((prev_x_z - z)*(prev_x -x))-((prev_x - x)*(prev_xy_z - z)) ,((prev_x - x)*(prev_y -y))-(0) );
					glVertex3f(x,      y,       z        );
					glVertex3f(prev_x, y,       prev_x_z );
					glVertex3f(prev_x, prev_y,  prev_xy_z);
				glEnd();

				glBegin(GL_TRIANGLES);
					glNormal3f( (0)-((prev_x_z - z)*(prev_y -y)), ((prev_x_z - z)*(prev_x -x))-((prev_x - x)*(prev_xy_z - z)) ,((prev_x - x)*(prev_y -y))-(0) );
					glVertex3f(x,      y,      z        );
					glVertex3f(prev_x, prev_y, prev_xy_z);
					glVertex3f(x,      prev_y, prev_y_z );
				glEnd();

				j++;
			}
			current_y = current_y + step_y;
			i = i+2;
		}
	}

	glLineWidth(1.0f);
	drawAxes(bigger, false, true, true);
}


int GLWidget::nearestIndex(float value, QVector<float> data_array){
	int index = 0;
	float last_difference = abs(value - data_array[0]);
	int i = 1;
	while(i < data_array.size()){
		float difference = abs(value - data_array[i]);
		if(difference < last_difference){
			last_difference = difference;
			index = i;
		}
		i++;
	}
	return index;
}

float GLWidget::abs(float number){
    if (number < 0)
        return -number;
    else
        return number;
}

float GLWidget::fit_to_size(float number){
	if(number < -1){
		return -1.0;
	}else if(number > 1){
		return 1.0;
	}else{
		return number;
	}
}

void GLWidget::_draw_text(double x, double y, double z, QString txt, QColor color)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    qglColor(color);
    renderText(x, y, z, txt, QFont("Arial", 10, QFont::Bold, false) );
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

