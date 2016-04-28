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

void GSWidget::setX(int x)
{
	if (mX == x)
		return;

	mX = x;
	if (widget() && mY != -1)
		parent()->addWidget(widget(), this->x(), y(), xSpan(), ySpan());
	emit xChanged(x);
}

void GSWidget::setY(int y)
{
	if (mY == y)
		return;

	mY = y;
	if (widget() && mX != -1)
		parent()->addWidget(widget(), x(), this->y(), xSpan(), ySpan());
	emit yChanged(y);
}

void GSWidget::setXSpan(int xSpan)
{
	if (mXSpan == xSpan)
		return;

	mXSpan = xSpan;
	if (widget() && mX != -1 && mY != -1)
		parent()->addWidget(widget(), x(), y(), this->xSpan(), ySpan());
	emit xSpanChanged(xSpan);
}

void GSWidget::setYSpan(int ySpan)
{
	if (mYSpan == ySpan)
		return;

	mYSpan = ySpan;
	if (widget() && mX != -1 && mY != -1)
		parent()->addWidget(widget(), x(), y(), xSpan(), this->ySpan());
	emit ySpanChanged(ySpan);
}

