#pragma once
#include <qobject.h>


//SLKeyBoardEventDispatcher

class KeyEvent;

/**
* \brief 处理按键事件
*/
class SLKeyBoardEventDispatcher : public QObject
{
	Q_OBJECT

public:
	explicit SLKeyBoardEventDispatcher(QObject *parent = nullptr);

	/**
	* \brief 设置焦点控件
	* \param obj 控件
	*/
	void setFocusWidget(QWidget *obj);

public slots:
	/**
	* \brief 处理按键事件
	* \param key_event 事件
	*/
	void slotKeyEvent(KeyEvent *key_event);

private:
	QWidget* GetFocusWidget();
	QWidget *m_focus;
};
