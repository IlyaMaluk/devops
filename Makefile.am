AUTOMAKE_OPTIONS = foreign
bin_PROGRAMS = my_program
my_program_SOURCES = lab2/lab2/main.cpp lab2/lab2/factorial.cpp lab2/lab2/TrigonometryClass.cpp lab2/lab2/HTTP_Server.cpp lab2/lab2/Aztec.cpp
my_program_LDFLAGS -static
dist_doc_DATA = README

CTRLF_DIR=$(CURDIR)/deb/DEBIAN
CTRLF_NAME=$(CTRLF_DIR)/control

deb:

	mkdir -p $(CTRLF_DIR)
	chmod 0755 $(CTRLF_DIR)
	echo Package: $(PACKAGE) > $(CTRLF_NAME)
	echo Version: $(VERSION) >> $(CTRLF_NAME)
	echo Architecture: all >> $(CTRLF_NAME)
	echo Maintainer: $(PACKAGE_BUGREPORT) >> $(CTRLF_NAME)
	echo "Description: Hello world" >> $(CTRLF_NAME)
	make DESTDIR=$(CURDIR)/deb install

debug:
	$(foreach v, $(.VARIABLES), $(info $(v)=$($(v))))


