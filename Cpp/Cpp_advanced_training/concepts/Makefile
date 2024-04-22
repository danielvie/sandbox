SUBDIRS=$(shell for d in [[:lower:]]* ; do test -d $$d && echo $$d; done)

all:
	for d in $(SUBDIRS) ; do make -C $$d; done

clean:
	for d in $(SUBDIRS) ; do make -C $$d clean; done
