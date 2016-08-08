#ifndef GSCOLUMN_H
#define GSCOLUMN_H

#include "gsobject.h"

class GSTable;

class GSColumn : public GSObject
{
	Q_OBJECT
public:
	GSColumn(GSObject* parent);

	virtual bool loadSource(SourceItem *item);

	Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged)
	Q_PROPERTY(int pos READ pos WRITE setPos NOTIFY posChanged)
	Q_PROPERTY(QString header READ header WRITE setHeader NOTIFY headerChanged)

	QVariant value() const;
	int pos() const;
	QString header() const;

public slots:
	void setValue(QVariant value);
	void setPos(int pos);
	void setHeader(QString header);

signals:
	void valueChanged(QVariant value);
	void posChanged(int pos);
	void headerChanged(QString header);

private:
	QVariantList mValue;
	int mPos;

	GSTable* mHost;
	QString mHeader;
};

DEFINE_GSCLASS(GSColumn, "column")

#endif // GSCOLUMN_H
