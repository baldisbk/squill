#include "gsobject.h"

#include <QQmlContext>
#include <QMetaProperty>
#include <QEvent>

#include "gscontext.h"

////////////////////////////////////////////////////////
//////////////// GSObject		////////////////

GSObject::GSObject(GSObject *parent):
	QObject(parent), mParent(parent), mQmlContext(NULL), mContext(NULL)
{
}

bool GSObject::loadSource(SourceItem *item)
{
	if (mParent)
		mContext = mParent->contextObject();
	else
		mContext = makeContext();

	if (!item)
		return false;
	setName(item->name);

	setLocalObject(THIS_RESWORD, this);
	if (contextObject())
		setLocalObject(QString(), contextObject());
	if (mParent) {
		setLocalObject(PARENT_RESWORD, mParent);
		QStringList siblings = mParent->childrenObjects();
		foreach(QString sibling, siblings)
			setLocalObject(sibling, mParent->localObject(sibling));
	} else
		setLocalObject(name(), this);

	foreach(SourceAttr attr, item->attributes)
		if (attr.type == attrValue)
			object()->setProperty(attr.name.toLatin1(), attr.value);
	if (!setContents(item->contents))
		;// TODO report problem

	QList<SourceItem*> children = item->children.values();

	// register local classes
	foreach(SourceItem* child, children) {
		if (child->type == CLASS_RESWORD)
			GSObjectFactory::factory()->registerBuilder(child);
	}

	// make children
	mChildren.clear();
	foreach(SourceItem* child, children) {
		if (child->type == CLASS_RESWORD)
			continue;
		GSObject* obj = GSObjectFactory::factory()->makeObject(child, this);
		if (!obj)
			// TODO report problem
			return false;
		setLocalObject(child->name, obj);
		mChildren.append(child->name);
		SourceItem* newSrc = GSObjectFactory::factory()->makeSource(child);
		item->children[child->name] = newSrc;
		delete child;
	}
	// now we have all children, parent and siblings
	// load children (they will connect and bind)
	foreach(SourceItem* child, item->children) {
		if (child->type == CLASS_RESWORD)
			continue;
		localObject(child->name)->loadSource(child);
	}

	// remove local classes
	foreach(SourceItem* child, item->children) {
		if (child->type == CLASS_RESWORD)
			GSObjectFactory::factory()->unregisterBuilder(child);
	}

	// connect and bind this
	foreach(SourceConnect connect, item->connects)
		if (!makeConnection(connect))
			;// TODO report problem
	foreach(SourceBind binding, item->bindings)
		if (!makeBinding(binding))
			;//TODO report problem
	// TODO embedded scripts for properties
	return true;
}

void GSObject::setLocalObject(const QString &name, GSObject *obj)
{
	if (!obj)
		return;
	mLocalContext.insert(name, obj);
	if (name.isEmpty())
		return;
	object()->setProperty(
		name.toLatin1(), QVariant::fromValue(obj->object()));
	if (qmlContext())
		qmlContext()->setContextProperty(name, obj->object());
}

QStringList GSObject::localObjects() const
{
	return mLocalContext.keys();
}

QStringList GSObject::childrenObjects() const
{
	return mChildren;
}

QVariant GSObject::gsProperty(const QString &name) const
{
	return object()->property(name.toLatin1());
}

bool GSObject::hasGSProperty(const QString &name) const
{
	return
		object()->metaObject()->indexOfProperty(name.toLatin1()) != -1 ||
		object()->dynamicPropertyNames().contains(name.toLatin1());
}

void GSObject::setGSProperty(const QString &name, const QVariant &value)
{
	object()->setProperty(name.toLatin1(), value);
	if (qmlContext())
		qmlContext()->setContextProperty(name, value);
	emit gsPropertyChanged(name);
}

QStringList GSObject::gsProperties() const
{
	const QMetaObject* metaObject = object()->metaObject();
	QStringList properties;
	for(int i = 0; i < metaObject->propertyCount(); ++i)
		properties << QString::fromLatin1(metaObject->property(i).name());
	foreach(QByteArray arr, object()->dynamicPropertyNames())
		properties << QString::fromLatin1(arr);
	return properties;
}

GSObject *GSObject::localObject(const QString& name) const
{
	return mLocalContext.value(name, NULL);
}

GSContext *GSObject::contextObject()
{
	return mContext;
}

