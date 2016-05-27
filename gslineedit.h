#ifndef GSLINEEDIT_H
#define GSLINEEDIT_H

#include "gswidget.h"

#include <QLineEdit>

class GSLineEdit : public GSWidget
{
	Q_OBJECT
public:
	GSLineEdit(GSObject* parent);

	Q_PROPERTY(QVariant text READ text WRITE setText NOTIFY textChanged)

	virtual QString type() const;
	virtual QWidget *widget() const;

	QVariant text() const;

public slots:
	void setText(QVariant text);
	void setText(QString text);

signals:
	void textChanged(QVariant text);

private slots:
	void transformTextSignal(QString value);

private:
	QLineEdit* mEdit;
	QString m_text;
};

class GSLineEditBuilder : public GSObjectBuilder {
public:
	virtual GSObject *makeObject(GSObject *parent) const;

protected:
	virtual GSObjectBuilder *clone() const;
};

#endif // GSLINEEDIT_H
