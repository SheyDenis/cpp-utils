import logging

from conan import ConanFile
from conan.tools.build import check_min_cppstd
from conan.tools.cmake import CMakeDeps, CMakeToolchain, cmake_layout

from scripts.get_project_version import get_project_version

# pylint: disable=missing-class-docstring,missing-function-docstring


def _setup_logger(log_level: int = logging.DEBUG) -> logging.Logger:
    logging.basicConfig(format='[%(asctime)s][%(levelname)s] %(message)s', level=log_level)
    return logging.getLogger()


logger = _setup_logger()


class CppUtilsConanFile(ConanFile):
    name = 'cpp-utils'
    url = 'https://github.com/SheyDenis/cpp-utils'
    license = 'Unlicense'
    settings = 'os', 'compiler', 'build_type', 'arch'

    def set_version(self):
        self.version = get_project_version()

    def configure(self):
        pass

    def build_requirements(self):
        self.tool_requires('cmake/[>=3.16.0]')

        self.requires('catch2/3.5.0')
        self.requires('trompeloeil/46')

    def requirements(self):
        self.requires('fmt/10.2.1')

    def layout(self):
        cmake_layout(self, src_folder='src')

    def validate(self):
        check_min_cppstd(self, cppstd='17', gnu_extensions=False)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()

        tc = CMakeToolchain(self)
        tc.user_presets_path = False
        tc.generate()