QQmlContext *GSObject::qmlContext()
{
	if (mQmlContext)
		return mQmlContext;
	else if (mParent && mParent->qmlContext())
		mQmlContext = new QQmlContext(mParent->qmlContext());
	else
		mQmlContext = makeRootQmlContext();
	if (mQmlContext) {
		foreach(GSObject* object, mLocalContext) {
			mQmlContext->setContextProperty(
				object->name(), object->object());
			mQmlContext->setProperty(
				object->name().toLatin1(),
				QVariant::fromValue(object->object()));
		}
		if (contextObject()) {
			QStringList contextProps = contextObject()->gsProperties();
			foreach(QString name, contextProps)
				mQmlContext->setContextProperty(
					name, contextObject()->gsProperty(name));
		}
		return mQmlContext;
	} else
		return NULL;
}

QWidget *GSObject::widget() const
{
	return NULL;
}

const QObject *GSObject::object() const
{
	return this;
}

QObject *GSObject::object()
{
	return this;
}

GSObject *GSObject::parent() const
{
	return mParent;
}

bool GSObject::addWidget(
	QWidget */*widget*/,
	int /*x*/, int /*y*/,
	int /*xspan*/, int /*yspan*/)
{
	return false;
}

QString capitalize(QString src)
{
	if (src.isEmpty())
		return src;
	QChar first = src.at(0);
	QString res = src.right(src.length() - 1);
	res.prepend(first.toUpper());
	return res;
}

void GSObject::removeBinding(QString dst)
{
	if (!mListeners.contains(dst))
		return;
	PropertyListener* l = mListeners[dst];
	if (l->dynamic()) {
		mBinding[l->sender()][l->source()].removeAll(dst);
		if (mBinding[l->sender()][l->source()].isEmpty())
			mBinding[l->sender()].remove(l->source());
		if (mBinding[l->sender()].isEmpty()) {
			mBinding.remove(l->sender());
			l->sender()->removeEventFilter(this);
		}
	}
	delete l;
	mListeners.remove(dst);
}

PropertyListener* GSObject::bindProperty(QString obj, QString src, QString dst)
{
	// TODO empty name is either context or this
	QObject* snd = localObject(obj)->object();
	if (!snd) return NULL;
	int sindex = snd->metaObject()->indexOfProperty(src.toLatin1());
	QMetaProperty sprop = snd->metaObject()->property(sindex);
	QString sigName;
	if (sprop.isValid() && sprop.hasNotifySignal())
		sigName = signalStr(QString::fromLatin1(
			sprop.notifySignal().methodSignature()));
	else {
		removeBinding(dst);
		if (!mBinding.contains(snd))
			snd->installEventFilter(this);
		mBinding[snd][src].append(dst);
		mListeners[dst] = new PropertyListener(snd, src, object(), dst);
		mListeners[dst]->setDynamic(true);
		// do NOT connect
		// fcuk property exist check
		return mListeners[dst];
	}
	removeBinding(dst);
	PropertyListener* l = new PropertyListener(snd, src, object(), dst);
	connect(snd, sigName.toLatin1().data(), l, SLOT(notify()));
	mListeners[dst] = l;
	return l;
}

bool GSObject::eventFilter(QObject *obj, QEvent *e)
{
	if (e->type()==QEvent::DynamicPropertyChange && mBinding.contains(obj)) {
		QDynamicPropertyChangeEvent *propEvent =
			static_cast<QDynamicPropertyChangeEvent*>(e);
		if (propEvent) {
			QString propName = QString::fromLatin1(propEvent->propertyName());
			if (mBinding[obj].contains(propName)) {
				QStringList list = mBinding[obj][propName];
				foreach(QString dst, list)
					mListeners[dst]->notify();
			}
		}
	}
	return QObject::eventFilter(obj, e);
}

QString GSObject::name() const
{
	return mName;
}

void GSObject::setName(const QString &name)
{
	mName = name;
}

bool GSObject::setContents(const QString& /*contents*/)
{
	return false;
}

bool GSObject::makeConnection(SourceConnect connection)
{
	QObject* snd = localObject(connection.sender)->object();
	QObject* rcv = localObject(connection.receiver)->object();
	if (snd && rcv)
		// TODO report problem
		return connect(
			snd, signalStr(connection.signal).toLatin1(),
			rcv, slotStr(connection.slot).toLatin1());
	else
		return false; // TODO report problem
}

bool GSObject::makeBinding(SourceBind binding)
{
	GSObject* dst = localObject(binding.dst);
	if (!dst)
		return false; // TODO report problem
	// TODO report problem
	return dst->bindProperty(binding.src, binding.srcprop, binding.dstprop);
}

QString GSObject::signalStr(const QString &signal) const
{
	if (signal.contains("("))
		return QString("2%1").arg(signal);
	else
		return QString("2%1()").arg(signal);
}

