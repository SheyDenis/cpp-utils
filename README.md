# cpp-utils

General C++ utils and boilerplate code.

## Building

### Environment setup

```bash
poetry shell
poetry install --sync
```

### Consuming dependencies

```bash
export CONAN_HOME="$(pwd)/build"
conan profile detect
conan install . --build=missing -s build_type=Debug
```
