#pragma once
#include <qobject.h>


//SLKeyBoardEventDispatcher

class KeyEvent;

/**
* \brief �������¼�
*/
class SLKeyBoardEventDispatcher : public QObject
{
	Q_OBJECT

public:
	explicit SLKeyBoardEventDispatcher(QObject *parent = nullptr);

	/**
	* \brief ���ý���ؼ�
	* \param obj �ؼ�
	*/
	void setFocusWidget(QWidget *obj);

public slots:
	/**
	* \brief �������¼�
	* \param key_event �¼�
	*/
	void slotKeyEvent(KeyEvent *key_event);

private:
	QWidget* GetFocusWidget();
	QWidget *m_focus;
};
