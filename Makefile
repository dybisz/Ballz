SUBDIRS = gfx/ network/

all: $(SUBDIRS)

# TODO learn options: @
$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: $(SUBDIRS)
