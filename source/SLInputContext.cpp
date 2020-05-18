#include "SLInputContext.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QtWidgets/QMainWindow>
#include "SLWidgetKeyBoard.h"
#include "SLWidgetNumberKeypad.h"
#include "SLKeyBoardEventDispatcher.h"
#include "KeyEvent.h"

#define WINDOW_HEIGHT QApplication::desktop()->height()
SLInputContext *SLInputContext::s_this = nullptr;


SLInputContext::SLInputContext(QWidget* parent)
//: m_numberKeyBoard(SLWidgetNumberKeypad::getInstance())
	: m_keyBoard(SLWidgetKeyBoard::getInstance())
	, m_numberKeyBoard(SLWidgetNumberKeypad::getInstance())
	, m_keyEventDispatcher(new SLKeyBoardEventDispatcher)
{
	//connect(m_numberKeyBoard, &SLWidgetNumberKeypad::sigPressNormalKey, 
	//	m_keyEventDispatcher, &SLKeyBoardEventDispatcher::slotNormalKey);
	//connect(m_numberKeyBoard, &SLWidgetNumberKeypad::sigPressCustomKey, 
	//	m_keyEventDispatcher, &SLKeyBoardEventDispatcher::slotCustomKey);
	connect(m_keyBoard, &SLWidgetKeyBoard::sigPressKey,
		m_keyEventDispatcher, &SLKeyBoardEventDispatcher::slotKeyEvent);
	connect(m_numberKeyBoard, &SLWidgetNumberKeypad::sigPressKey,
		m_keyEventDispatcher, &SLKeyBoardEventDispatcher::slotKeyEvent);
	connect(m_keyBoard, &SLWidgetKeyBoard::sigChangeNumberKeyBoard,[this](QPoint position)
	{
		m_keyBoard->hide();
		m_numberKeyBoard->move(position);
		m_numberKeyBoard->show();
	});

	connect(m_numberKeyBoard, &SLWidgetNumberKeypad::sigChangeKeyBoard, [this](QPoint position)
	{
		m_numberKeyBoard->hide();
		m_keyBoard->move(position);
		m_keyBoard->show();
	});
	connect(qApp, &QApplication::focusChanged,
		this, &SLInputContext::focusChanged);
}

SLInputContext::~SLInputContext()
{
	if(m_keyEventDispatcher)
	{
		delete m_keyEventDispatcher;
		m_keyEventDispatcher = nullptr;
	}
	if (m_keyBoard)
	{
		SLWidgetKeyBoard::release();
	}
	if (m_numberKeyBoard)
	{
		SLWidgetNumberKeypad::release();
	}
}


SLInputContext* SLInputContext::getInstance()
{
	if (nullptr == s_this)
	{
		s_this = new SLInputContext;
	}
	return s_this;
}

void SLInputContext::release()
{
	if (nullptr != s_this)
	{
		delete s_this;
		s_this = nullptr;
	}
}


/*void SLInputContext::showNumberKeypad()
{
	if (!m_numberKeyBoard)
	{
		m_numberKeyBoard = SLWidgetNumberKeypad::getInstance();
	}
	m_numberKeyBoard->show();
	m_numberKeyBoard->move(m_numberKeyBoard->x(), WINDOW_HEIGHT - m_numberKeyBoard->height());
}*/

void SLInputContext::showKeyBoard()
{
	if (!m_keyBoard)
	{
		m_keyBoard = SLWidgetKeyBoard::getInstance();
	}
	m_keyBoard->show();
	m_keyBoard->move(m_keyBoard->x(), WINDOW_HEIGHT - m_keyBoard->height());

}

/*void SLInputContext::showNumberKeypad(QWidget* obj)
{
	m_keyEventDispatcher->setFocusWidget(obj);
	if (!m_numberKeyBoard)
	{
		m_numberKeyBoard = SLWidgetNumberKeypad::getInstance();
	}
	m_numberKeyBoard->show();
	m_numberKeyBoard->move(m_numberKeyBoard->x(), WINDOW_HEIGHT - m_numberKeyBoard->height());
}*/

void SLInputContext::focusChanged(QWidget* old, QWidget* now)
{
	if(nullptr == now)
	{
		//m_keyEventDispatcher->setFocusWidget(nullptr);
	}
	else
	{
		m_keyEventDispatcher->setFocusWidget(now);
		if(!m_keyBoard->isVisible() && !m_numberKeyBoard->isVisible())
		{
			m_keyBoard->focusChanged(old, now);
		}
	}
}


/*void SLInputContext::hideInputPanel()
{
	m_keyEventDispatcher->setFocusWidget(nullptr);
	if (m_numberKeyBoard)
	{
		m_numberKeyBoard->hide();
	}
}*/






