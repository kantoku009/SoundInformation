/**
 * @file	CReadSample16.h
 * @brief	WAVEファイルのサンプル値を読み込むクラス.
 */

#ifndef __CREADSAMPLE16_H__
#define __CREADSAMPLE16_H__

#include <fstream>
using namespace std;

#include "IReadSample.h"

/**
 * @brief	WAVEファイルのサンプル値を読み込むクラス.
 */
class CReadSample16 : public IReadSample
{
public:
	/**
	 * @brief	コンストラクタ.
	 */
	CReadSample16()
	{
		m_shBitsPerSample = 16;
	}
	
	/**
	 * @brief	デストラクタ.
	 */
	virtual ~CReadSample16(){ }

	/**
	 * @brief	WAVEファイルに書き込み.
	 * @param	const string i_strFileName	ファイル名.
	 * @return	正規化されたサンプル値.
	 */
	double read(ifstream& i_cFileStream);
};

#endif	//__CREADSAMPLE16_H__

