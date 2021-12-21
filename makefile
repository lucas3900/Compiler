CFLAGS=-Wall -Werror -std=c++11

UFLAGS:=
# UFLAGS are up to you. I had them to control compilation at one point earlier.
TARGET=decaf

all: $(TARGET)c

# executables

$(TARGET)c: token.o lex.yy.o $(TARGET)c.o y.tab.o parsetree.o semantics.o codegen.o
	g++ -o $(TARGET)c token.o lex.yy.o $(TARGET)c.o y.tab.o parsetree.o semantics.o codegen.o

# object files

y.tab.o: y.tab.c token.h parsetree.h y.tab.h makefile
	g++ $(CFLAGS) $(UFLAGS) -c y.tab.c

$(TARGET)c.o: $(TARGET)c.cc $(TARGET)c.h parsetree.h token.h y.tab.h semantics.h makefile 
	g++ $(CFLAGS) $(UFLAGS) -c $(TARGET)c.cc 

token.o: token.cc token.h y.tab.h makefile
	g++ $(CFLAGS) $(UFLAGS) -c token.cc

parsetree.o: parsetree.cc parsetree.h token.h y.tab.h semantics.h makefile
	g++ $(CFLAGS) $(UFLAGS) -c parsetree.cc

semantics.o: semantics.cc semantics.h makefile
	g++ $(CFLAGS) $(UFLAGS) -c semantics.cc

codegen.o: codegen.cc codegen.h makefile
	g++ $(CFLAGS) $(UFLAGS) -c codegen.cc

lex.yy.o: lex.yy.c token.h y.tab.h makefile
	g++ $(CFLAGS) $(UFLAGS) -c lex.yy.c

# generated source code files

lex.yy.c: $(TARGET).l y.tab.h makefile
	flex $(TARGET).l

y.tab.c: $(TARGET).y makefile
	bison -o y.tab.c -d -v  $(TARGET).y

y.tab.h: $(TARGET).y makefile
	bison -o y.tab.c -d -v  $(TARGET).y 


# cleanup

clean:
	rm -f $(TARGET)c *.o lex.yy.c y.tab.[c,h] y.output *.j *.class codegen/*.j codegen/*.class


