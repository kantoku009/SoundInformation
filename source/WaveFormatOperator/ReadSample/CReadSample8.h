/**
 * @file	CReadSample8.h
 * @brief	WAVEファイルのサンプル値を読み込むクラス.
 */

#ifndef __CREADSAMPLE8_H__
#define __CREADSAMPLE8_H__

#include <fstream>
using namespace std;

#include "IReadSample.h"

/**
 * @brief	WAVEファイルのサンプル値を読み込むクラス.
 */
class CReadSample8 : public IReadSample
{
public:
	/**
	 * @brief	コンストラクタ.
	 */
	CReadSample8()
	{
		m_shBitsPerSample = 8;
	}
	
	/**
	 * @brief	デストラクタ.
	 */
	virtual ~CReadSample8(){ }

	/**
	 * @brief	WAVEファイルに書き込み.
	 * @param	const string i_strFileName	ファイル名.
	 * @return	正規化されたサンプル値.
	 */
	double read(ifstream& i_cFileStream);
};

#endif	//__CREADSAMPLE8_H__

