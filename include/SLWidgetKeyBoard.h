#ifndef SLWIDGETKEYBOARD_H
#define SLWIDGETKEYBOARD_H

#include <qwidget.h>
#include "slkeyboard_global.h"


namespace Ui
{
class SLWidgetKeyBoard;
}

class SLKeyBoard;
class KeyEvent;
class QButtonGroup;

class SLWidgetKeyBoard : public QWidget
{
    Q_OBJECT

    explicit SLWidgetKeyBoard(QWidget *parent = nullptr);
    ~SLWidgetKeyBoard();
	SLWidgetKeyBoard(const SLWidgetKeyBoard& kObj) = delete;
	SLWidgetKeyBoard& operator=(const SLWidgetKeyBoard& kObj) = delete;
	static SLWidgetKeyBoard *s_this;
	Ui::SLWidgetKeyBoard *ui;

public:
	static SLWidgetKeyBoard* getInstance();
	static void release();

	void focusChanged(QWidget *old_widget, QWidget *now_widget);

signals:
	void sigPressKey(KeyEvent *key);
	void sigChangeNumberKeyBoard(QPoint position);

private slots:
	void slotLettersClick(int id);
	void slotNumbersClick(int id);
	void slotInuputMethodClick(int id);
	
    void on_btnClose_clicked();

    void on_btnCase_clicked();

    void on_btnSpace_clicked();

    void on_btnSymbol_clicked();

    void on_btnBackSpace_clicked();

    void on_btnType_clicked();

    void on_btnEnter_clicked();


    void on_btnPrev_clicked();

    void on_btnNext_clicked();

    void on_btnPoint_clicked();

    void on_btnNumber_clicked();

private:
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void changeEvent(QEvent* event);
	void InitUi();
	void SetSymbols();
	void EnblePrevNextBtn();
	void UpdateCandidate();
	void CancelCh();
	void SetLetters();
	void DeleteBtnGroup();
	bool m_mousePress;              //鼠标是否按下
	QPoint m_mousePoint;              //鼠标拖动自定义标题栏时的坐标
	bool m_isClose;

	QButtonGroup *m_lettersBtnG;	   ///<字母位置按钮
	QButtonGroup *m_numbersBtnG;	   ///<数字位置按钮
	QButtonGroup *m_inputMethodBtnG;   ///<输入法位置按钮

	QWidget *m_nowWidget;		///<当前widget
	SLKeyBoard *m_keyBoard;
};
#endif // SLWIDGETKEYBOARD_H
