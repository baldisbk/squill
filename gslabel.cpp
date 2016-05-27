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

QVariant GSLabel::label() const
{
	return mLabel->text();
}

void GSLabel::setLabel(QVariant label)
{
	QString lab = gsToScalar(label).toString();

	if (mLabel->text() == lab)
		return;

	mLabel->setText(lab);
	emit labelChanged(lab);
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
