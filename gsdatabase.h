#ifndef GSDATABASE_H
#define GSDATABASE_H

#include "gsobject.h"

#include <QtSql/QSqlDatabase>

class GSDatabase : public GSObject
{
	Q_OBJECT
public:
	GSDatabase(GSObject* parent);

	virtual QString type() const;

	Q_PROPERTY(QString dbName READ dbName WRITE setDbName NOTIFY dbNameChanged)
	Q_PROPERTY(QString dbHost READ dbHost WRITE setDbHost NOTIFY dbHostChanged)
	Q_PROPERTY(int dbPort READ dbPort WRITE setDbPort NOTIFY dbPortChanged)
	Q_PROPERTY(QString dbUser READ dbUser WRITE setDbUser NOTIFY dbUserChanged)
	Q_PROPERTY(QString dbPswd READ dbPswd WRITE setDbPswd NOTIFY dbPswdChanged)
	Q_PROPERTY(QString dbType READ dbType WRITE setDbType NOTIFY dbTypeChanged)

	QString dbName() const;
	QString dbHost() const;
	int dbPort() const;
	QString dbUser() const;
	QString dbPswd() const;
	QString dbType() const;

public slots:
	void open();

	void setDbName(QString dbName);
	void setDbHost(QString dbHost);
	void setDbPort(int dbPort);
	void setDbUser(QString dbUser);
	void setDbPswd(QString dbPswd);
	void setDbType(QString dbType);

signals:
	void dbNameChanged(QString dbName);
	void dbHostChanged(QString dbHost);
	void dbPortChanged(int dbPort);
	void dbUserChanged(QString dbUser);
	void dbPswdChanged(QString dbPswd);
	void dbTypeChanged(QString dbType);

private:
	QSqlDatabase mDatabase;
	QString mDBName;
	QString mDBHost;
	int mDBPort;
	QString mDBUser;
	QString mDBPswd;
	QString mDBType;
};


class GSDatabaseBuilder : public GSObjectBuilder {
public:
	virtual GSObject *makeObject(GSObject *parent) const;

protected:
	virtual GSObjectBuilder *clone() const;
};

#endif // GSDATABASE_H
