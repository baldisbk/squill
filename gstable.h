#ifndef GSTABLE_H
#define GSTABLE_H

#include "gswidget.h"

#include <QTableView>
#include <QAbstractItemModel>

class GSColumn;
class GSTableModel;

class GSTable : public GSWidget
{
	Q_OBJECT
public:
	GSTable(GSObject* parent);

	virtual QWidget *widget() const;

	void appendColumn(GSColumn* column);
	bool moveColumn(GSColumn* column, int newPos);

private:
	QTableView* mTable;
	GSTableModel* mModel;
};

class GSTableModel : public QAbstractItemModel
{
	Q_OBJECT
public:
	GSTableModel(GSTable* host);

	virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
	virtual QModelIndex parent(const QModelIndex &child) const;
	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
	virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

	void appendColumn(GSColumn* column);
	bool moveColumn(GSColumn* column, int newPos);

public slots:
	void updateColumn(int colPos, int start, int fin);

private slots:
	void columnValueChanged(QVariant value);
	void columnMoved(int newPos);

private:
	GSTable* mHost;
	QList<GSColumn*> mColumns;
	int mRowNumber;
	QList<QVariantList> mValues;
};

DEFINE_GSCLASS(GSTable, "table")

#endif // GSTABLE_H
