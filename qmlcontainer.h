#ifndef QMLCONTAINER_H
#define QMLCONTAINER_H

#include <QQuickWindow>

class QmlContainer
{
public:
	QmlContainer();

	QQuickWindow* window() const;
	void setItem(QQuickItem *item);

private:
	QQuickWindow* mWindow;
};

#endif // QMLCONTAINER_H
