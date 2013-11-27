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
	void setModelVector(QVector< QVector<float> > data_vector, float max_x, float min_x, float max_y, float min_y, float max_z, float min_z, float dx, float dy, QString drawtype);
	void setDATModelVector(QVector< QVector<float> > data_vector, float max, float maxy, QString drawtype);

	void drawCSV();
	void drawDAT();

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
	float absolute(float number);
	float max_x;
	float min_x;
	float max_y;
	float min_y;
	float max_z;
	float min_z;
	float dx;
	float dy;
	float shouldpaint;

	bool isDAT;

	int nearestIndex(float value, QVector<float> data_array);
};

#endif /* GLWIDGET_H_ */
