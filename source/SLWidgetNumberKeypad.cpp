#include "SLWidgetNumberKeypad.h"
#include "ui_SLWidgetNumberKeypad.h"
#include "SLInputContext.h"
#include "SLKeyBoard.h"
#include "KeyEvent.h"
#include <qfontdatabase.h>

SLWidgetNumberKeypad *SLWidgetNumberKeypad::s_this = nullptr;

SLWidgetNumberKeypad::SLWidgetNumberKeypad(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::SLWidgetNumberKeypad)
	, m_btnGroup(new QButtonGroup)
	, m_mousePress(false)
	, m_isClose(true)
	, m_keyBoard(new SLKeyBoard())
	, m_nowWidget(nullptr)
	//, m_numberKeypad(new SLNumberKeypad())
{
	setWindowModality(Qt::WindowModal);
	setWindowFlags(windowFlags() | Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowDoesNotAcceptFocus);
	ui->setupUi(this);
	m_btnGroup->addButton(ui->btn0, 0);
	m_btnGroup->addButton(ui->btn1, 1);
	m_btnGroup->addButton(ui->btn2, 2);
	m_btnGroup->addButton(ui->btn3, 3);
	m_btnGroup->addButton(ui->btn4, 4);
	m_btnGroup->addButton(ui->btn5, 5);
	m_btnGroup->addButton(ui->btn6, 6);
	m_btnGroup->addButton(ui->btn7, 7);
	m_btnGroup->addButton(ui->btn8, 8);
	m_btnGroup->addButton(ui->btn9, 9);
	connect(m_btnGroup, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
		this, static_cast<void(SLWidgetNumberKeypad::*)(int)>(&SLWidgetNumberKeypad::slotButtonClick));


	int fontId = QFontDatabase::addApplicationFont(":/Resources/FontAwesome.otf");
	auto fontname = QFontDatabase::applicationFontFamilies(fontId).at(0);
	QFont icofont(fontname);
	icofont.setPixelSize(15);

	//
	QFont deffont;
	deffont.setPixelSize(20);
	ui->btnBackSpace->setText(QChar(0xf060));
	ui->btnClose->setText(QChar(0xf00d));
	ui->btnBackSpace->setFont(icofont);
	ui->btnClose->setFont(icofont);
	for(auto &btn : m_btnGroup->buttons())
	{
		btn->setFont(deffont);
	}
	ui->btnBack->setFont(deffont);
	ui->btnDeciaml->setFont(deffont);
	ui->btnPlusMinus->setFont(deffont);
	ui->btnEnter->setFont(deffont);
}

SLWidgetNumberKeypad::~SLWidgetNumberKeypad()
{
	if (m_btnGroup)
	{
		delete m_btnGroup;
		m_btnGroup = nullptr;
	}
	if (m_keyBoard)
	{
		delete m_keyBoard;
		m_keyBoard = nullptr;
	}
}



SLWidgetNumberKeypad* SLWidgetNumberKeypad::getInstance()
{
	if (nullptr == s_this)
	{
		s_this = new SLWidgetNumberKeypad;
	}
	return s_this;
}

void SLWidgetNumberKeypad::release()
{
	if (nullptr != s_this)
	{
		delete s_this;
		s_this = nullptr;
	}
}

void SLWidgetNumberKeypad::mouseMoveEvent(QMouseEvent* e)
{
	if (m_mousePress && (e->buttons())) {
		this->move(e->globalPos() - m_mousePoint);
		e->accept();
	}
}

void SLWidgetNumberKeypad::mousePressEvent(QMouseEvent* e)
{
	if (e->button() == Qt::LeftButton) {
		m_mousePress = true;
		m_mousePoint = e->globalPos() - this->pos();
		e->accept();
	}
}

void SLWidgetNumberKeypad::mouseReleaseEvent(QMouseEvent*)
{
	m_mousePress = false;
}

void SLWidgetNumberKeypad::slotButtonClick(int id)
{
	emit sigPressKey(m_keyBoard->ClickNumber(id));
}

void SLWidgetNumberKeypad::on_btnPlusMinus_clicked()
{//����
	emit sigPressKey(m_keyBoard->ClickSymbol(12/* - */));
}

void SLWidgetNumberKeypad::on_btnDeciaml_clicked()
{//С����
	emit sigPressKey(m_keyBoard->ClickPoint());
}

void SLWidgetNumberKeypad::on_btnBackSpace_clicked()
{
	emit sigPressKey(m_keyBoard->ClickBackSpace());
}
//
void SLWidgetNumberKeypad::focusChanged(QWidget* old_widget, QWidget* now_widget)
{
	if (nullptr == now_widget || this->isAncestorOf(now_widget))
	{
		return;
	}
	if (now_widget->inherits("QLineEdit") ||
		now_widget->inherits("QTextEdit") ||
		now_widget->inherits("QPlainTextEdit") ||
		now_widget->inherits("QSpinBox") ||
		now_widget->inherits("QDoubleSpinBox"))
	{
		if (!m_isClose || now_widget != m_nowWidget)
		{
			m_nowWidget = now_widget;
			//QPoint movePoint(deskWidth / 2 - rect().width() / 2, deskHeight - rect().height());
			//this->move(movePoint);
			//this->setVisible(false);
			this->setVisible(true);
			m_isClose = false;
		}
	}
	else
	{
		m_nowWidget = nullptr;
		this->setVisible(false);
	}
}

void SLWidgetNumberKeypad::on_btnBack_clicked()
{
	emit sigChangeKeyBoard(this->pos());
}

void SLWidgetNumberKeypad::on_btnClose_clicked()
{
	m_isClose = true;
	this->setVisible(false);
}

void SLWidgetNumberKeypad::on_btnEnter_clicked()
{
	emit sigPressKey(m_keyBoard->ClickEnter());
	on_btnClose_clicked();
}
