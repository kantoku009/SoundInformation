/**
 * @file	CSampleOperatorOther.h
 * @brief	WAVEファイルのサンプル値を読み込むクラス.
 */

#ifndef __CSAMPLEOPERATOROTHER_H__
#define __CSAMPLEOPERATOROTHER_H__

#include <fstream>
using namespace std;

#ifndef __ISAMPLEOPERATOR_H__
#include "ISampleOperator.h"
#endif

/**
 * @brief	WAVEファイルのサンプル値を読み込むクラス.
 */
class CSampleOperatorOther : public ISampleOperator
{
public:
	/**
	 * @brief	コンストラクタ.
	 */
	CSampleOperatorOther();
	
	/**
	 * @brief	デストラクタ.
	 */
	virtual ~CSampleOperatorOther(){ }

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

#endif	//__CSAMPLEOPERATOROTHER_H__

