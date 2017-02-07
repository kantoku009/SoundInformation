/**
 * @file	CSampleOperator8.h
 * @brief	WAVEファイルのサンプル値を読み込むクラス.
 */

#ifndef __CSAMPLEOPERATOR8_H__
#define __CSAMPLEOPERATOR8_H__

#include <fstream>
using namespace std;

#ifndef __ISAMPLEOPERATOR_H__
#include "ISampleOperator.h"
#endif

/**
 * @brief	WAVEファイルのサンプル値を読み込むクラス.
 */
class CSampleOperator8 : public ISampleOperator
{
public:
	/**
	 * @brief	コンストラクタ.
	 */
	CSampleOperator8();
	
	/**
	 * @brief	デストラクタ.
	 */
	virtual ~CSampleOperator8(){ }

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

#endif	//__CSAMPLEOPERATOR8_H__

