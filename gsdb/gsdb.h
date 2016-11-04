#ifndef GSDB_H
#define GSDB_H

#include <gsobject.h>

class GSDb : public QObject, SquillPluginInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.baldis.Squill.DB")
	Q_INTERFACES(SquillPluginInterface)
public:
	GSDb();
	virtual QList<GSObjectBuilder *> builders() const;
};

#endif // GSDB_H
