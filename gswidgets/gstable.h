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

	Q_PROPERTY(QVariant selection READ selection WRITE setSelection NOTIFY selectionChanged)
	Q_PROPERTY(QVariant currentRow READ currentRow WRITE setCurrentRow NOTIFY currentRowChanged)

	QVariant selection() const;
	QVariant currentRow() const;

	int columnCount() const;
	GSColumn *column(int col) const;

public slots:
	void setSelection(QVariant selection);
	void setCurrentRow(QVariant currentRow);

signals:
	void selectionChanged(QVariant selection);
	void currentRowChanged(QVariant currentRow);
	void columnAdded(GSColumn* column);

private slots:
	void onCurrentChanged(const QModelIndex &current);
	void onSelectionChanged();

private:
	QTableView* mTable;
	GSTableModel* mModel;
};

class GSTableModel : public QAbstractItemModel
{
	Q_OBJECT
public:
	GSTableModel(GSTable* host);

	virtual QModelIndex index(
			int row, int column,
			const QModelIndex &parent = QModelIndex()) const;
	virtual QModelIndex parent(const QModelIndex &child) const;
	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
	virtual int columnCount(
			const QModelIndex &parent = QModelIndex()) const;
	virtual QVariant data(
			const QModelIndex &index,
			int role = Qt::DisplayRole) const;
	virtual QVariant headerData(
			int section, Qt::Orientation orientation,
			int role) const;

	void appendColumn(GSColumn* column);
	bool moveColumn(GSColumn* column, int newPos);
	GSColumn* column(int col) const;

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
