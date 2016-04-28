#include "gscontext.h"

#include <QQmlContext>

GSContext::GSContext()
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

QString GSContext::type() const
{
	return "context";
}

bool GSContext::setContents(const QString &/*contents*/)
{
	return false;
}
