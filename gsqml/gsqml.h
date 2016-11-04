#ifndef GSQML_H
#define GSQML_H

#include <gsobject.h>

class GSQml : public QObject, SquillPluginInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.baldis.Squill.QML")
	Q_INTERFACES(SquillPluginInterface)
public:
	GSQml();
	virtual QList<GSObjectBuilder *> builders() const;
};


#endif // GSQML_H
