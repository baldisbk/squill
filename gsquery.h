#ifndef GSQUERY_H
#define GSQUERY_H

#include "gsobject.h"

class GSQuery : public GSObject
{
	Q_OBJECT
public:
	GSQuery(GSObject* parent);
	Q_PROPERTY(QString query READ query WRITE setQuery NOTIFY queryChanged)
	Q_PROPERTY(QString database READ database WRITE setDatabase NOTIFY databaseChanged)

	virtual QString type() const;

	QString query() const;
	QString database() const;

public slots:
	void exec();
	void setQuery(QString query);

	void setDatabase(QString database);

signals:
	void queryChanged(QString query);
	void databaseChanged(QString database);

protected:
	virtual bool setContents(const QString &contents);

private:
	QString mQuery;
	QString mDatabase;
};


class GSQueryBuilder : public GSObjectBuilder {
public:
	virtual GSObject *makeObject(GSObject *parent) const;

protected:
	virtual GSObjectBuilder *clone() const;
};

#endif // GSQUERY_H
