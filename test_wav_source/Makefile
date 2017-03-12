CC = g++
LIBS = 
LDFLAGS = -Wall -O2

#SRCS_WAVEFILE. WaveFileを扱うソースコード.
SRCS_WAVEFILE_DIR := ../source/WaveFile
include ../source/WaveFile/Makefile

#SRCS_WAVEFORM. 音声を扱うソースコード.
SRCS_WAVEFORM_DIR := ../source/WaveForm
include ../source/WaveForm/Makefile

#Test code SRC. テスト用のソースコード.
SRCS_TEST_CODE = ./test_CWaveFile.cpp


#Outfilename. 生成される実行ファイル.
OUTFILE_TEST_WAVEFORMAT_OPERATOR = ./test_WaveFileOperator

default:
	$(CC) $(LDFLAGS) -o $(OUTFILE_TEST_WAVEFORMAT_OPERATOR) $(LIBS) $(SRCS_TEST_CODE) $(SRCS_WAVEFORM) $(SRCS_WAVEFILE)

clean:
	rm $(OUTFILE_TEST_WAVEFORMAT_OPERATOR)

