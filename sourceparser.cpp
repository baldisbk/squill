#include "sourceparser.h"

#include <QRegExp>

SourceParser::SourceParser()
{
}

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
			SourceAttr attr;
			attr.value = a.value().toString();
			attr.type = attrValue;
			if (attr.value.isEmpty())
				continue;
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
				if (re.exactMatch(attr.value)) {
					SourceBind b;
					b.dst = THIS_RESWORD;
					b.dstprop = n;
					b.src = re.cap(1);
					if (!b.src.isEmpty())
						b.src.chop(1);
					b.srcprop = re.cap(3);
					bindings.append(b);
					continue;
				} else
					attr.type = attrScript;
			}
			attr.name = n;
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
				SourceConnect c;
				c.sender = item->attributes[SOURCE_RESWORD].value;
				c.receiver = item->attributes[DEST_RESWORD].value;
				c.signal = item->attributes[SIGNAL_RESWORD].value;
				c.slot = item->attributes[SLOT_RESWORD].value;
				if (c.sender.isEmpty())
					c.sender = THIS_RESWORD;
				if (c.receiver.isEmpty())
					c.receiver = THIS_RESWORD;
				connects.append(c);
				break;
			} else if (item->type == BINDING_RESWORD) {
				SourceBind b;
				b.src = item->attributes[SOURCE_RESWORD].value;
				b.dst = item->attributes[DEST_RESWORD].value;
				b.srcprop = item->attributes[SRCPROP_RESWORD].value;
				b.dstprop = item->attributes[DSTPROP_RESWORD].value;
				if (b.src.isEmpty())
					b.src = THIS_RESWORD;
				if (b.dst.isEmpty())
					b.dst = THIS_RESWORD;
				bindings.append(b);
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
