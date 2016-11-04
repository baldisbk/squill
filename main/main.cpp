#include <QApplication>
#include <QFile>
#include <QDir>
#include <QPluginLoader>

#include <gsobject.h>

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

	GSObject* obj = GSObjectFactory::factory()->makeObject(&src);
	if (!obj) {
		qDebug() << QString("Failed to create root %1 (%2)").
			    arg(src.name).arg(src.type);
		return -1;
	}
	SourceItem* newSrc = GSObjectFactory::factory()->makeSource(&src);
	obj->loadSource(newSrc);

	int res = app.exec();

	delete obj;

	return res;
}
