#include "gslabel.h"

GSLabel::GSLabel(GSObject *parent): GSWidget(parent)
{
	mLabel = new QLabel;
}

QWidget *GSLabel::widget() const
{
	return mLabel;
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

