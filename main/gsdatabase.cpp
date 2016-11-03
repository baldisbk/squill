#include "gsdatabase.h"

GSDatabase::GSDatabase(GSObject *parent): GSObject(parent)
{
}

QString GSDatabase::dbName() const
{
	return mDBName;
}

QString GSDatabase::dbHost() const
{
	return mDBHost;
}

int GSDatabase::dbPort() const
{
	return mDBPort;
}

QString GSDatabase::dbUser() const
{
	return mDBUser;
}

QString GSDatabase::dbPswd() const
{
	return mDBPswd;
}

QString GSDatabase::dbType() const
{
	return mDBType;
}

void GSDatabase::open()
{
	if (QSqlDatabase::contains(name()) && mDatabase.isOpen())
		return;
	QSqlDatabase::removeDatabase(name());
	mDatabase = QSqlDatabase::addDatabase(dbType(), name());
	mDatabase.setDatabaseName(dbName());
	mDatabase.setHostName(dbHost());
	mDatabase.setPort(dbPort());
	mDatabase.open(dbUser(), dbPswd());
}

void GSDatabase::setDbName(QString dbName)
{
	if (mDBName == dbName)
		return;

	mDBName = dbName;
	emit dbNameChanged(dbName);
}

void GSDatabase::setDbHost(QString dbHost)
{
	if (mDBHost == dbHost)
		return;

	mDBHost = dbHost;
	emit dbHostChanged(dbHost);
}

void GSDatabase::setDbPort(int dbPort)
{
	if (mDBPort == dbPort)
		return;

	mDBPort = dbPort;
	emit dbPortChanged(dbPort);
}

void GSDatabase::setDbUser(QString dbUser)
{
	if (mDBUser == dbUser)
		return;

	mDBUser = dbUser;
	emit dbUserChanged(dbUser);
}

void GSDatabase::setDbPswd(QString dbPswd)
{
	if (mDBPswd == dbPswd)
		return;

	mDBPswd = dbPswd;
	emit dbPswdChanged(dbPswd);
}

void GSDatabase::setDbType(QString dbType)
{
	if (mDBType == dbType)
		return;

	mDBType = dbType;
	emit dbTypeChanged(dbType);
}
