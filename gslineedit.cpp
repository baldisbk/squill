#include "gslineedit.h"

GSLineEdit::GSLineEdit(GSObject *parent): GSWidget(parent)
{
	mEdit = new QLineEdit;
	connect(mEdit, SIGNAL(textChanged(QString)),
		this, SLOT(transformTextSignal(QString)));
}

QWidget *GSLineEdit::widget() const
{
	return mEdit;
}

QVariant GSLineEdit::text() const
{
	return mEdit->text();
}

void GSLineEdit::setText(QVariant text)
{
	setText(gsToScalar(text).toString());
}

void GSLineEdit::setText(QString text)
{
	if (mEdit->text() == text)
		return;

	mEdit->setText(text);
	emit textChanged(text);
}

void GSLineEdit::transformTextSignal(QString value)
{
	emit textChanged(value);
}
