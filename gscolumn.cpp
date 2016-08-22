#include "gscolumn.h"

#include "gstable.h"

GSColumn::GSColumn(GSObject *parent) : GSObject(parent), mHost(NULL)
{}

bool GSColumn::loadSource(SourceItem *item)
{
	if (!GSObject::loadSource(item))
		return false;
	mHost = qobject_cast<GSTable*>(gsParent());
	if (mHost) mHost->appendColumn(this);
	return true;
}

QVariant GSColumn::value() const
{
	return mValue;
}

QVariant GSColumn::value(int pos) const
{
	if (pos >= 0 && pos < mValue.size())
		return mValue[pos];
	else
		return QVariant();
}

int GSColumn::pos() const
{
	return mPos;
}

QString GSColumn::header() const
{
	return mHeader;
}

int GSColumn::size() const
{
	return mValue.size();
}

void GSColumn::setValue(QVariant value)
{
	if (value.type() != QVariant::List)
		return;
	QVariantList list = value.toList();
	if (mValue == list)
		return;

	mValue = list;
	emit valueChanged(value);
}

void GSColumn::setPos(int pos)
{
	if (mPos == pos)
		return;

	if (mHost && !mHost->moveColumn(this, pos))
		return;

	mPos = pos;
	emit posChanged(pos);
}

void GSColumn::setHeader(QString header)
{
	if (mHeader == header)
		return;

	mHeader = header;
	emit headerChanged(header);
}
