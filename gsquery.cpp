#include "gsquery.h"

#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>

#include "gscontext.h"

GSQuery::GSQuery(GSObject *parent): GSObject(parent)
{
}

bool GSQuery::setContents(const QString &contents)
{
	setQuery(contents);
	return true;
}

QString GSQuery::query() const
{
	return mQuery;
}

QString GSQuery::database() const
{
	return mDatabase;
}

void GSQuery::exec()
{
	if (!contextObject())
		return;
	QSqlDatabase db = QSqlDatabase::database(database());
	if (!db.isValid() || !db.isOpen())
		return;
	QSqlQuery q(db);
	q.exec(query());
	// TODO report error
	QSqlRecord rec = q.record();
	QStringList names;
	QList<QVariantList> res;
	for (int i = 0; i < rec.count(); ++i) {
		names.append(rec.fieldName(i));
		res.append(QVariantList());
	}
	while(q.next()) {
		for(int i = 0; i < names.size(); ++i)
			res[i].append(q.value(i));
	}
	for (int i = 0; i < names.size(); ++i)
		contextObject()->setGSProperty(names[i], res[i]);
}

void GSQuery::setQuery(QString query)
{
	if (mQuery == query)
		return;

	mQuery = query;
	emit queryChanged(query);
}

void GSQuery::setDatabase(QString database)
{
	if (mDatabase == database)
		return;

	mDatabase = database;
	emit databaseChanged(database);
}
