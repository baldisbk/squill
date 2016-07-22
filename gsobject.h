#ifndef GSOBJECT_H
#define GSOBJECT_H

#include <QObject>
#include <QQmlEngine>
#include <QStack>

#include "sourceparser.h"

#include <QDebug>

class GSObject;

class PropertyListener : public QObject {
	Q_OBJECT
public:
	PropertyListener(
		GSObject* sender, QString source,
		GSObject* receiver, QString destination);
	bool dynamic() const;
	void setDynamic(bool dynamic);

	GSObject *sender() const;
	GSObject *receiver() const;
	QString source() const;
	QString destination() const;

public slots:
	void notify();

signals:
	void notified();

private:
	GSObject* mSnd;
	QString mSprop;
	GSObject* mRcv;
	QString mRprop;
	bool mDynamic;
};

class GSContext;

class GSObject : public QObject {
	Q_OBJECT
public:
	GSObject(GSObject* parent = NULL);
	virtual bool loadSource(SourceItem* item);

	GSObject *localObject(const QString &name) const;
	void setLocalObject(const QString &name, GSObject* obj);
	QStringList localObjects() const;
	QStringList childrenObjects() const;

	QVariant gsProperty(const QString& name) const;
	bool hasGSProperty(const QString& name) const;
	void setGSProperty(const QString& name, const QVariant &value);
	QStringList gsProperties() const;

	// it is inherited from parent
	// (and implicitly created in MainWindow)
	GSContext *contextObject();
	// it is created only if necessary (for QML & JS only)
	QQmlContext *qmlContext();

	virtual const QObject *object() const;
	virtual QObject *object();

	GSObject *gsParent() const;

	virtual PropertyListener *bindProperty(QString obj, QString src, QString dst);
	void removeBinding(QString dst);
	virtual bool eventFilter(QObject *obj, QEvent *e);

	QString name() const;
	void setName(const QString &name);

	virtual QString type() const = 0;
	static QVariant gsToScalar(const QVariant& var);

signals:
	void gsPropertyChanged(const QString& name);

protected:
	bool makeConnection(SourceConnect connection);
	bool makeBinding(SourceBind binding);
	virtual bool setContents(const QString& contents);

	static QString signalStr(const QString &signal);
	static QString slotStr(const QString &slot);

	virtual QQmlContext *makeRootQmlContext();
	virtual GSContext *makeContext(GSContext *parent = NULL);

protected:
	QMap<QObject*, QMap<QString, QStringList> > mBinding;
	QMap<QString, PropertyListener*> mListeners;

private:
	GSObject* mParent;
	QQmlContext* mQmlContext;
	GSContext* mContext;
	QString mName;
	QMap<QString, GSObject*> mLocalContext;
	QStringList mSiblings;
	QStringList mChildren;
};


/**
 * @brief The GSObjectBuilder class
 */
class GSObjectBuilder {
public:
	GSObjectBuilder();
	virtual ~GSObjectBuilder();

	/**
	 * @brief makeObject
	 * Use this to create new object for this class from item section.
	 * @param item Item section with this class
	 * @return new object
	 */
	virtual GSObject* makeObject(GSObject *parent) const = 0;

	/**
	 * @brief enhancedSource
	 * Makes section enhanced with default section contents
	 * @param item initial section
	 * @return enhanced section
	 */
	SourceItem* makeSource(SourceItem* item) const;

	/**
	 * @brief makeEnhanced
	 * Use this to create new builder from class section with this class as
	 * a parent.
	 * @param item Class section with this class as a parent
	 * @return new class builder
	 */
	GSObjectBuilder* makeEnhancedBuilder(SourceItem* item);

	QString name() const;
	void setName(const QString &name);

	/**
	 * @brief enhancement
	 * Default description for new objects. Exact item section contents
	 * overrides these properties, if specified.
	 * @return default section
	 */
	SourceItem *enhancement() const;
	void setEnhancement(SourceItem *enhancement);

	virtual GSObjectBuilder* clone() const = 0;

private:
	SourceItem* mEnhancement;
	QString mName;
};

class GSObjectFactory : private QMap<QString, QStack<GSObjectBuilder*> > {
public:
	GSObject* makeObject(SourceItem* item, GSObject *parent);
	SourceItem* makeSource(SourceItem* item);
	void registerBuilder(QString className, GSObjectBuilder* builder);
	void registerBuilder(SourceItem* item);
	void unregisterBuilder(SourceItem* item);

	static GSObjectFactory *factory();
private:
	GSObjectFactory() {}

	static GSObjectFactory* mFactory;
};

#endif // GSOBJECT_H
