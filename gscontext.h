#ifndef GSCONTEXT_H
#define GSCONTEXT_H

#include "gsobject.h"

class GSContext : public GSObject
{
	Q_OBJECT
public:
	GSContext(GSObject* parent, GSContext* parentCtx = NULL);

	void bindQmlContext(QQmlContext* context);
	void unbindQmlContext(QQmlContext* context);

private slots:
	void notifyQml(const QString& name, const QVariant &value);

private:
	QList<QQmlContext*> mContexts;
};

#endif // GSCONTEXT_H
