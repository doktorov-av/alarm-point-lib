from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake, cmake_layout
from subprocess import run

class APL(ConanFile):
    name    = "alarm-point-lib"
    version = "1.0.0"

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"

    def requirements(self):
        self.requires("nlohmann_json/3.12.0")
    def build_requirements(self):
        self.test_requires("gtest/1.16.0")

    def configure(self):
        return
    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()

        tc = CMakeToolchain(self)
        tc.cache_variables["CONAN_PROJECT_VERSION"] = self.version
        tc.cache_variables["CONAN_PROJECT_NAME"] = self.name
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()