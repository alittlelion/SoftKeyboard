#pragma once
#include <qwidget.h>
#include "slkeyboard_global.h"
#include "qbuttongroup.h"
namespace Ui
{
	class SLWidgetNumberKeypad;
}
class KeyEvent;
class SLKeyBoard;

class  SLWidgetNumberKeypad :public QWidget
{
	Q_OBJECT
	explicit SLWidgetNumberKeypad(QWidget *parent = nullptr);
	~SLWidgetNumberKeypad();

	SLWidgetNumberKeypad(const SLWidgetNumberKeypad& kObj) = delete;
	SLWidgetNumberKeypad& operator=(const SLWidgetNumberKeypad& kObj) = delete;

	static SLWidgetNumberKeypad *s_this;
	Ui::SLWidgetNumberKeypad *ui;

public:
	static SLWidgetNumberKeypad* getInstance();
	static void release();
	void focusChanged(QWidget* old_widget, QWidget* now_widget);

signals:
	void sigPressKey(KeyEvent *key);
	void sigChangeKeyBoard(QPoint position);
private slots:
	void slotButtonClick(int id);
	
    void on_btnPlusMinus_clicked();

    void on_btnDeciaml_clicked();

    void on_btnBackSpace_clicked();
	//void focusChanged(QWidget *, QWidget *);


    void on_btnBack_clicked();

    void on_btnClose_clicked();

    void on_btnEnter_clicked();

private:
	void mouseMoveEvent(QMouseEvent *e);
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *);
	
	QButtonGroup *m_btnGroup;
	bool m_mousePress;              //�����Ƿ�����
	QPoint m_mousePoint;              //�����϶��Զ���������ʱ������

	SLKeyBoard *m_keyBoard;
	bool m_isClose;
	QWidget *m_nowWidget;		///<��ǰwidget

	//SLNumberKeypad *m_numberKeypad;
};
