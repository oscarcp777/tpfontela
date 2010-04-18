CXX := g++
CFLAGS := -g -Wall -O2
OBJ_LOGGER := StringUtils.o Logger.o Log.o
OBJ_HASH := Hash.o StringUtils.o
OBJ_PARSER := Parser.o ParserInput.o
all:	logger hash parser

#Esto corresponde a la creacion del ejecutable del logger.
logger:	$(OBJ_LOGGER)
	$(CXX) $(CFLAGS) -o log $(OBJ_LOGGER)

#Esto corresponde a la creacion del ejecutable del hash.
hash:	$(OBJ_HASH)
	$(CXX) $(CFLAGS) -o hash $(OBJ_HASH)

parser: $(OBJ_PARSER)
	$(CXX) $(CFLAGS) -o parser $(OBJ_PARSER)

clean:
	$(RM) $(OBJ_LOGGER) log
	$(RM) $(OBJ_HASH) hash

#Esto corresponde a la compilacion del Logger.
stringUtils.o:	StringUtils.cpp
		$(CXX) $(CFLAGS) -c StringUtils.cpp

logger.o:	Logger.cpp Define.h StringUtils.h
		$(CXX) $(CFLAGS) -c Logger.cpp

log.o:	Log.cpp Logger.h StringUtils.h
	$(CXX) $(CFLAGS) -c Log.cpp Logger.h

#Esto corresponde a la compilacion del Hash.
hash.o:	Hash.cpp StringUtils.h
	$(CXX) $(CFLAGS) -c Hash.cpp

#Esto corresponde a la compilacion del Parser.
parser.o: Parser.cpp
	$(CXX) $(CFLAGS) -c Parser.cpp	

parserInput.o: ParserInput.cpp
	$(CXX) $(CFLAGS) -c ParserInput.cpp


