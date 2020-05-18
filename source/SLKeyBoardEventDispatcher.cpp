#include "SLKeyBoardEventDispatcher.h"

#include "KeyEvent.h"

SLKeyBoardEventDispatcher::SLKeyBoardEventDispatcher(QObject *parent) 
	: QObject(parent)
	, m_focus(nullptr)
{
}

void SLKeyBoardEventDispatcher::setFocusWidget(QWidget* obj)
{
	m_focus = obj;
}

void SLKeyBoardEventDispatcher::slotKeyEvent(KeyEvent* key_event)
{
	if (GetFocusWidget())
	{
		key_event->sendEvent(reinterpret_cast<QObject*>(GetFocusWidget()));
	}
}


QWidget* SLKeyBoardEventDispatcher::GetFocusWidget()
{
	//return QApplication::focusWidget();
	return m_focus;
}

