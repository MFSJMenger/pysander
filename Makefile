include ../config.h

install:
	$(PYTHON) setup.py install --prefix $(AMBERHOME)

skip:
	@echo ""
	@echo "Skipping installation of pysander."
	@echo ""

