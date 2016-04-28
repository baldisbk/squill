#include "gsbutton.h"

GSButton::GSButton(GSObject *parent):
	GSWidget(parent)
{
	mButton = new QPushButton;
	connect(mButton, SIGNAL(clicked(bool)), this, SIGNAL(clicked()));
}

QWidget *GSButton::widget() const
{
	return mButton;
}

QString GSButton::caption() const
{
	return mButton->text();
}

void GSButton::setCaption(QString name)
{
	if (mButton->text() == name)
		return;

	mButton->setText(name);
	emit captionChanged(name);
}

QString GSButton::type() const
{
	return "button";
}


GSObject *GSButtonBuilder::makeObject(GSObject *parent) const
{
	return new GSButton(parent);
}

GSObjectBuilder *GSButtonBuilder::clone() const
{
	GSObjectBuilder *res = new GSButtonBuilder();
	res->setEnhancement(new SourceItem(enhancement()));
	return res;
}
