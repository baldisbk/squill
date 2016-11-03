#include "gswidget.h"

GSWidget::GSWidget(GSObject *parent):
	GSObject(parent), mX(-1), mY(-1), mXSpan(1), mYSpan(1)
{
}

int GSWidget::x() const
{
	return mX;
}

int GSWidget::y() const
{
	return mY;
}

int GSWidget::xSpan() const
{
	return mXSpan;
}

int GSWidget::ySpan() const
{
	return mYSpan;
}

GSWidget *GSWidget::parentWidget() const
{
	return qobject_cast<GSWidget*>(gsParent());
}

void GSWidget::setX(int x)
{
	if (mX == x)
		return;

	mX = x;
	if (widget() && mY != -1 && parentWidget())
		parentWidget()->addWidget(widget(), x, y(), xSpan(), ySpan());
	emit xChanged(x);
}

void GSWidget::setY(int y)
{
	if (mY == y)
		return;

	mY = y;
	if (widget() && mX != -1 && parentWidget())
		parentWidget()->addWidget(widget(), x(), y, xSpan(), ySpan());
	emit yChanged(y);
}

void GSWidget::setXSpan(int xSpan)
{
	if (mXSpan == xSpan)
		return;

	mXSpan = xSpan;
	if (widget() && mX != -1 && mY != -1 && parentWidget())
		parentWidget()->addWidget(widget(), x(), y(), xSpan, ySpan());
	emit xSpanChanged(xSpan);
}

void GSWidget::setYSpan(int ySpan)
{
	if (mYSpan == ySpan)
		return;

	mYSpan = ySpan;
	if (widget() && mX != -1 && mY != -1 && parentWidget())
		parentWidget()->addWidget(widget(), x(), y(), xSpan(), ySpan);
	emit ySpanChanged(ySpan);
}

QWidget *GSWidget::widget() const
{
	return NULL;
}

bool GSWidget::addWidget(
	QWidget */*widget*/,
	int /*x*/, int /*y*/,
	int /*xspan*/, int /*yspan*/)
{
	return false;
}
