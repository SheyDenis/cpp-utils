# Define the source and header files
HEADER_FILES := $(shell find include/ tests/ -type f -iname '*.h' -or -iname '*.hpp')
SOURCE_FILES := $(shell find src/ tests/ -type f -iname '*.c' -or -iname '*.cpp')

# Define Python scripts
PYTHON_SCRIPTS := conanfile.py $(shell find scripts/ -type f -iname '*.py')

# Define the clang-format command
CLANG_FORMAT := clang-format
CLANG_FORMAT_ARGS := -style=file -i

# Define isort and yapf commands
ISORT := isort
ISORT_ARGS := --settings-file .isort
YAPF := yapf
YAPF_ARGS := -i --style .yapf_style

# Default target
all: format

# Target to format all files
format: format-headers format-source format-python

# Target to format header files
format-headers:
	$(CLANG_FORMAT) $(CLANG_FORMAT_ARGS) $(HEADER_FILES)

# Target to format source files
format-source:
	$(CLANG_FORMAT) $(CLANG_FORMAT_ARGS) $(SOURCE_FILES)

# Target to format Python scripts
format-python:
	$(ISORT) $(ISORT_ARGS) .
	$(YAPF) $(YAPF_ARGS) $(PYTHON_SCRIPTS)
