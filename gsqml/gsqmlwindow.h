#ifndef GSQMLWINDOW_H
#define GSQMLWINDOW_H

#include <gsobject.h>
#include "qmlcontainer.h"

#include <QQuickItem>
#include <QQuickWindow>

class GSQmlItem;

class GSQmlWindow : public GSObject, public QmlContainer
{
	Q_OBJECT
public:
	GSQmlWindow(GSObject* parent = NULL);
	virtual bool loadSource(SourceItem *item);
};

DEFINE_GSCLASS(GSQmlWindow, "qmlwindow")

#endif // GSQMLWINDOW_H
