CC = g++
LIBS = 
LDFLAGS = -Wall -O2

SRCS_MP3 = ../source/Mp3File/CMp3File.cpp ../source/Mp3File/CMpegFrame.cpp
SRCS_WAVE_FORM = ../source/WaveForm/BWaveForm.cpp

#Test code SRC
SRCS_TEST_CODE = ./test_CMp3File.cpp

#Outfilename
OUTFILE = ./test_Mp3FileOperator

default:
	$(CC) $(LDFLAGS) -o $(OUTFILE) $(LIBS) $(SRCS_TEST_CODE) $(SRCS_WAVE_FORM) $(SRCS_MP3)

clean:
	rm $(OUTFILE)

