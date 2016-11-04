#ifndef GSCOMBOBOX_H
#define GSCOMBOBOX_H

#include <gswidget.h>

#include <QComboBox>

class GSComboBox : public GSWidget
{
	Q_OBJECT
public:
	GSComboBox(GSObject* parent);

	Q_PROPERTY(QVariant current READ current WRITE setCurrent NOTIFY currentChanged)
	Q_PROPERTY(bool readonly READ readonly WRITE setReadonly NOTIFY readonlyChanged)
	Q_PROPERTY(QVariant values READ values WRITE setValues NOTIFY valuesChanged)

	virtual QWidget *widget() const;

	bool readonly() const;
	QVariant current() const;
	QVariant values() const;

public slots:
	void setReadonly(bool ro);
	void setCurrent(QVariant curr);
	void setValues(QVariant values);

signals:
	void readonlyChanged(bool readonly);
	void currentChanged(QVariant current);
	void valuesChanged(QVariant values);

private slots:
	void transformTextSignal(QString value);

private:
	QComboBox* mCombo;
	bool mReadonly;
	QString mCurrent;
	QVariant m_values;
};

DEFINE_GSCLASS(GSComboBox, "combo")

#endif // GSCOMBOBOX_H