QString GSObject::slotStr(const QString &slot) const
{
	if (slot.contains("("))
		return QString("1%1").arg(slot);
	else
		return QString("1%1()").arg(slot);
}

QQmlContext *GSObject::makeRootQmlContext()
{
	return NULL;
}

GSContext *GSObject::makeContext(GSContext */*parent*/)
{
	return NULL;
}


////////////////////////////////////////////////////////
//////////////// PropertyListener	////////////////

PropertyListener::PropertyListener(QObject *snd, QString sprop, QObject *rcv, QString rprop) :
	QObject(rcv), mSnd(snd), mSprop(sprop), mRcv(rcv), mRprop(rprop), mDynamic(false)
{
	notify();
}

void PropertyListener::notify()
{
	mRcv->setProperty(mRprop.toLatin1(), mSnd->property(mSprop.toLatin1()));
	emit notified();
}

bool PropertyListener::dynamic() const
{
	return mDynamic;
}

void PropertyListener::setDynamic(bool dynamic)
{
	mDynamic = dynamic;
}


QObject *PropertyListener::sender() const
{
	return mSnd;
}

QObject *PropertyListener::receiver() const
{
	return mRcv;
}

QString PropertyListener::source() const
{
	return mSprop;
}

QString PropertyListener::destination() const
{
	return mRprop;
}


////////////////////////////////////////////////////////
//////////////// GSObjectBuilder	////////////////

GSObjectBuilder::GSObjectBuilder() : mEnhancement(new SourceItem) {}

GSObjectBuilder::~GSObjectBuilder() {delete mEnhancement;}

SourceItem *GSObjectBuilder::enhancement() const
{
	return mEnhancement;
}

void GSObjectBuilder::setEnhancement(SourceItem *enhancement)
{
	delete mEnhancement;
	mEnhancement = enhancement;
}

SourceItem *GSObjectBuilder::makeSource(SourceItem *item) const
{
	SourceItem* res = new SourceItem(item);
	foreach(QString aname, enhancement()->attributes.keys()) {
		if (aname == PARENT_RESWORD)
			continue;
		if (!res->attributes.contains(aname))
			res->attributes[aname] = enhancement()->attributes[aname];
	}
	foreach(QString cname, enhancement()->children.keys())
		if (!res->children.contains(cname))
			res->children[cname] =
				new SourceItem(enhancement()->children[cname]);
	if (res->contents.isEmpty())
		res->contents = enhancement()->contents;
	res->name = item->name;
	res->type = item->type;
	return res;
}

GSObjectBuilder *GSObjectBuilder::makeEnhancedBuilder(SourceItem *item)
{
	GSObjectBuilder* res = clone();
	res->setEnhancement(makeSource(item));
	return res;
}

QString GSObjectBuilder::name() const
{
	return mName;
}

void GSObjectBuilder::setName(const QString &name)
{
	mName = name;
}


////////////////////////////////////////////////////////
//////////////// GSObjectFactory	////////////////

GSObjectFactory* GSObjectFactory::mFactory = NULL;

GSObject *GSObjectFactory::makeObject(SourceItem *item, GSObject* parent)
{
	if (item && contains(item->type) && !value(item->type).isEmpty())
		return value(item->type).top()->makeObject(parent);
	else
		return NULL;
}

SourceItem *GSObjectFactory::makeSource(SourceItem *item)
{
	if (item && contains(item->type) && !value(item->type).isEmpty())
		return value(item->type).top()->makeSource(item);
	else
		return NULL;
}

void GSObjectFactory::registerBuilder(QString className, GSObjectBuilder *builder)
{
	if (!builder)
		return;
	operator[](className).push(builder);
}

void GSObjectFactory::registerBuilder(SourceItem *item)
{
	if (!item)
		return;
	if (item->type != CLASS_RESWORD)
		return;
	if (!item->attributes.contains(PARENT_RESWORD))
		return;
	if (operator[](item->attributes[PARENT_RESWORD].value).isEmpty())
		return;
	GSObjectBuilder* parent =
		value(item->attributes[PARENT_RESWORD].value).top();
	operator[](item->name).push(parent->makeEnhancedBuilder(item));
}

void GSObjectFactory::unregisterBuilder(SourceItem *item)
{
	if (!item)
		return;
	if (item->type != CLASS_RESWORD)
		return;
	if (operator[](item->name).isEmpty())
		return;
	operator[](item->name).pop();
}

GSObjectFactory *GSObjectFactory::factory()
{
	if (mFactory)
		return mFactory;
	else
		return mFactory = new GSObjectFactory;
}
