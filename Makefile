
.PHONY: all data_lib app clean

all: script_lib data_lib app

script_lib:
	./tools/data_lib_generator/target/release/data_lib_generator --json applicative_data.json --dest libs/data_lib

data_lib: script_lib
	$(MAKE) -C libs/data_lib -f Makefile.lib

app: data_lib
	$(MAKE) -f Makefile.app

clean:
	$(MAKE) -C libs/data_lib -f Makefile.lib clean
	$(MAKE) -f Makefile.app clean