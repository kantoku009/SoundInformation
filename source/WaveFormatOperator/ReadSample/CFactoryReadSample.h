/**
 * @file	CFactoryReadSample.h
 * @brief	WAVEファイルのサンプル値を書き込むクラスを生成する.
 */

#ifndef __CFACTORYREADSAMPLE_H__
#define __CFACTORYREADSAMPLE_H__

#include "IReadSample.h"
#include "CReadSample8.h"
#include "CReadSample16.h"
#include "CReadSampleOther.h"

/**
 * @brief	WAVEファイルのサンプル値を書き込むクラスを生成する.
 */
class CFactoryReadSample
{
public:
	/**
	 * @brief	コンストラクタ.
	 */
	CFactoryReadSample(){ }
	
	/**
	 * @brief	デストラクタ.
	 */
	virtual ~CFactoryReadSample(){ }

	/**
	 * @brief	WAVEファイルのサンプル値を書き込むクラスを生成する.
	 * @param	i_shBitPerSample	サンプルの量子化ビット.
	 * @return	WAVEファイルのサンプル値を書き込むクラス.
	 */
	IReadSample* create(short i_shBitPerSample);

private:
	CReadSample8		m_CReadSample8;
	CReadSample16		m_CReadSample16;
	CReadSampleOther	m_CReadSampleOther;
};

#endif	//__CFACTORYREADSAMPLE_H__

