#pragma once
#include "googlepinyin.h"

class SLGooglePinYin
{
public:
	SLGooglePinYin();
	~SLGooglePinYin();

	/**
	 * \brief 获取匹配列表
	 * \return 匹配列表
	 */
	QVector<QString> GetAllCandidate() const;
	
	/**
	 * \brief 获取当前匹配列表
	 * \return 匹配列表
	 */
	QVector<QString> GetCurCandidate() const;

	/**
	 * \brief 选择匹配结果
	 * \param id 序号
	 * \return 匹配完成返回结果，匹配未完成返回空
	 */
	QString Choose(const unsigned &id) const;

	/**
	 * \brief 退格
	 */
	void BackSpace() const;
	
	/**
	 * \brief 获取临时字符串
	 * \return 返回临时字符串
	 */
	QString GetTempStr() const;

	/**
	 * \brief 添加字符串
	 * \param c 字符串
	 */
	void PushBack(const QString &c);

	/**
	 * \brief 取消拼写
	 */
	void Cancel() ;

	/**
	 * \brief 上一页
	 */
	void PrevPage() ;

	/**
	 * \brief 下一页
	 */
	void NextPage();

	/**
	 * \brief 能不能下一页
	 */
	bool CanNext();

	/**
	 * \brief 能不能上一页
	 */
	bool CanPrev();
private:
	GooglePinyin *m_google;
};

