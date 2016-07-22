#include "gsmainwindow.h"

#include <QLabel>

#include "gscontext.h"

GSMainWindow::GSMainWindow(GSObject */*parent*/): GSWidget()
{
	mMW = new QMainWindow;
	mMW->setCentralWidget(new QWidget(mMW));
	mGrid = new QGridLayout(mMW->centralWidget());
	mMW->centralWidget()->setLayout(mGrid);
	setName(type());
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

QString GSMainWindow::type() const
{
	return "main";
}

void GSMainWindow::run()
{
	mMW->show();
	emit shown();
}

QQmlContext *GSMainWindow::makeRootQmlContext()
{
	return mEngine.rootContext();
}

GSContext *GSMainWindow::makeContext(GSContext *parent)
{
	return new GSContext(/*parent*/);
}
