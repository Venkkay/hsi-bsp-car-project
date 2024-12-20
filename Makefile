
.PHONY: all data_lib app clean

all: data_lib app

data_lib:
	$(MAKE) -C libs/data_lib -f datalib_Makefile

app: data_lib
	$(MAKE) -f app_Makefile

clean:
	$(MAKE) -C libs/data_lib -f datalib_Makefile clean
	$(MAKE) -f app_Makefile clean