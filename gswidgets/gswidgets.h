#ifndef GSWIDGETS_H
#define GSWIDGETS_H

#include <gsobject.h>

class GSWidgets : public QObject, SquillPluginInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.baldis.Squill.Widgets")
	Q_INTERFACES(SquillPluginInterface)
public:
	GSWidgets();
	virtual QList<GSObjectBuilder *> builders() const;
};

#endif // GSWIDGETS_H
