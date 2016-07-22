#include "gstable.h"

#include "gscolumn.h"

GSTable::GSTable(GSObject* parent): GSWidget(parent)
{
	mTable = new QTableView;
	mTable->setModel(mModel = new GSTableModel(this));
}

QString GSTable::type() const
{
	return "table";
}

QWidget *GSTable::widget() const
{
	return mTable;
}

void GSTable::appendColumn(GSColumn *column)
{
	mModel->appendColumn(column);
}

bool GSTable::moveColumn(GSColumn *column, int newPos)
{
	return mModel->moveColumn(column, newPos);
}


GSTableModel::GSTableModel(GSTable *host) : QAbstractItemModel(host),
	mHost(host), mRowNumber(0)
{
}

QModelIndex GSTableModel::index(int row, int column, const QModelIndex &parent) const
{
	if (parent.isValid())
		return QModelIndex();
	return createIndex(row, column);
}

QModelIndex GSTableModel::parent(const QModelIndex &child) const
{
	return QModelIndex();
}

int GSTableModel::rowCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;
	return mRowNumber;
}

int GSTableModel::columnCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;
	return mColumns.size();
}

QVariant GSTableModel::data(const QModelIndex &index, int role) const
{
	if (index.parent().isValid())
		return QVariant();
	switch(role) {
	case Qt::DisplayRole: {
		int r = index.row();
		int c = index.column();
		if (c < 0 || c >= mValues.size())
			return QVariant();
		if (r < 0 || r >= mValues[c].size())
			return QVariant();
		return mValues[c][r];
	}
	default:;
	}
	return QVariant();
}

QVariant GSTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation != Qt::Horizontal)
		return QVariant();
	if (section < 0 || section >= mColumns.size())
		return QVariant();
	switch(role) {
	case Qt::DisplayRole:
		return mColumns[section]->header();
	default:;
	}
	return QVariant();
}

void GSTableModel::appendColumn(GSColumn *column)
{
	int ind = 0;
	int newPos = column->pos();
	while (ind < mColumns.size() && mColumns.at(ind)->pos() < newPos) ++ind;
	beginInsertColumns(QModelIndex(), ind, ind);
	mColumns.insert(ind, column);
	mValues.insert(ind, column->value().toList());
	endInsertColumns();
	int newSize = column->value().toList().size();
	if (newSize > mRowNumber) {
		beginResetModel();
		mRowNumber = newSize;
		endResetModel();
	}
	connect(column, SIGNAL(valueChanged(QVariant)),
		this, SLOT(columnValueChanged(QVariant)));
	connect(column, SIGNAL(posChanged(int)),
		this, SLOT(columnMoved(int)));
}

bool GSTableModel::moveColumn(GSColumn *column, int newPos)
{
	if (newPos < 0 || newPos >= mColumns.size())
		return false;
	int oldPos = mColumns.indexOf(column);
	if (oldPos < 0)
		return false;
	return true;
}

void GSTableModel::updateColumn(int colPos, int start, int fin)
{
	QModelIndex b = index(start, colPos, QModelIndex());
	QModelIndex e = index(fin, colPos, QModelIndex());

	emit dataChanged(b, e);
}

void GSTableModel::columnValueChanged(QVariant value)
{
	GSColumn* column = qobject_cast<GSColumn*>(sender());
	if (!column)
		return;
	if (value.type() != QVariant::List)
		return;
	int size = value.toList().size();
	if (size > mRowNumber) {
		// TODO smart check insert
		beginResetModel();
		mValues[column->pos()] = value.toList();
		mRowNumber = size;
		endResetModel();
	} else if (size < mRowNumber) {
		// TODO smart check remove
		int maxval = size;
		foreach(GSColumn* col, mColumns)
			if (col->pos() > maxval)
				maxval = col->pos();
		if (maxval < mRowNumber) {
			beginResetModel();
			mValues[column->pos()] = value.toList();
			endResetModel();
		} else {
			mValues[column->pos()] = value.toList();
			emit dataChanged(
				index(0, column->pos()),
				index(mRowNumber - 1, column->pos()));
		}
	} else {
		// TODO smart check update
		mValues[column->pos()] = value.toList();
		emit dataChanged(
			index(0, column->pos()),
			index(mRowNumber - 1, column->pos()));
	}
}

void GSTableModel::columnMoved(int newPos)
{
	GSColumn* column = qobject_cast<GSColumn*>(sender());
	if (!column)
		return;
	int oldPos = mColumns.indexOf(column);
	if (oldPos < 0)
		return;
	if (newPos != oldPos)
		moveColumn(column, newPos);
}


GSObject *GSTableBuilder::makeObject(GSObject *parent) const
{
	return new GSTable(parent);
}

GSObjectBuilder *GSTableBuilder::clone() const
{
	GSObjectBuilder *res = new GSTableBuilder();
	res->setEnhancement(new SourceItem(enhancement()));
	return res;
}
