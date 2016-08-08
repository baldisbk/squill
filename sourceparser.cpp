#include "sourceparser.h"

#include <QStringList>
#include <QRegExp>

void SourceItem::read(QXmlStreamReader &reader)
{
	if (reader.tokenType() != QXmlStreamReader::StartElement)
		return;
	type = reader.name().toString();
	foreach(QXmlStreamAttribute a, reader.attributes()) {
		QString n = a.name().toString();
		if (n == NAME_RESWORD)
			name = a.value().toString();
		else {
			SourceAttr attr = readAttr(n, a.value().toString());
			if (attr.value.isEmpty())
				continue;
			if (attr.type == attrBind)
				bindings.append(readLink(attr));
			else
				attributes[n] = attr;
		}
	}
	while (reader.readNext() != QXmlStreamReader::EndElement) {
		if (reader.hasError())
			return;
		switch (reader.tokenType()) {
		case QXmlStreamReader::StartElement: {
			SourceItem* item = new SourceItem;
			item->read(reader);
			if (reader.hasError())
				return;
			if (item->type == CONNECT_RESWORD) {
				connects.append(item->readLink(
					SIGNAL_RESWORD, SLOT_RESWORD));
				break;
			} else if (item->type == BINDING_RESWORD) {
				bindings.append(item->readLink(
					SRCPROP_RESWORD, DSTPROP_RESWORD));
				break;
			}
			if (children.contains(item->name)) {
				reader.raiseError("Duplicate children name");
				return;
			}
			children[item->name] = item;
			break;
		}
		case QXmlStreamReader::Characters:
			if (!contents.isEmpty())
				contents.append("\n");
			contents.append(reader.text());
			break;
		case QXmlStreamReader::Invalid:
			return;
		default:;
		}
	}
	// read token AFTER element
	reader.readNext();
}

SourceLink SourceItem::readLink(QString sprRW, QString dprRW) const
{
	SourceLink b;
	QString src, dst, srcprop, dstprop;
	if (attributes.contains(SOURCE_RESWORD))
		src = attributes[SOURCE_RESWORD].value;
	if (attributes.contains(DEST_RESWORD))
		dst = attributes[DEST_RESWORD].value;
	if (attributes.contains(sprRW))
		srcprop = attributes[sprRW].value;
	if (attributes.contains(dprRW))
		dstprop = attributes[dprRW].value;
	return readLink(src, srcprop, dst, dstprop);
}

SourceLink SourceItem::readLink(
	QString src, QString srcprop, QString dst, QString dstprop)
{
	SourceLink link;
	QStringList sparts = src.split(".");
	QStringList dparts = dst.split(".");

	if (src.isEmpty()) {
		link.src = THIS_RESWORD;
		link.srcprop = srcprop;
	} else if (srcprop.isEmpty()) {
		if (!sparts.isEmpty()) {
			link.srcprop = sparts.last();
			sparts.removeLast();
			link.src = sparts.join(".");
			if (link.src.isEmpty()) {
				if (sparts.isEmpty())
					link.src = THIS_RESWORD;
				else
					link.src = CONTEXT_RESWORD;
			}
		}
	} else {
		link.src = src;
		link.srcprop = srcprop;
	}

	if (dst.isEmpty()) {
		link.dst = THIS_RESWORD;
		link.dstprop = dstprop;
	} else if (dstprop.isEmpty()) {
		if (!dparts.isEmpty()) {
			link.dstprop = dparts.last();
			dparts.removeLast();
			link.dst = dparts.join(".");
			if (link.dst.isEmpty()) {
				if (dparts.isEmpty())
					link.dst = THIS_RESWORD;
				else
					link.dst = CONTEXT_RESWORD;
			}
		}
	} else {
		link.dst = dst;
		link.dstprop = dstprop;
	}
	return link;
}

SourceLink SourceItem::readLink(SourceAttr attr)
{
	return readLink(attr.value, QString(), QString(), attr.name);
}

SourceAttr SourceItem::readAttr(QString n, QString val)
{
	SourceAttr attr;
	// TODO: let class decide whether value or bind is default
	attr.value = val;
	attr.name = n;
	attr.type = attrValue;
	if (attr.value.isEmpty())
		return attr;
	bool hasSymbol = false;
	if (attr.value.at(0) == VALUE_SYMBOL) {
		hasSymbol = true;
		attr.type = attrValue;
	} else if (attr.value.at(0) == LINK_SYMBOL) {
		hasSymbol = true;
		attr.type = attrScript;
	}
	if (hasSymbol)
		attr.value = attr.value.right(attr.value.length()-1);

	if (attr.type == attrScript) {
		QRegExp re("(([a-zA-Z_][0-9a-zA-Z_]*\\.)*)([a-zA-Z_][0-9a-zA-Z_]*)");
		if (re.exactMatch(attr.value))
			attr.type = attrBind;
		else
			attr.type = attrScript;
	}
	return attr;
}
