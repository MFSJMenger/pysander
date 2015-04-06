include ../config.h

install:
	$(PYTHON) setup.py install $(PYTHON_INSTALL)

clean:
	/bin/rm -fr build/

skip:
	@echo ""
	@echo "Skipping installation of pysander."
	@echo ""

