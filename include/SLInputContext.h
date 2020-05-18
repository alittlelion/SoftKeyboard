#pragma once
#include <qobject.h>

#include "slkeyboard_global.h"

class SLInputContextPrivate;
class SLKeyBoardEventDispatcher;
class SLWidgetKeyBoard;
class SLWidgetNumberKeypad;
/**
* \brief ����
*/
class SLKEYBOARD_EXPORT SLInputContext : public QObject
{
	Q_OBJECT
	explicit SLInputContext(QWidget *parent = nullptr);
	~SLInputContext();
	SLInputContext(const SLInputContext& kObj) = delete;
	SLInputContext& operator=(const SLInputContext& kObj) = delete;
	static SLInputContext *s_this;

public:
	static SLInputContext* getInstance();
	static void release();

	//void hideInputPanel();
	//show and hide invoked by Qt when editor gets focus
	//void showNumberKeypad();
	
	/**
	* \brief ��ʾ����
	*/
	void showKeyBoard();
	//void showNumberKeypad(QWidget *obj);

private slots:
	/**
	* \brief ����仯
	* \param old �ɿؼ�
	* \param now �¿ؼ�
	*/
	 void focusChanged(QWidget *old, QWidget *now);

private:
	//SLWidgetNumberKeypad *m_numberKeyBoard;
	SLWidgetKeyBoard *m_keyBoard;
	SLWidgetNumberKeypad *m_numberKeyBoard;
	SLKeyBoardEventDispatcher *m_keyEventDispatcher;
};

