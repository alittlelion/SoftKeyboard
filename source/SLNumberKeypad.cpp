#include "SLNumberKeypad.h"
#include "ui_SLWidgetNumberKeypad.h"
SLNumberKeypad *SLNumberKeypad::s_this = nullptr;

SLNumberKeypad::SLNumberKeypad(QWidget* parent) :
	QWidget(parent),
	ui(new Ui::SLWidgetNumberKeypad)
{
	ui->setupUi(this);

	setWindowModality(Qt::WindowModal);
	setWindowFlags(windowFlags() | Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowDoesNotAcceptFocus);

}

SLNumberKeypad::~SLNumberKeypad()
{
	release();
}

SLNumberKeypad* SLNumberKeypad::getInstance()
{
	if (nullptr == s_this)
	{
		s_this = new SLNumberKeypad;
	}
	return s_this;
}

void SLNumberKeypad::release()
{
	if (nullptr != s_this)
	{
		delete s_this;
		s_this = nullptr;
	}
}