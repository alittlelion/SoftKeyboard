#pragma once
#include <qobject.h>

#include "slkeyboard_global.h"

class SLInputContextPrivate;
class SLKeyBoardEventDispatcher;
class SLWidgetKeyBoard;
class SLWidgetNumberKeypad;
/**
* \brief 键盘
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
	* \brief 显示键盘
	*/
	void showKeyBoard();
	//void showNumberKeypad(QWidget *obj);

private slots:
	/**
	* \brief 焦点变化
	* \param old 旧控件
	* \param now 新控件
	*/
	 void focusChanged(QWidget *old, QWidget *now);

private:
	//SLWidgetNumberKeypad *m_numberKeyBoard;
	SLWidgetKeyBoard *m_keyBoard;
	SLWidgetNumberKeypad *m_numberKeyBoard;
	SLKeyBoardEventDispatcher *m_keyEventDispatcher;
};

