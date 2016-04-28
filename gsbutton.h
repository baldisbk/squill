#ifndef GSBUTTON_H
#define GSBUTTON_H

#include <QPushButton>

#include "gswidget.h"

class GSButton : public GSWidget {
	Q_OBJECT
public:
	GSButton(GSObject* parent);

	Q_PROPERTY(QString caption READ caption WRITE setCaption NOTIFY captionChanged)

	virtual QString type() const;
	virtual QWidget *widget() const;

	QString caption() const;

public slots:
	void setCaption(QString caption);

signals:
	void captionChanged(QString caption);
	void clicked();

private:
	QPushButton* mButton;
};

class GSButtonBuilder : public GSObjectBuilder {
public:
	virtual GSObject *makeObject(GSObject *parent) const;

protected:
	virtual GSObjectBuilder *clone() const;
};
#endif // GSBUTTON_H
