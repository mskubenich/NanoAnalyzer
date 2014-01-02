/*
 * GLWidget.h
 *
 *  Created on: Nov 3, 2013
 *      Author: Misha
 */

#ifndef GLWIDGET_H_
#define GLWIDGET_H_

#include <QGLWidget>
#include "ArcBall.h"

class GLWidget : public QGLWidget {
	Q_OBJECT
public:
	explicit GLWidget(QWidget *parent = 0);
	void initializeGL();
	void paintGL();
	void resizeGL(int w, int h);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent* event);
	void setModelVector(QVector< QVector<float> > data_vector, float max_x, float min_x, float max_y, float min_y, float max_z, float min_z, float dx, float dy);
	void setDATModelVector(QVector< QVector<float> > data_vector, float max, float maxy);

	void drawCSV();
	void drawDAT();
	void _draw_text(double x, double y, double z, QString txt, QColor color);

	QColor color;
	bool gradient;
	GLfloat scale;
	bool draw_axes;
	QString drawtype;

private:
	void draw();
	void drawAxes(float bigger, boolean draw_x, boolean draw_y, boolean draw_z);
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

	bool isDAT;

	float abs(float number);
	int nearestIndex(float value, QVector<float> data_array);
	float fit_to_size(float number);

	Matrix4fT Transform;
	Matrix3fT LastRot;
	Matrix3fT ThisRot;
	ArcBallT* arc_ball;
	Point2fT MousePt;
};

#endif /* GLWIDGET_H_ */
