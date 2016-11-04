#ifndef GSQMLWIDGET_H
#define GSQMLWIDGET_H

#include <gswidget.h>
#include "qmlcontainer.h"

#include <QQuickItem>
#include <QQuickWindow>

class GSQmlItem;

class GSQmlWidget : public GSWidget, public QmlContainer
{
	Q_OBJECT
public:
	GSQmlWidget(GSObject* parent = NULL);
	virtual QWidget* widget() const;

private:
	QWidget* mWidget;
};

DEFINE_GSCLASS(GSQmlWidget, "qmlwidget")

#endif // GSQMLWIDGET_H
