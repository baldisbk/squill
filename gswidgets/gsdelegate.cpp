#include "gsdelegate.h"

#include "gstable.h"
#include "gscolumn.h"

GSDelegate::GSDelegate(GSObject *parent): GSObject(parent), mRow(-1)
{
}

bool GSDelegate::loadSource(SourceItem *item)
{
	if (!GSObject::loadSource(item))
		return false;
	mHost = qobject_cast<GSTable*>(gsParent());
	if (mHost) {
		connect(mHost, SIGNAL(currentRowChanged(QVariant)),
			this, SLOT(setRow(QVariant)));
		connect(this, SIGNAL(rowChanged(QVariant)),
			mHost, SLOT(setCurrentRow(QVariant)));
		for (int i = 0; i < mHost->columnCount(); ++i)
			onColumnAdded(mHost->column(i));
	}
	return true;
}

QVariant GSDelegate::row() const
{
	return mRow;
}

void GSDelegate::setRow(QVariant row)
{
	if (mRow == row.toInt())
		return;

	mRow = row.toInt();
	foreach(GSColumn* col, mColumns.keys())
		setGSProperty(col->name(), col->value(mRow));

	emit rowChanged(mRow);
}

void GSDelegate::onColumnAdded(GSColumn *column)
{
	if (!column)
		return;
	mColumns[column] = column->name();
	setGSProperty(column->name(), column->value(mRow));
	connect(column, SIGNAL(gsPropertyChanged(QString, QVariant)),
		this, SLOT(onColumnChanged(QString)));
}

void GSDelegate::onColumnChanged(QString name)
{
	GSColumn* column = qobject_cast<GSColumn*>(sender());
	if (column && name == "value")
		setGSProperty(column->name(), column->value(mRow));
}
