CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		src/main.o src/Base64.o src/Config.o src/CSProcessor.o src/JabberTerminal.o src/Process.o src/PipeProcess.o src/SystemException.o src/TerminalProcess.o

LIBS =	-lgloox -lutil -lpthread

TARGET =	jabber-terminal

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
