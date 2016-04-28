#include "gslabel.h"

GSLabel::GSLabel(GSObject *parent): GSWidget(parent)
{
	mLabel = new QLabel;
}

QWidget *GSLabel::widget() const
{
	return mLabel;
}

QString GSLabel::type() const
{
	return "label";
}

QString GSLabel::label() const
{
	return mLabel->text();
}

void GSLabel::setLabel(QString label)
{
	if (mLabel->text() == label)
		return;

	mLabel->setText(label);
	emit labelChanged(label);
}

GSObject *GSLabelBuilder::makeObject(GSObject *parent) const
{
	return new GSLabel(parent);
}

GSObjectBuilder *GSLabelBuilder::clone() const
{
	GSObjectBuilder *res = new GSLabelBuilder();
	res->setEnhancement(new SourceItem(enhancement()));
	return res;
}
