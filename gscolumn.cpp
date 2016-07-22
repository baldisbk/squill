#include "gscolumn.h"

#include "gstable.h"

GSColumn::GSColumn(GSObject *parent) : GSObject(parent), mHost(NULL)
{}

QString GSColumn::type() const
{
	return "column";
}

bool GSColumn::loadSource(SourceItem *item)
{
	GSObject::loadSource(item);
	mHost = qobject_cast<GSTable*>(gsParent());
	if (mHost) mHost->appendColumn(this);
	return true;
}

QVariant GSColumn::value() const
{
	return mValue;
}

int GSColumn::pos() const
{
	return mPos;
}

QString GSColumn::header() const
{
	return mHeader;
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


GSObject *GSColumnBuilder::makeObject(GSObject *parent) const
{
	return new GSColumn(parent);
}

GSObjectBuilder *GSColumnBuilder::clone() const
{
	GSObjectBuilder *res = new GSColumnBuilder();
	res->setEnhancement(new SourceItem(enhancement()));
	return res;
}
