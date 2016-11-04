#ifndef GSMAINWINDOW_H
#define GSMAINWINDOW_H

#include <gswidget.h>

#include <QMainWindow>
#include <QGridLayout>
#include <QQmlEngine>

class GSMainWindow : public GSWidget
{
	Q_OBJECT
public:
	GSMainWindow(GSObject* parent = NULL);

	virtual QWidget *widget() const;
	virtual bool addWidget(QWidget *widget, int x, int y, int xspan, int yspan);
	virtual bool loadSource(SourceItem *item);

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

DEFINE_GSCLASS(GSMainWindow, "main")

#endif // GSMAINWINDOW_H
