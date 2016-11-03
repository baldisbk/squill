#ifndef GSDELEGATE_H
#define GSDELEGATE_H

#include "gsobject.h"

class GSTable;
class GSColumn;

class GSDelegate : public GSObject
{
	Q_OBJECT
public:
	GSDelegate(GSObject* parent = NULL);

	virtual bool loadSource(SourceItem *item);

	Q_PROPERTY(QVariant row READ row WRITE setRow NOTIFY rowChanged)
	QVariant row() const;

public slots:
	void setRow(QVariant row);

signals:
	void rowChanged(QVariant row);

private slots:
	void onColumnAdded(GSColumn* column);
	void onColumnChanged(QString name);

private:
	GSTable* mHost;
	QMap<GSColumn*, QString> mColumns;
	int mRow;
};

DEFINE_GSCLASS(GSDelegate, "delegate")

#endif // GSDELEGATE_H
