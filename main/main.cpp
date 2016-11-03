#include <QApplication>
#include <QFile>
#include <QDir>
#include <QPluginLoader>

#include "gsmainwindow.h"

#include "gsdatabase.h"
#include "gsquery.h"

#include "gsqmlitem.h"
#include "gsqmlwidget.h"
#include "gsqmlwindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QXmlStreamReader reader;
	SourceItem src;
	QFile file((argc > 1) ? argv[1] : "test.xml");
	if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		reader.setDevice(&file);
		while (reader.readNext() != QXmlStreamReader::StartElement) {}
		src.read(reader);
	}

	GSObjectFactory* fak = GSObjectFactory::factory();

	QDir pluginsDir(qApp->applicationDirPath());
	pluginsDir.cd("plugins");
	foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
		QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
		QObject *plugin = pluginLoader.instance();
		SquillPluginInterface *splugin =
			qobject_cast<SquillPluginInterface*>(plugin);

		if (splugin) {
			QList<GSObjectBuilder*> builders = splugin->builders();
			foreach(GSObjectBuilder* builder, builders)
				fak->registerBuilder(builder);
		} else
			qDebug() << QString("Error loading plugin %1: %2").
				arg(fileName).arg(pluginLoader.errorString());
	}

	// base
	fak->registerBuilder(new GSDatabaseBuilder);
	fak->registerBuilder(new GSQueryBuilder);

	//QML
	fak->registerBuilder(new GSQmlItemBuilder);
	fak->registerBuilder(new GSQmlWidgetBuilder);
	fak->registerBuilder(new GSQmlWindowBuilder);

	GSMainWindow mw;
	mw.loadSource(&src);
	mw.run();

	return app.exec();
}
