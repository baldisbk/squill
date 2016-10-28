#include "gsqmlwindow.h"

#include <QWidget>

GSQmlWindow::GSQmlWindow(GSObject* parent): GSObject(parent)
{
}

bool GSQmlWindow::loadSource(SourceItem *item)
{
	if (!GSObject::loadSource(item))
		return false;
	window()->show();
	return true;
}
