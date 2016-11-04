#include "gsqmlitem.h"

#include <QQmlContext>

#include "qmlcontainer.h"

GSQmlItem::GSQmlItem(GSObject *parent) : GSObject(parent), mItem(NULL)
{
}

QObject *GSQmlItem::object()
{
	return mItem;
}

QObject *GSQmlItem::object() const
{
	return mItem;
}

bool GSQmlItem::setContents(const QString &contents)
{
	QQmlComponent component(qmlContext()->engine());
	component.setData(contents.toUtf8(), QUrl());
	mItem = qobject_cast<QQuickItem*>(component.create(qmlContext()));
	if (mItem)
		mItem->setObjectName(name());

	return mItem != NULL;
}

QQuickItem *GSQmlItem::item() const
{
	return mItem;
}

bool GSQmlItem::loadSource(SourceItem *item)
{
	if (!GSObject::loadSource(item))
		return false;
	QmlContainer* host = dynamic_cast<QmlContainer*>(gsParent());
	if (host && mItem)
		host->setItem(mItem);
	return true;
}
