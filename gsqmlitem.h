#ifndef GSQMLITEM_H
#define GSQMLITEM_H

#include "gswidget.h"

#include <QQuickItem>
#include <QQuickWindow>

class GSQmlItem : public GSWidget
{
	Q_OBJECT
public:
	GSQmlItem(GSObject* parent = NULL);
	virtual QWidget* widget() const;
	virtual QObject* object();
	virtual QObject* object() const;
	virtual void setGSProperty(const QString &name, const QVariant &value);

protected:
	virtual bool setContents(const QString &contents);

private:
	QQuickItem* mItem;
	QQuickWindow* mQml;
	QWidget* mWidget;
};

DEFINE_GSCLASS(GSQmlItem, "qml")

#endif // GSQMLITEM_H
