#include "gswidgets.h"

#include "gsbutton.h"
#include "gslabel.h"
#include "gslineedit.h"
#include "gscombobox.h"

#include "gscolumn.h"
#include "gstable.h"
#include "gsdelegate.h"

GSWidgets::GSWidgets()
{
}

QList<GSObjectBuilder *> GSWidgets::builders() const
{
	QList<GSObjectBuilder *> res;

	//widgets
	res.append(new GSButtonBuilder);
	res.append(new GSLabelBuilder);
	res.append(new GSLineEditBuilder);
	res.append(new GSComboBoxBuilder);

	//table
	res.append(new GSTableBuilder);
	res.append(new GSColumnBuilder);
	res.append(new GSDelegateBuilder);

	return res;
}
