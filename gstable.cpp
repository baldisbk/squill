#include "gstable.h"

#include "gscolumn.h"

GSTable::GSTable(GSObject* parent): GSWidget(parent)
{
	mTable = new QTableView;
	mTable->setModel(mModel = new GSTableModel(this));
	connect(mTable->selectionModel(),
		SIGNAL(currentChanged(QModelIndex,QModelIndex)),
		this, SLOT(onCurrentChanged(QModelIndex)));
	connect(mTable->selectionModel(),
		SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
		this, SLOT(onSelectionChanged()));
}

QWidget *GSTable::widget() const
{
	return mTable;
}

void GSTable::appendColumn(GSColumn *column)
{
	mModel->appendColumn(column);
	emit columnAdded(column);
}

bool GSTable::moveColumn(GSColumn *column, int newPos)
{
	return mModel->moveColumn(column, newPos);
}

QVariant GSTable::selection() const
{
	QVariantList res;
	QModelIndexList ilist = mTable->selectionModel()->selectedIndexes();
	foreach(QModelIndex ind, ilist)
		if (!res.contains(ind.row()))
			res.append(ind.row());
	std::sort(res.begin(), res.end());
	return res;
}

QVariant GSTable::currentRow() const
{
	return mTable->currentIndex().row();
}

int GSTable::columnCount() const
{
	return mModel->columnCount();
}

GSColumn *GSTable::column(int col) const
{
	return mModel->column(col);
}

void GSTable::setSelection(QVariant currentRows)
{
	QList<int> ilist;
	if (currentRows.type() == QVariant::List) {
		foreach(QVariant v, currentRows.toList())
			if (v.canConvert(QVariant::Int))
				ilist.append(v.toInt());
	} else if (currentRows.canConvert(QVariant::Int))
		ilist.append(currentRows.toInt());
	else
		return;
	bool hasChanged = false;
	QModelIndexList mlist = mTable->selectionModel()->selectedIndexes();
	foreach(QModelIndex index, mlist)
		if (!ilist.contains(index.row())) {
			mTable->selectionModel()->select(
					index, QItemSelectionModel::Deselect);
			hasChanged = true;
		}
	foreach(int ind, ilist) {
		QModelIndex index = mModel->index(ind, 0);
		if (!mTable->selectionModel()->isSelected(index)) {
			mTable->selectionModel()->select(
					index, QItemSelectionModel::Select);
			hasChanged = true;
		}
	}

	if (hasChanged)
		emit selectionChanged(selection());
}

void GSTable::setCurrentRow(QVariant currentRow)
{
	QModelIndex curr = mTable->currentIndex();
	int cr = gsToScalar(currentRow).toInt();
	if (curr.isValid() && curr.row() == cr)
		return;
	int column = curr.isValid() ? curr.column() : 0;
	mTable->setCurrentIndex(mModel->index(cr, column));
	emit currentRowChanged(cr);
}

void GSTable::onCurrentChanged(const QModelIndex &current)
{
	if (current.isValid())
		emit currentRowChanged(current.row());
}

void GSTable::onSelectionChanged()
{
	emit selectionChanged(selection());
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
	int newSize = column->size();
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

GSColumn *GSTableModel::column(int col) const
{
	if (col >= 0 && col < columnCount())
		return mColumns.at(col);
	return NULL;
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
