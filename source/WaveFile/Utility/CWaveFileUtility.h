/**
 * @file	CWaveFileUtility.h
 * @brief	SoundInformation�̃��[�e�B���e�B�N���X.
 */

#ifndef __CWAVEFILEUTILITY_H__
#define __CWAVEFILEUTILITY_H__


class CWaveFileUtility
{
public:
	CWaveFileUtility();
	~CWaveFileUtility();

	/**
	 * @brief	bit shift������.
	 * @param	short i_shBitShift
	 * @return	bit shift��������.
	 */
	static long bitShift(short i_shNumShift);
    
	/**
	 * @brief	Big-endian���ۂ��𒲂ׂ�.
	 * @param	�Ȃ�.
	 * @return	true:Big-endian / false:Little-endian
	 */
	static bool isBigEndian();
    
	/**
	 * @brief	long�^ Little-endian -> Big-endian ��ϊ�����.
	 * @param	�ϊ�����f�[�^.
	 * @return	�ϊ���������.
	 */
	static long swapLong(char* i_pbyData);

	/**
	 * @brief	short�^ Little-endian -> Big-endian ��ϊ�����.
	 * @param	�ϊ�����f�[�^.
	 * @return	�ϊ���������.
	 */
	static short swapShort(char* i_pbyData);

	/**
	 * @brief	int�^ Little-endian -> Big-endian ��ϊ�����.
	 * @param	�ϊ�����f�[�^.
	 * @return	�ϊ���������.
	 */
	static int swapInt(char* i_pbyData);

	/**
	 * @brief	4ByteData��long�^�ɕϊ�����.
	 * @param	char* data
	 * @return	�ϊ��������l.
	 */
	static long convert4ByteDataToLong(char* data);

	/**
	 * @brief	long�^��4ByteData�ɕϊ�����.
	 * @param	long i_lInteger
	 * @param	char* i_pbyData out����.
	 * @return	�Ȃ�.
	 */
	static void convertLongTo4ByteData(long i_lInteger, char* i_pbyData);

	/**
	 * @brief	2ByteData��short�^�ɕϊ�����.
	 * @param	char* data
	 * @return	�ϊ��������l.
	 */
	static short convert2ByteDataToShort(char* data);

	/**
	 * @brief	short�^��2ByteData�ɕϊ�����.
	 * @param	short i_shInteger
	 * @param	char* i_pbyData out����.
	 * @return	�Ȃ�.
	 */
	static void convertShortTo2ByteData(short i_shInteger, char* i_pbyData);

};

#endif	//__CWAVEFILEUTILITY_H__
