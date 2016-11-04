#include "gsqml.h"

#include "gsqmlitem.h"
#include "gsqmlwidget.h"
#include "gsqmlwindow.h"

GSQml::GSQml()
{
}

QList<GSObjectBuilder *> GSQml::builders() const
{
	QList<GSObjectBuilder *> res;

	res.append(new GSQmlItemBuilder);
	res.append(new GSQmlWidgetBuilder);
	res.append(new GSQmlWindowBuilder);

	return res;
}
