
.PHONY: all data_lib app clean

all: data_lib app

data_lib:
	$(MAKE) -C libs/data_lib -f Makefile.lib

app: data_lib
	$(MAKE) -f Makefile.app

clean:
	$(MAKE) -C libs/data_lib -f Makefile.lib clean
	$(MAKE) -f Makefile.app clean