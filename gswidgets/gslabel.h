#ifndef GSLABEL_H
#define GSLABEL_H

#include <gswidget.h>

#include <QLabel>

class GSLabel : public GSWidget
{
	Q_OBJECT
public:
	GSLabel(GSObject* parent);

	Q_PROPERTY(QVariant label READ label WRITE setLabel NOTIFY labelChanged)

	virtual QWidget *widget() const;

	QVariant label() const;

public slots:
	void setLabel(QVariant label);

signals:
	void labelChanged(QVariant label);

private:
	QLabel* mLabel;
};

DEFINE_GSCLASS(GSLabel, "label")

#endif // GSLABEL_H
