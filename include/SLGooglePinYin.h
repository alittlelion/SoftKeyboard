#pragma once
#include "googlepinyin.h"

class SLGooglePinYin
{
public:
	SLGooglePinYin();
	~SLGooglePinYin();

	/**
	 * \brief ��ȡƥ���б�
	 * \return ƥ���б�
	 */
	QVector<QString> GetAllCandidate() const;
	
	/**
	 * \brief ��ȡ��ǰƥ���б�
	 * \return ƥ���б�
	 */
	QVector<QString> GetCurCandidate() const;

	/**
	 * \brief ѡ��ƥ����
	 * \param id ���
	 * \return ƥ����ɷ��ؽ����ƥ��δ��ɷ��ؿ�
	 */
	QString Choose(const unsigned &id) const;

	/**
	 * \brief �˸�
	 */
	void BackSpace() const;
	
	/**
	 * \brief ��ȡ��ʱ�ַ���
	 * \return ������ʱ�ַ���
	 */
	QString GetTempStr() const;

	/**
	 * \brief ����ַ���
	 * \param c �ַ���
	 */
	void PushBack(const QString &c);

	/**
	 * \brief ȡ��ƴд
	 */
	void Cancel() ;

	/**
	 * \brief ��һҳ
	 */
	void PrevPage() ;

	/**
	 * \brief ��һҳ
	 */
	void NextPage();

	/**
	 * \brief �ܲ�����һҳ
	 */
	bool CanNext();

	/**
	 * \brief �ܲ�����һҳ
	 */
	bool CanPrev();
private:
	GooglePinyin *m_google;
};

