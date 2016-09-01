#include "gsqmlitem.h"

#include <QWidget>
#include <QQmlContext>

GSQmlItem::GSQmlItem(GSObject *parent) : GSWidget(parent), mItem(NULL)
{
	mQml = new QQuickWindow();
	mWidget = QWidget::createWindowContainer(mQml);
}

QWidget *GSQmlItem::widget() const
{
	return mWidget;
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
	if (mItem) {
		mItem->setParentItem(mQml->contentItem());
		mItem->setObjectName(name());
	}

	return mItem != NULL;
}


void GSQmlItem::setGSProperty(const QString &name, const QVariant &value)
{
	if (name == "x")
		setX(gsToScalar(value).toInt());
	else if (name == "y")
		setY(gsToScalar(value).toInt());
	else
		GSWidget::setGSProperty(name, value);
}
