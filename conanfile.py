import logging

from conan import ConanFile

# pylint: disable=missing-class-docstring,missing-function-docstring,not-callable


def _setup_logger(log_level: int = logging.DEBUG) -> logging.Logger:
    logging.basicConfig(format='[%(asctime)s][%(levelname)s] %(message)s', level=log_level)
    return logging.getLogger()


logger = _setup_logger()


class CppUtilsConanFile(ConanFile):
    generators = 'CMakeToolchain', 'CMakeDeps'
    settings = 'os', 'compiler', 'build_type', 'arch'

    def configure(self):
        pass

    def build_requirements(self):
        self.tool_requires('cmake/[>=3.21.0]')

    def requirements(self):
        self.requires('catch2/3.5.0')
        self.requires('fmt/10.2.1')
        self.requires('spdlog/1.12.0')
        self.requires('trompeloeil/46')

    def layout(self):
        self.folders.source = 'src'
        self.folders.build = 'build'
        self.folders.install = 'install'
        self.folders.generators = 'build/generators'
