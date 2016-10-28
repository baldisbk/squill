#include "gsqmlwidget.h"

#include <QWidget>

GSQmlWidget::GSQmlWidget(GSObject* parent): GSWidget(parent)
{
	mWidget = QWidget::createWindowContainer(window());
}

QWidget *GSQmlWidget::widget() const
{
	return mWidget;
}
