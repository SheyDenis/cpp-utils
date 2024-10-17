# Define the source and header files
HEADER_FILES := $(shell find include/ tests/ -type f -iname '*.h' -or -iname '*.hpp')
SOURCE_FILES := $(shell find src/ tests/ -type f -iname '*.c' -or -iname '*.cpp')

# Define the clang-format command
CLANG_FORMAT := clang-format
CLANG_FORMAT_ARGS := -style=file -i

# Default target
all: format

# Target to format all files
format: format-headers format-source

# Target to format header files
format-headers:
	$(CLANG_FORMAT) $(CLANG_FORMAT_ARGS) $(HEADER_FILES)

# Target to format source files
format-source:
	$(CLANG_FORMAT) $(CLANG_FORMAT_ARGS) $(SOURCE_FILES)
