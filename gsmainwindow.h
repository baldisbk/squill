#ifndef GSMAINWINDOW_H
#define GSMAINWINDOW_H

#include "gsobject.h"

#include <QMainWindow>
#include <QGridLayout>
#include <QQmlEngine>

class GSMainWindow : public GSObject
{
	Q_OBJECT
public:
	GSMainWindow(GSObject* parent = NULL);

	virtual QWidget *widget() const;
	virtual bool addWidget(QWidget *widget, int x, int y, int xspan, int yspan);
	virtual QString type() const;

public slots:
	void run();

signals:
	void shown();

protected:
	virtual QQmlContext *makeRootQmlContext();
	virtual GSContext *makeContext(GSContext *parent);

private:
	QMainWindow* mMW;
	QGridLayout* mGrid;
	QQmlEngine mEngine;
};

#endif // GSMAINWINDOW_H
