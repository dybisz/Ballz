SUBDIRS = gfx/ network/

all: $(SUBDIRS)

# TODO(ciecier) learn options: @
$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: $(SUBDIRS)
