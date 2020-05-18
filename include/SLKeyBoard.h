#pragma once
#include <qvector.h>

class KeyEvent;
class SLGooglePinYin;
class SLKeyBoard
{
public:
  SLKeyBoard();
  ~SLKeyBoard() = default;

  void ClickCase();
  void ClickSymbolChange();
  void ClickType();
  bool GetIsCapital() const;
  bool GetIsChinese() const;
  bool GetIsSymbol() const;
  QVector<QString> GetSymbols();
  QString GetLetters() const;
  KeyEvent *ClickNumber(const int &number);
  KeyEvent *ClickLetter(const int &letter);
  KeyEvent *ClickSpace();
  KeyEvent *ClickPoint();
  KeyEvent* ClickEnter();
  KeyEvent *ClickBackSpace();
  QString ClickChinese(const int &idx);
  QVector<QString> GetCurCandidate();
  KeyEvent *ClickChBackSpace();
  QString GetChTempStr() const;
  KeyEvent *ClickInputMethod(const int &idx);
  void PrevPage();
  void NextPage();
  bool CanNext() const;
  bool CanPrev() const;
  void CancelCh();
  KeyEvent *ClickSymbol(const int &idx);
private:
  Qt::Key Id2Key(const int &letter);

  bool m_isCapital;
  bool m_isSymbol;
  bool m_isChinese;
  SLGooglePinYin *m_googlepinyin;




	
  const QString m_letters = "qwertyuiopasdfghjklzxcvbnm";
  const QString m_capitalLetters = "QWERTYUIOPASDFGHJKLZXCVBNM";
  const QVector<QString> m_symbols {
  	"~", "`", "!", "@", "#", "$", "%", "^", "&&", "*",
	"(", ")", "-", "_", "=", "+", "{", "}", "[", "]",
	";", ":", "'", "\"","\\","|","<",">","?",",",
	".","/" };
};
