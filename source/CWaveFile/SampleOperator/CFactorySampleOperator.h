/**
 * @file	CFactorySampleOperator.h
 * @brief	WAVEファイルのサンプル値をread/writeするクラスを生成する.
 */

#ifndef __CFACTORYSAMPLEOPERATOR_H__
#define __CFACTORYSAMPLEOPERATOR_H__

#ifndef __ISAMPLEOPERATOR_H__
#include "./ISampleOperator.h"
#endif

#ifndef __CSAMPLEOPERATOR8_H__
#include "./CSampleOperator8.h"
#endif

#ifndef __CSAMPLEOPERATOR16_H__
#include "./CSampleOperator16.h"
#endif

#ifndef __CSAMPLEOPERATOROTHER_H__
#include "./CSampleOperatorOther.h"
#endif

/**
 * @brief	WAVEファイルのサンプル値をread/writeするクラスを生成する.
 */
class CFactorySampleOperator
{
public:
	/**
	 * @brief	コンストラクタ.
	 */
	CFactorySampleOperator(){ }
	
	/**
	 * @brief	デストラクタ.
	 */
	virtual ~CFactorySampleOperator(){ }

	/**
	 * @brief	WAVEファイルのサンプル値をread/writeするクラスを生成する.
	 * @param	i_shBitPerSample	サンプルの量子化ビット.
	 * @return	WAVEファイルのサンプル値をread/writeするクラス.
	 */
	ISampleOperator* create(short i_shBitPerSample)
	{
		ISampleOperator* a_piSampleOperator;
		
		if(i_shBitPerSample <= 8)
		{
			// 8bitで量子化されたファイルを書き込む.
			a_piSampleOperator = &m_cSampleOperator8;
		}
		else if(i_shBitPerSample > 8 && i_shBitPerSample <= 16)
		{
			// 16bitで量子化されたファイルを書き込む.
			a_piSampleOperator = &m_cSampleOperator16;
		}
		else
		{
			// 8bit,16bit以外で量子化されたファイルを書き込む.
			a_piSampleOperator = &m_cSampleOperatorOther;
		}
		
		return a_piSampleOperator;
	}

private:
	CSampleOperator8		m_cSampleOperator8;
	CSampleOperator16		m_cSampleOperator16;
	CSampleOperatorOther	m_cSampleOperatorOther;
};

#endif	//__CFACTORYSAMPLEOPERATOR_H__

