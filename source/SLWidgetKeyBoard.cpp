#include <qfontdatabase.h>
#include "ui_SLWidgetKeyBoard.h"
#include "SLWidgetKeyBoard.h"
#include "SLKeyBoard.h"
#include "KeyEvent.h"
#include <QButtonGroup>

SLWidgetKeyBoard *SLWidgetKeyBoard::s_this = nullptr;
SLWidgetKeyBoard::SLWidgetKeyBoard(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::SLWidgetKeyBoard)
	, m_mousePress(false)
	, m_isClose(true)
	, m_lettersBtnG(new QButtonGroup())
	, m_numbersBtnG(new QButtonGroup())
	, m_inputMethodBtnG(new QButtonGroup())
	, m_nowWidget(nullptr)
	, m_keyBoard(new SLKeyBoard())
{
	ui->setupUi(this);
	InitUi();
}

SLWidgetKeyBoard::~SLWidgetKeyBoard()
{
	if(m_keyBoard)
	{
		delete m_keyBoard;
		m_keyBoard = nullptr;
	}
	DeleteBtnGroup();
	delete ui;
}


void SLWidgetKeyBoard::InitUi()
{
	this->setWindowModality(Qt::WindowModal);
	this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint
    | Qt::WindowStaysOnTopHint | Qt::WindowDoesNotAcceptFocus);
	
	int fontId = QFontDatabase::addApplicationFont(":/Resources/FontAwesome.otf");
	auto fontname = QFontDatabase::applicationFontFamilies(fontId).at(0);
	QFont icofont(fontname);
	icofont.setPixelSize(15);

	//��������
	QFont deffont;
	deffont.setPixelSize(20);
	
	ui->btnCase->setText(QChar(0xf062));
	ui->btnBackSpace->setText(QChar(0xf060));
	ui->btnPrev->setText(QChar(0xf0d9));
	ui->btnNext->setText(QChar(0xf0da)); 
	ui->btnClose->setText(QChar(0xf00d));
	ui->btnCase->setFont(icofont);
	ui->btnBackSpace->setFont(icofont);
	ui->btnNext->setFont(icofont);
	ui->btnPrev->setFont(icofont);
	ui->btnClose->setFont(icofont);
	ui->btnSymbol->setFont(deffont);
	ui->btnSpace->setFont(deffont);
	ui->btnType->setFont(deffont);
	ui->btnEnter->setFont(deffont);
	ui->inputLabel->setFont(deffont);
	ui->btnPoint->setFont(deffont);
	ui->btnNumber->setFont(deffont);
	
	m_lettersBtnG->addButton(ui->btnq, 0);
	m_lettersBtnG->addButton(ui->btnw, 1);
	m_lettersBtnG->addButton(ui->btne, 2);
	m_lettersBtnG->addButton(ui->btnr, 3);
	m_lettersBtnG->addButton(ui->btnt, 4);
	m_lettersBtnG->addButton(ui->btny, 5);
	m_lettersBtnG->addButton(ui->btnu, 6);
	m_lettersBtnG->addButton(ui->btni, 7);
	m_lettersBtnG->addButton(ui->btno, 8);
	m_lettersBtnG->addButton(ui->btnp, 9);
	m_lettersBtnG->addButton(ui->btna, 10);
	m_lettersBtnG->addButton(ui->btns, 11);
	m_lettersBtnG->addButton(ui->btnd, 12);
	m_lettersBtnG->addButton(ui->btnf, 13);
	m_lettersBtnG->addButton(ui->btng, 14);
	m_lettersBtnG->addButton(ui->btnh, 15);
	m_lettersBtnG->addButton(ui->btnj, 16);
	m_lettersBtnG->addButton(ui->btnk, 17);
	m_lettersBtnG->addButton(ui->btnl, 18);
	m_lettersBtnG->addButton(ui->btnz, 19);
	m_lettersBtnG->addButton(ui->btnx, 20);
	m_lettersBtnG->addButton(ui->btnc, 21);
	m_lettersBtnG->addButton(ui->btnv, 22);
	m_lettersBtnG->addButton(ui->btnb, 23);
	m_lettersBtnG->addButton(ui->btnn, 24);
	m_lettersBtnG->addButton(ui->btnm, 25);

	for (auto btn : m_lettersBtnG->buttons())
	{
		btn->setFont(deffont);
	}
	connect(m_lettersBtnG, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
		this, static_cast<void(SLWidgetKeyBoard::*)(int)>(&SLWidgetKeyBoard::slotLettersClick));



	m_numbersBtnG->addButton(ui->btn0, 0);
	m_numbersBtnG->addButton(ui->btn1, 1);
	m_numbersBtnG->addButton(ui->btn2, 2);
	m_numbersBtnG->addButton(ui->btn3, 3);
	m_numbersBtnG->addButton(ui->btn4, 4);
	m_numbersBtnG->addButton(ui->btn5, 5);
	m_numbersBtnG->addButton(ui->btn6, 6);
	m_numbersBtnG->addButton(ui->btn7, 7);
	m_numbersBtnG->addButton(ui->btn8, 8);
	m_numbersBtnG->addButton(ui->btn9, 9);
	for (auto btn : m_numbersBtnG->buttons())
	{
		btn->setFont(deffont);
	}
	connect(m_numbersBtnG, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
		this, static_cast<void(SLWidgetKeyBoard::*)(int)>(&SLWidgetKeyBoard::slotNumbersClick));

	m_inputMethodBtnG->addButton(ui->btnCh0, 0);
	m_inputMethodBtnG->addButton(ui->btnCh1, 1);
	m_inputMethodBtnG->addButton(ui->btnCh2, 2);
	m_inputMethodBtnG->addButton(ui->btnCh3, 3);
	m_inputMethodBtnG->addButton(ui->btnCh4, 4);
	connect(m_inputMethodBtnG, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
		this, static_cast<void(SLWidgetKeyBoard::*)(int)>(&SLWidgetKeyBoard::slotInuputMethodClick));
	for (auto btn : m_inputMethodBtnG->buttons())
	{
		btn->setFont(deffont);
	}
	EnblePrevNextBtn();
}


