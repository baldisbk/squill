#include <QApplication>
#include <QFile>

#include "gsmainwindow.h"

#include "gsdatabase.h"
#include "gsquery.h"

#include "gsbutton.h"
#include "gslabel.h"
#include "gslineedit.h"

#include "gscolumn.h"
#include "gstable.h"

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

	fak->registerBuilder("database", new GSDatabaseBuilder);
	fak->registerBuilder("query", new GSQueryBuilder);

	fak->registerBuilder("button", new GSButtonBuilder);
	fak->registerBuilder("label", new GSLabelBuilder);
	fak->registerBuilder("lineedit", new GSLineEditBuilder);

	fak->registerBuilder("table", new GSTableBuilder);
	fak->registerBuilder("column", new GSColumnBuilder);

	GSMainWindow mw;
	mw.loadSource(&src);
	mw.run();

	return app.exec();
}
