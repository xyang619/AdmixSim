CXX = g++
CXXFLAGS =	-O2 -Wall

SRCS = Segment.cpp Chrom.cpp ChromPair.cpp Population.cpp PopModel.cpp Utils.cpp Param.cpp AdmixSim.cpp

OBJS = $(SRCS:.cpp=.o)

LIBS = 

TARGET = AdmixSim

$(TARGET):	$(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)