void SLWidgetKeyBoard::changeEvent(QEvent* event)
{
	if (event->type() == QEvent::LanguageChange) 
	{
		ui->retranslateUi(this);
	}
	else {
		QWidget::changeEvent(event);
	}
}


void SLWidgetKeyBoard::SetSymbols()
{
	auto symbols = m_keyBoard->GetSymbols();
	int i = 0;
	for (auto btn : m_numbersBtnG->buttons())
	{
		btn->setText(symbols.at(i));
		i++;
	}
	for (auto btn : m_lettersBtnG->buttons())
	{
		if (i >= symbols.size())
		{
			btn->setText({});
		}
		else
		{
			btn->setText(symbols.at(i));
		}
		i++;
	}
}

void SLWidgetKeyBoard::EnblePrevNextBtn()
{
	ui->btnPrev->setEnabled(m_keyBoard->CanPrev());
	ui->btnNext->setEnabled(m_keyBoard->CanNext());
}

void SLWidgetKeyBoard::UpdateCandidate()
{
	auto vec = m_keyBoard->GetCurCandidate();
	auto list = m_inputMethodBtnG->buttons();
	int i = 0;
	for (auto btn : list)
	{
		if (vec.size() <= i)
		{
			btn->setText({});
		}
		else
		{
			btn->setText(QString("%1.%2").arg(i + 1).arg(vec.at(i)));
		}
		i++;
	}
	EnblePrevNextBtn();
}

void SLWidgetKeyBoard::CancelCh()
{
	ui->inputLabel->clear();
	for(auto &btn : m_inputMethodBtnG->buttons())
	{
		btn->setText({});
	}
	m_keyBoard->CancelCh();
}

void SLWidgetKeyBoard::SetLetters()
{
	int i = 0;
	for (auto btn : m_lettersBtnG->buttons())
	{
		btn->setText(m_keyBoard->GetLetters().at(i));
		i++;
	}
}

void SLWidgetKeyBoard::DeleteBtnGroup()
{
	if (m_lettersBtnG)
	{
		delete m_lettersBtnG;
		m_lettersBtnG = nullptr;
	}
	if (m_numbersBtnG)
	{
		delete m_numbersBtnG;
		m_numbersBtnG = nullptr;
	}
	if (m_inputMethodBtnG)
	{
		delete m_inputMethodBtnG;
		m_inputMethodBtnG = nullptr;
	}
}

SLWidgetKeyBoard* SLWidgetKeyBoard::getInstance()
{
	if (nullptr == s_this)
	{
		s_this = new SLWidgetKeyBoard;
	}
	return s_this;
}

void SLWidgetKeyBoard::release()
{
	if (s_this)
	{
		delete s_this;
		s_this = nullptr;
	}
}

void SLWidgetKeyBoard::focusChanged(QWidget* old_widget, QWidget* now_widget)
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

void SLWidgetKeyBoard::slotLettersClick(int id)
{
	if (m_keyBoard->GetIsChinese() && !m_keyBoard->GetIsSymbol())
	{
		ui->inputLabel->setText(m_keyBoard->ClickChinese(id));
		UpdateCandidate();
	}
	else
	{
		emit sigPressKey(m_keyBoard->ClickLetter(id));
	}
}

