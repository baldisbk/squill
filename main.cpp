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

	fak->registerBuilder(new GSDatabaseBuilder);
	fak->registerBuilder(new GSQueryBuilder);

	fak->registerBuilder(new GSButtonBuilder);
	fak->registerBuilder(new GSLabelBuilder);
	fak->registerBuilder(new GSLineEditBuilder);

	fak->registerBuilder(new GSTableBuilder);
	fak->registerBuilder(new GSColumnBuilder);

	fak->registerBuilder(new GSComboBoxBuilder);

	GSMainWindow mw;
	mw.loadSource(&src);
	mw.run();

	return app.exec();
}
