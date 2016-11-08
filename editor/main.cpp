#include "mainwindow.h"
#include <QApplication>
#include <QDir>
#include <QPluginLoader>

#include <gsobject.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QXmlStreamReader reader;
	SourceItem proj;
	QFile file((argc > 1) ? argv[1] : "test.xml");
	if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		reader.setDevice(&file);
		while (reader.readNext() != QXmlStreamReader::StartElement) {}
		proj.read(reader);
	}

	MainWindow w;

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

	w.show();

	return a.exec();
}
