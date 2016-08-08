#ifndef SOURCEPARSER_H
#define SOURCEPARSER_H

#include <QXmlStreamReader>
#include <QMap>

#define PARENT_RESWORD "parent"
#define CLASS_RESWORD "class"
#define NAME_RESWORD "name"
#define THIS_RESWORD "this"
#define CONTEXT_RESWORD "context"

#define SCRIPT_RESWORD "script"
#define CONNECT_RESWORD "connect"
#define BINDING_RESWORD "bind"
#define DATABASE_RESWORD "database"

#define SOURCE_RESWORD "src"
#define DEST_RESWORD "dst"
#define SIGNAL_RESWORD "signal"
#define SLOT_RESWORD "slot"
#define SRCPROP_RESWORD "srcprop"
#define DSTPROP_RESWORD "dstprop"

#define VALUE_SYMBOL '#'
#define LINK_SYMBOL '@'

enum AttrType {
	attrValue,
	attrBind,
	attrScript
};

struct SourceAttr {
	QString name;
	QString value;
	AttrType type;
};

struct SourceLink {
	QString src, srcprop, dst, dstprop;
};

struct SourceItem {
	QString type;
	QString name;
	QString contents;
	QMap<QString, SourceAttr> attributes;
	QMap<QString, SourceItem*> children;
	QList<SourceLink> bindings;
	QList<SourceLink> connects;

	void read(QXmlStreamReader& reader);

	SourceLink readLink(QString sprRW, QString dprRW) const;
	static SourceLink readLink(
		QString src, QString srcprop, QString dst, QString dstprop);
	static SourceLink readLink(SourceAttr attr);
	static SourceAttr readAttr(QString n, QString val);

	SourceItem() {}
	SourceItem(SourceItem* other) {
		*this = *other;
		children.clear();
		foreach(SourceItem* child, other->children)
			children[child->name] = new SourceItem(child);
	}
	~SourceItem() {
		foreach(SourceItem* child, children)
			delete child;
	}
};

#endif // SOURCEPARSER_H
