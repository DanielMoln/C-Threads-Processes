import os
import SCons.Script
from glob import glob

# Setup GCC build environment
env = Environment(
    CC='gcc',
    CXX='g++',
)

env.Append(CFLAGS=['-pthread', '-g', '-O0', '-Wall', '-Wextra', '-fdiagnostics-color=always', '-std=c11'])  # -g = debug info, -O0 = no optimization, -Wall/-Wextra = more warnings, -fdiagnostics-color=always = colored diagnostics, -std=c11 = C standard

print("Environment successfully created with gcc.")

# Find source files
src_files = Glob("src/*.c")

# Setup include dirs for header files
base_dir = os.getcwd()
include_dirs = [
    "include",
]

for file_path in glob(os.path.join(base_dir, "include/*.h"), recursive=True):
    include_dirs.append(os.path.relpath(os.path.dirname(file_path), base_dir))

env.Append(CPPPATH=list(set(include_dirs)))

# Linker libraries and dependencies
# Windows specific libraries are removed as this is now a GCC build.
# If you need platform-specific libraries, you'll need to handle them conditionally.
env.Append(LIBPATH=[])
env.Append(LIBS=[])

# Set the build directory
build_dir = "build"

# Ensure build directory exists
if not os.path.exists(build_dir):
    os.makedirs(build_dir)

# Configure object file directory
env['OBJPREFIX'] = os.path.join(build_dir, '')  # Trailing slash important
env['OBJSUFFIX'] = '.o'  # GCC uses .o for object files

# Build the program with object files in build directory
program = env.Program(
    target=os.path.join(build_dir, "MyApp"),
    source=src_files,
)

AlwaysBuild(program)