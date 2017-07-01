/**
 * @file	CMp3File.h
 * @brief	MP3�t�@�C���𑀍삷��N���X.
 */
#ifndef __CMP3FILE_H__
#define __CMP3FILE_H__

#include <fstream>
using namespace std;

#ifndef __BWAVEFORM_H__
#include "BWaveForm.h"
#endif

// �N���X�O���錾.
class CMpegFrame;

/**
 * @brief	MP3�t�@�C���������N���X.
 */
class CMp3File : public BWaveForm
{
public:
	/**
	 * @brief	�R���X�g���N�^.
	 */
	CMp3File()
	{ 
		m_bIsDebug = true;
	}

	/**
	 * @brief	�f�X�g���N�^.
	 */
	virtual ~CMp3File(){ }

	/**
	 * @brief	MP3�t�@�C������ǂݍ���.
	 * @param	const string i_strFileName
	 * @return	����/���s.
	 */
	bool read(const string i_strFileName);

	/**
	 * @brief	MP3�t�@�C���ɏ�������.
	 * @param	const string i_strFileName
	 * @return	����/���s.
	 * @note	������.
	 */
	bool write(const string i_strFileName){ return true; }

private:
	/**
	 * @brief	MPEG Frame��T��.
	 * @param	[in ] ifstream& i_cFileStream
	 * @param	[out]CMpegFrame& i_cMpegFrame
	 * @return	����/���s.
	 */
	bool seekMpegFrame( ifstream& i_cFileStream, CMpegFrame& i_cMpegFrame );

	/**
	 * @brief
	 */
	bool seekMpegFrameAfter(ifstream& i_cFileStream, CMpegFrame& i_cMpegFrame);

	/**
	 * @brief	CRC��ǂݍ���.
	 */
	bool readCRC(ifstream& i_cFileStream, CMpegFrame& i_cMpegFrame);

	/**
	 * @brief	�T�C�h����ǂݍ���.
	 * @param	[in]ifstream& i_cFileStream
	 * @param	[in]CMpegFrame& i_cMpegFrame
	 * @param	[out]char* i_pbySide
	 */
	bool readSideInfo(ifstream& i_cFileStream, CMpegFrame& i_cMpegFrame, char* i_pbySide);

	/**
	 * @brief	���C���f�[�^��ǂݍ���.
	 */
	bool readMainData(ifstream& i_cFileStream, CMpegFrame& i_cMpegFrame);

	/**
	 * @brief	4�o�C�g���t�@�C������ǂ�.
	 * @param	[out]ifstream& i_cFileStream
	 * @param	[out]unsigned long& i_ulHeader
	 * @return	�Ȃ�.
	 */
	void read4byte(ifstream& i_cFileStream, unsigned long& i_ulHeader);

	/**
	 * @brief	CRC���`�F�b�N.
	 * @param	[in]CMpegFrame& i_cMpegFrame
	 * @param	[in]unsigned char* i_pbySide
	 * @return	true:CRC��v / false:CRC�s��v.
	 */
	bool checkCRC(CMpegFrame& i_cMpegFrame, char* i_pbySide);
	/**
	 * @brief	CRC���v�Z.
	 * @param	unsigned char* i_pbyCheckBuf
	 * @param	short i_shBytes
	 * @return	CRC�l.
	 */
	unsigned short calcCRC(unsigned char* i_pbyCheckBuf, short i_shBytes);


    //BOOL DecodeSideInfo( CBitStream* pbs, CMpegFrame* pmf );

	/**
	 * @brief	�t�@�C���|�W�V������\��. Debug�p.
	 * @param	char* i_pMessage
	 * @param	ifstream& i_cFileStream
	 * @return	�Ȃ�
	 */
	void printFilePos(char* i_pMessage, ifstream& i_cFileStream);

	/**
	 * @brief	�f�o�b�O�p�̃t���O.
	 */
	bool m_bIsDebug;
};

#endif  //__MP3FILE_H__

