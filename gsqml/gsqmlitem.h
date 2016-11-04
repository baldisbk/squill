#ifndef GSQMLITEM_H
#define GSQMLITEM_H

#include <gswidget.h>

#include <QQuickItem>

class GSQmlItem : public GSObject
{
	Q_OBJECT
public:
	GSQmlItem(GSObject* parent = NULL);
	virtual QObject* object();
	virtual QObject* object() const;
	virtual bool loadSource(SourceItem *item);

	QQuickItem *item() const;

protected:
	virtual bool setContents(const QString &contents);

private:
	QQuickItem* mItem;
};

DEFINE_GSCLASS(GSQmlItem, "qml")

#endif // GSQMLITEM_H
