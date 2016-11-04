#include "gsmainwindow.h"

#include <QLabel>

#include <gscontext.h>

GSMainWindow::GSMainWindow(GSObject */*parent*/): GSWidget()
{
	mMW = new QMainWindow;
	mMW->setCentralWidget(new QWidget(mMW));
	mGrid = new QGridLayout(mMW->centralWidget());
	mMW->centralWidget()->setLayout(mGrid);
	setName("main");
}

QWidget *GSMainWindow::widget() const
{
	return mMW;
}

bool GSMainWindow::addWidget(QWidget *widget, int x, int y, int xspan, int yspan)
{
	widget->setParent(mMW);
	mGrid->addWidget(widget, y, x, yspan, xspan);
	return true;
}

QQmlContext *GSMainWindow::makeRootQmlContext()
{
	return mEngine.rootContext();
}

GSContext *GSMainWindow::makeContext(GSContext *parent)
{
	return new GSContext(parent);
}

bool GSMainWindow::loadSource(SourceItem *item)
{
	if (!GSWidget::loadSource(item))
		return false;
	mMW->show();
	emit shown();
	return true;
}
