#include "gslineedit.h"

GSLineEdit::GSLineEdit(GSObject *parent): GSWidget(parent)
{
	mEdit = new QLineEdit;
	connect(mEdit, SIGNAL(textChanged(QString)), this, SLOT(setText(QString)));
}

QString GSLineEdit::type() const
{
	return "lineedit";
}

QWidget *GSLineEdit::widget() const
{
	return mEdit;
}

QString GSLineEdit::text() const
{
	return mEdit->text();
}

void GSLineEdit::setText(QString text)
{
	if (mEdit->text() == text)
		return;

	mEdit->setText(text);
	emit textChanged(text);
}


GSObject *GSLineEditBuilder::makeObject(GSObject *parent) const
{
	return new GSLineEdit(parent);
}

GSObjectBuilder *GSLineEditBuilder::clone() const
{
	GSObjectBuilder *res = new GSLineEditBuilder();
	res->setEnhancement(new SourceItem(enhancement()));
	return res;
}
