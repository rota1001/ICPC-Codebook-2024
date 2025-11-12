BUILD_DIR   = build
LATEX       = xelatex
LATEX_FLAGS = -shell-escape -output-directory $(BUILD_DIR)
export TEXMF_OUTPUT_DIRECTORY := $(BUILD_DIR)

ifeq ($(OS_NAME),linux)
    RM = rm -rf
    MKDIR = mkdir -p
    PYTHON_FOR_LATEX = printf '\\newcommand{\\pythoncmd}{%s}' '$(PYTHONCMD)' > pythoncmd.tex
else ifeq ($(OS_NAME),windows)
    RM = rmdir /s /q
    MKDIR = mkdir
    PYTHON_FOR_LATEX = echo \newcommand{\pythoncmd}{$(PYTHONCMD)} > pythoncmd.tex
endif

all: build content
	$(LATEX) $(LATEX_FLAGS) main.tex && $(LATEX) $(LATEX_FLAGS) main.tex
	$(MV) $(BUILD_DIR)$(SEP)main.pdf .

clean:
	$(RM) $(BUILD_DIR)

build:
	$(MKDIR) $(BUILD_DIR)

content:
	$(PYTHON_FOR_LATEX)
	$(PYTHONCMD) content-generator.py config.yaml $(BUILD_DIR)$(SEP)content.tex
