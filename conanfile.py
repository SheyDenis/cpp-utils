import logging

from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, cmake_layout

# pylint: disable=missing-class-docstring,missing-function-docstring,not-callable


def _setup_logger(log_level: int = logging.DEBUG) -> logging.Logger:
    logging.basicConfig(format='[%(asctime)s][%(levelname)s] %(message)s', level=log_level)
    return logging.getLogger()


logger = _setup_logger()


class CppUtilsConanFile(ConanFile):
    generators = 'CMakeDeps'
    settings = 'os', 'compiler', 'build_type', 'arch'

    def configure(self):
        pass

    def build_requirements(self):
        self.tool_requires('cmake/[>=3.21.0]')

    def requirements(self):
        self.requires('catch2/3.5.0')
        self.requires('fmt/10.2.1')
        self.requires('trompeloeil/46')

    def layout(self):
        cmake_layout(self, src_folder='src')

    def generate(self):
        tc = CMakeToolchain(self)
        tc.user_presets_path = False
        tc.generate()
