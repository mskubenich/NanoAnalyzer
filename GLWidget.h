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
//	void mouseDoubleClickEvent(QMouseEvent *event);
	void setModelVector(QVector<float> *data_vector);

private:
	void draw();
	int faceAtPosition(const QPoint &pos);
	GLfloat rotationX;
	GLfloat rotationY;
	GLfloat rotationZ;
	QColor faceColors[6];
	QPoint lastPos;
};

#endif /* GLWIDGET_H_ */
