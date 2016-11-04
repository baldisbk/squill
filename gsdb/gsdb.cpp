#include "gsdb.h"

#include "gsquery.h"
#include "gsdatabase.h"

GSDb::GSDb()
{
}

QList<GSObjectBuilder *> GSDb::builders() const
{
	QList<GSObjectBuilder *> res;

	res.append(new GSQueryBuilder);
	res.append(new GSDatabaseBuilder);

	return res;
}
