VFLAGS := -skip-unused -prod
VCC := gcc

dev:
	v .

release:
	v $(VFLAGS) -cc $(VCC) .

debug:
	v -d debug .