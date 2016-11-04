#include "qmlcontainer.h"

#include "gsqmlitem.h"

QmlContainer::QmlContainer()
{
	mWindow = new QQuickWindow();
}

QQuickWindow *QmlContainer::window() const
{
	return mWindow;
}

void QmlContainer::setItem(QQuickItem *item)
{
	item->setParentItem(mWindow->contentItem());
}

