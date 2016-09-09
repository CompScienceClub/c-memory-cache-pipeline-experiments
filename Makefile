LOCATION  = src/performance_tests
OPT_FLAGS = -O3 -msse2
PREAMBLE  = rm -rf _build; mkdir _build 
OCAML_VER = 4.02.3
OCAML_LIB = $(SHELL ~)/.opam/$(OCAML_VER)/lib/ocaml
OCAML_OPT = -O3


cache_line_no_opt:
	$(PREAMBLE)
	cp $(LOCATION)/cache_line_no_opt.c _build
	cd _build && gcc cache_line_no_opt.c -o cache_line
	cp _build/cache_line .

cache_line_opt:
	$(PREAMBLE)
	cp $(LOCATION)/cache_line_opt.c _build
	cd _build && gcc cache_line_opt.c $(OPT_FLAGS) -o cache_line
	cp _build/cache_line .

cache_size:
	$(PREAMBLE)
	cp $(LOCATION)/cache_size.c _build
	cd _build && gcc cache_size.c $(OPT_FLAGS) -o cache_size
	cp _build/cache_size .

pipeline_no_opt:
	$(PREAMBLE)
	cp $(LOCATION)/pipeline_no_opt.c _build
	cd _build && gcc pipeline_no_opt.c -o pipeline
	cp _build/pipeline .

pipeline_opt:
	$(PREAMBLE)
	cp $(LOCATION)/pipeline_opt.c _build
	cd _build && gcc pipeline_opt.c $(OPT_FLAGS) -o pipeline
	cp _build/pipeline .

pipeline2_no_opt:
	$(PREAMBLE)
	cp $(LOCATION)/pipeline2.c _build
	cd _build && gcc pipeline2.c -o pipeline
	cp _build/pipeline .

pipeline2_opt:
	$(PREAMBLE)
	cp $(LOCATION)/pipeline2.c _build
	cd _build && gcc pipeline2.c $(OPT_FLAGS) -o pipeline
	cp _build/pipeline .

thread:
	$(PREAMBLE)
	cp $(LOCATION)/thread.c _build
	cd _build && gcc -lpthread thread.c $(OPT_FLAGS) -o thread
	cp _build/thread .

ocaml_native:
	$(PREAMBLE)
	cp src/ocaml_integration/ocaml_native* _build
	cd _build && ocamlfind ocamlopt ocaml_native.ml -package bigarray -linkpkg -o ocaml
	cp _build/ocaml .

ocaml_no_opt:
	$(PREAMBLE)
	cp src/ocaml_integration/ocaml_no_opt*  _build
	cd _build && gcc -c ocaml_no_opt_c.c -I$(OCAML_LIB)
	cd _build && ocamlfind ocamlopt ocaml_no_opt_ml.ml -package bigarray -linkpkg -cclib ocaml_no_opt_c.o -o ocaml
	cp _build/ocaml .

ocaml_opt:
	$(PREAMBLE)
	cp src/ocaml_integration/ocaml_opt*  _build
	cd _build && gcc -c $(OPT_FLAGS) ocaml_opt_c.c -I$(OCAML_LIB)
	cd _build && ocamlfind ocamlopt ocaml_opt_ml.ml $(OCAML_OPT) -package bigarray -linkpkg -cclib ocaml_opt_c.o -o ocaml
	cp _build/ocaml .

clean:
	rm -rf _build
	rm -rf cache_line cache_size pipeline thread ocaml