void SLWidgetKeyBoard::slotNumbersClick(int id)
{
	if(!ui->inputLabel->text().isEmpty())
	{
		slotInuputMethodClick(id - 1);
	}
	else
	{
		emit sigPressKey(m_keyBoard->ClickNumber(id));
	}
}

void SLWidgetKeyBoard::slotInuputMethodClick(int id)
{
	if (!m_keyBoard->GetIsChinese() || 
		m_keyBoard->GetCurCandidate().size() <= id || id < 0
		)
	{
		return;
	}
	auto result = m_keyBoard->ClickInputMethod(id);
	if (nullptr == result)
	{
		ui->inputLabel->setText(m_keyBoard->GetChTempStr());
		UpdateCandidate();
	}
	else
	{
		CancelCh();
		emit sigPressKey(result);
	}
}

void SLWidgetKeyBoard::mouseMoveEvent(QMouseEvent* event)
{
	if (m_mousePress && (event->buttons() == Qt::LeftButton))
	{
		this->move(event->globalPos() - m_mousePoint);
		event->accept();
	}
}

void SLWidgetKeyBoard::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_mousePress = true;
		m_mousePoint = event->globalPos() - this->pos();
		event->accept();
	}
}

void SLWidgetKeyBoard::mouseReleaseEvent(QMouseEvent* event)
{
	m_mousePress = false;
}


void SLWidgetKeyBoard::on_btnClose_clicked()
{
	m_isClose = true;
	this->setVisible(false);
	CancelCh();
}

void SLWidgetKeyBoard::on_btnCase_clicked()
{
	if (m_keyBoard->GetIsSymbol())
	{
		return;
	}
	m_keyBoard->ClickCase();
	if (m_keyBoard->GetIsChinese())
	{
		on_btnType_clicked();
	}
	if (m_keyBoard->GetIsCapital())
	{
		ui->btnCase->setStyleSheet("QPushButton{\
									background-color: rgb( 255 , 69 , 0);\
									color:rgb( 255 , 255 , 255);}");
	}
	else
	{
		ui->btnCase->setStyleSheet("QPushButton{\
									background-color: rgb( 255 , 255 , 255);\
									color:rgb( 0 , 0 , 0);}");
	}
	SetLetters();
}

void SLWidgetKeyBoard::on_btnSpace_clicked()
{
	emit sigPressKey(m_keyBoard->ClickSpace());
}

void SLWidgetKeyBoard::on_btnSymbol_clicked()
{
	m_keyBoard->ClickSymbolChange();
	if (m_keyBoard->GetIsSymbol())
	{
		SetSymbols();
		CancelCh();
		ui->btnSymbol->setText("abc");
	}
	else
	{
		ui->btnSymbol->setText(",./");
		SetLetters();
		int i = 0;
		for (auto btn : m_numbersBtnG->buttons())
		{
			btn->setText(QString::number(i));
			i++;
		}
	}

}

void SLWidgetKeyBoard::on_btnBackSpace_clicked()
{
	if (m_keyBoard->GetIsChinese() && !m_keyBoard->GetIsSymbol())
	{
		const auto event = m_keyBoard->ClickChBackSpace();
		if (event)
		{
			emit sigPressKey(event);
			return;
		}
		ui->inputLabel->setText(m_keyBoard->GetChTempStr());
		UpdateCandidate();
	}
	else
	{
		emit sigPressKey(m_keyBoard->ClickBackSpace());
	}
}

void SLWidgetKeyBoard::on_btnType_clicked()
{
	m_keyBoard->ClickType();
	if (m_keyBoard->GetIsChinese())
	{
		ui->btnType->setText(tr("Ch"));
	}
	else
	{
		ui->btnType->setText(tr("En"));
		CancelCh();
		
	}
	if (m_keyBoard->GetIsSymbol())
	{
		SetSymbols();
	}
}

void SLWidgetKeyBoard::on_btnEnter_clicked()
{
	emit sigPressKey(m_keyBoard->ClickEnter());
	on_btnClose_clicked();
}


void SLWidgetKeyBoard::on_btnPrev_clicked()
{
	if(!m_keyBoard->GetIsChinese())
	{
		return;
	}
	m_keyBoard->PrevPage();
	UpdateCandidate();
}

void SLWidgetKeyBoard::on_btnNext_clicked()
{
	if (!m_keyBoard->GetIsChinese())
	{
		return;
	}
	m_keyBoard->NextPage();
	UpdateCandidate();
}

void SLWidgetKeyBoard::on_btnPoint_clicked()
{
	emit sigPressKey(m_keyBoard->ClickPoint());
}

void SLWidgetKeyBoard::on_btnNumber_clicked()
{
	emit sigChangeNumberKeyBoard(this->pos());
}
