/**
 * @file	CFactoryWriteSample.h
 * @brief	WAVEファイルのサンプル値を書き込むクラスを生成する.
 */

#ifndef __CFACTORYWRITESAMPLE_H__
#define __CFACTORYWRITESAMPLE_H__

#include "IWriteSample.h"
#include "CWriteSample8.h"
#include "CWriteSample16.h"
#include "CWriteSampleOther.h"

/**
 * @brief	WAVEファイルのサンプル値を書き込むクラスを生成する.
 */
class CFactoryWriteSample
{
public:
	/**
	 * @brief	コンストラクタ.
	 */
	CFactoryWriteSample(){ }
	
	/**
	 * @brief	デストラクタ.
	 */
	virtual ~CFactoryWriteSample(){ }

	/**
	 * @brief	WAVEファイルのサンプル値を書き込むクラスを生成する.
	 * @param	i_shSample	サンプルの量子化ビット.
	 * @return	WAVEファイルのサンプル値を書き込むクラス.
	 */
	IWriteSample* create(short i_shBitPerSample);

private:
	CWriteSample8		m_CWriteSample8;
	CWriteSample16		m_CWriteSample16;
	CWriteSampleOther	m_CWriteSampleOther;
};

#endif	//__CFACTORYWRITESAMPLE_H__

