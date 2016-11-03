#include "gscombobox.h"

GSComboBox::GSComboBox(GSObject *parent): GSWidget(parent)
{
	mCombo = new QComboBox();
	connect(mCombo, SIGNAL(currentTextChanged(QString)),
		this, SLOT(transformTextSignal(QString)));
}

QWidget *GSComboBox::widget() const
{
	return mCombo;
}

bool GSComboBox::readonly() const
{
	return !mCombo->isEditable();
}

QVariant GSComboBox::current() const
{
	return mCombo->currentText();
}

QVariant GSComboBox::values() const
{
	QStringList res;
	for(int i = 0; i < mCombo->count(); ++i)
		res += mCombo->itemText(i);
	return res;
}

void GSComboBox::setReadonly(bool ro)
{
	if (readonly() == ro)
		return;

	mCombo->setEditable(!ro);
	emit readonlyChanged(ro);
}

void GSComboBox::setCurrent(QVariant curr)
{
	QString text = gsToScalar(curr).toString();
	if (current() == text)
		return;

	mCombo->setCurrentText(text);
	emit currentChanged(text);
}

void GSComboBox::setValues(QVariant values)
{
	QString curr = mCombo->currentText();

	QStringList vals;
	if (values.type() == QVariant::StringList)
		vals = values.toStringList();
	else if (values.type() == QVariant::List) {
		QVariantList vlist = values.toList();
		foreach(QVariant v, vlist)
			vals.append(v.toString());
	} else
		vals.append(values.toString());

	mCombo->clear();
	mCombo->addItems(vals);
	if (readonly()) {
		if (vals.contains(curr))
			mCombo->setCurrentText(curr);
		else {
			if (!vals.isEmpty())
				mCombo->setCurrentIndex(0);
			emit currentChanged(current());
		}
	} else
		mCombo->setCurrentText(curr);
	emit valuesChanged(vals);
}

void GSComboBox::transformTextSignal(QString value)
{
	emit currentChanged(value);
}
