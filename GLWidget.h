/*
 * GLWidget.h
 *
 *  Created on: Nov 3, 2013
 *      Author: Misha
 */

#ifndef GLWIDGET_H_
#define GLWIDGET_H_

#include <QGLWidget>

class GLWidget : public QGLWidget {
	Q_OBJECT
public:
	explicit GLWidget(QWidget *parent = 0);
	void initializeGL();
	void paintGL();
	void resizeGL(int w, int h);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void setModelVector(QVector< QVector<float> > data_vector, int max_x, int min_x, int max_y, int min_y, int max_z, int min_z, float dx, float dz, QString drawtype);

private:
	QString drawtype;
	void draw();
	void drawAxes();
	int faceAtPosition(const QPoint &pos);
	GLfloat rotationX;
	GLfloat rotationY;
	GLfloat rotationZ;
	QColor faceColors[6];
	QPoint lastPos;
	QVector<QVector <float> > points;
	float max_x;
	float min_x;
	float max_y;
	float min_y;
	float max_z;
	float min_z;
	float dx;
	float dy;
	float shouldpaint;

};

#endif /* GLWIDGET_H_ */
