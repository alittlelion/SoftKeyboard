#pragma once
#include <qwidget.h>
#include "slkeyboard_global.h"


namespace Ui
{
	class SLWidgetNumberKeypad;
}

class SLKEYBOARD_EXPORT SLNumberKeypad :public QWidget
{
	Q_OBJECT
	explicit SLNumberKeypad(QWidget *parent = 0);
	~SLNumberKeypad();

	SLNumberKeypad(const SLNumberKeypad& kObj) = delete;
	SLNumberKeypad& operator=(const SLNumberKeypad& kObj) = delete;

	static SLNumberKeypad *s_this;
	Ui::SLWidgetNumberKeypad *ui;

public:
	static SLNumberKeypad* getInstance();
	static void release();

private:


	
};





