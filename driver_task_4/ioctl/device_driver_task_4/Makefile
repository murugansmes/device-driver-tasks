SUBDIRS := $(wildcard */.)
objects :=$(wildcard */*.ko)

all: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@
	
.PHONY:	all $(SUBDIRS)

clean:
	rm -rfv  */*.o */*.order */*.symvers */*.cmd */*.ko */*.mod.c */output
	
