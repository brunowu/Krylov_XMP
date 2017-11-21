MAKE = make
SUBDIRS = ERAM GMRES

all:
	@for a in $(SUBDIRS); do \
	echo "======Processing folder $$a====="; \
	${MAKE} -C $$a all || exit 1; \
	done
	@echo "======$$a completed====="
