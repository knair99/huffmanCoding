

all: 
	g++ node.cc huff.cc main.cc -o huff

clean: 
	rm -rf *o huff
