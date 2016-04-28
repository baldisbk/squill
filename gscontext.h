#ifndef GSCONTEXT_H
#define GSCONTEXT_H

#include "gsobject.h"

class GSContext : public GSObject
{
	Q_OBJECT
public:
	GSContext();
	//GSContext(GSContext* parent);

	void bindQmlContext(QQmlContext* context);
	void unbindQmlContext(QQmlContext* context);

	// GSObject interface
public:
	virtual QString type() const;
	virtual bool setContents(const QString &contents);

private slots:
	void notifyQml(const QString& name);

private:
	QList<QQmlContext*> mContexts;
};

#endif // GSCONTEXT_H
