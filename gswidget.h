#ifndef GSWIDGET_H
#define GSWIDGET_H

#include "gsobject.h"

class GSWidget : public GSObject
{
	Q_OBJECT
public:
	GSWidget(GSObject* parent);

	Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
	Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
	Q_PROPERTY(int xSpan READ xSpan WRITE setXSpan NOTIFY xSpanChanged)
	Q_PROPERTY(int ySpan READ ySpan WRITE setYSpan NOTIFY ySpanChanged)

	int x() const;
	int y() const;
	int xSpan() const;
	int ySpan() const;

public slots:
	void setX(int x);
	void setY(int y);
	void setXSpan(int xSpan);
	void setYSpan(int ySpan);

signals:
	void xChanged(int x);
	void yChanged(int y);
	void xSpanChanged(int xSpan);
	void ySpanChanged(int ySpan);

private:
	int mX;
	int mY;
	int mXSpan;
	int mYSpan;
};

#endif // GSWIDGET_H
