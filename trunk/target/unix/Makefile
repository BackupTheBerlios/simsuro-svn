#
# Unix as target system
#

include ../app-make.in

TARGET = simsuro


UNIX_CHEADERS = \
	asuro_unix.h \
	asuro_unix_decode.h

UNIX_CSOURCES = \
	asuro_unix.c \
	asuro_unix_decode.c

UNIX_CXXHEADERS = 
UNIX_CXXSOURCES = 

UNIX_INCLUDES = -I. -I../../include

UNIX_DEFINES = -DUNIX

UNIX_LIBS = 


UNIX_COBJECTS = $(UNIX_CSOURCES:.c=.o)
UNIX_CXXOBJECTS = $(UNIX_CXXSOURCES:.cpp=.o)


CFLAGS = -ggdb -O0 $(APP_INCLUDES) $(APP_DEFINES) $(UNIX_INCLUDES) $(UNIX_DEFINES)
CXXFLAGS = -ggdb -O0 $(APP_INCLUDES) $(APP_DEFINES) $(UNIX_INCLUDES) $(UNIX_DEFINES)
LDFLAGS = 


all: unix

unix: $(APP_COBJECTS) $(APP_CXXOBJECTS) $(UNIX_COBJECTS) $(UNIX_CXXOBJECTS)
	$(CXX) $(LDFLAGS) $(APP_LIBS) $(UNIX_LIBS) -o $(TARGET) $(UNIX_COBJECTS) $(UNIX_CXXOBJECTS) $(APP_COBJECTS) $(APP_CXXOBJECTS)

clean:
	$(RM) $(APP_COBJECTS) $(APP_CXXOBJECTS) $(UNIX_COBJECTS) $(UNIX_CXXOBJECTS) $(TARGET)

