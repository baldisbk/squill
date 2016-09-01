#include <QApplication>
#include <QFile>

#include "gsmainwindow.h"

#include "gsdatabase.h"
#include "gsquery.h"

#include "gsbutton.h"
#include "gslabel.h"
#include "gslineedit.h"
#include "gscombobox.h"

#include "gscolumn.h"
#include "gstable.h"
#include "gsdelegate.h"

#include "gsqmlitem.h"

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

	// base
	fak->registerBuilder(new GSDatabaseBuilder);
	fak->registerBuilder(new GSQueryBuilder);

	//widgets
	fak->registerBuilder(new GSButtonBuilder);
	fak->registerBuilder(new GSLabelBuilder);
	fak->registerBuilder(new GSLineEditBuilder);
	fak->registerBuilder(new GSComboBoxBuilder);

	//table
	fak->registerBuilder(new GSTableBuilder);
	fak->registerBuilder(new GSColumnBuilder);
	fak->registerBuilder(new GSDelegateBuilder);

	//QML
	fak->registerBuilder(new GSQmlItemBuilder);

	GSMainWindow mw;
	mw.loadSource(&src);
	mw.run();

	return app.exec();
}
