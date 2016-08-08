#include "gscontext.h"

#include <QQmlContext>

GSContext::GSContext(GSObject *parent, GSContext */*parentCtx*/): GSObject(parent)
{
	connect(this, SIGNAL(gsPropertyChanged(QString)),
		this, SLOT(notifyQml(QString)));
}

void GSContext::bindQmlContext(QQmlContext *context)
{
	if (!mContexts.contains(context))
		mContexts.append(context);
}

void GSContext::unbindQmlContext(QQmlContext *context)
{
	mContexts.removeAll(context);
}

void GSContext::notifyQml(const QString &name)
{
	foreach(QQmlContext* context, mContexts)
		context->setContextProperty(name, gsProperty(name));
}
