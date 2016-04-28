#ifndef GSLABEL_H
#define GSLABEL_H

#include "gswidget.h"

#include <QLabel>

class GSLabel : public GSWidget
{
	Q_OBJECT
public:
	GSLabel(GSObject* parent);

	Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)

	virtual QWidget *widget() const;
	virtual QString type() const;

	QString label() const;

public slots:
	void setLabel(QString label);

signals:
	void labelChanged(QString label);

private:
	QLabel* mLabel;
};

class GSLabelBuilder : public GSObjectBuilder {
public:
	virtual GSObject *makeObject(GSObject *parent) const;

protected:
	virtual GSObjectBuilder *clone() const;
};

#endif // GSLABEL_H
