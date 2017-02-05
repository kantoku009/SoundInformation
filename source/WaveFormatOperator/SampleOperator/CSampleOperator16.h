/**
 * @file	CSampleOperator16.h
 * @brief	WAVEファイルのサンプル値を読み込むクラス.
 */

#ifndef __CSAMPLEOPERATOR16_H__
#define __CSAMPLEOPERATOR16_H__

#include <fstream>
using namespace std;

#ifndef __ISAMPLEOPERATOR_H__
#include "ISampleOperator.h"
#endif

/**
 * @brief	WAVEファイルのサンプル値を読み込むクラス.
 */
class CSampleOperator16 : public ISampleOperator
{
public:
	/**
	 * @brief	コンストラクタ.
	 */
	CSampleOperator16();
	
	/**
	 * @brief	デストラクタ.
	 */
	virtual ~CSampleOperator16(){ }

	/**
	 * @brief	WAVEファイルに書き込み.
	 * @param	const string i_strFileName	ファイル名.
	 * @return	正規化されたサンプル値.
	 */
	double read(ifstream& i_cFileStream);

	/**
	 * @brief	WAVEファイルに書き込み.
	 * @param	const string i_strFileName	ファイル名.
	 * @return	成功/失敗.
	 */
	bool write(double i_dSample, ofstream& i_cFileStream);

};

#endif	//__CSAMPLEOPERATOR16_H__

