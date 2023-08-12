import os
import pathlib
import shutil

os.chdir("./../") # Change to root directory

try:
    shutil.rmtree("CMakeFiles")
    os.remove(".ninja_deps")
    os.remove(".ninja_log")
    os.remove("build.ninja")
    os.remove("cmake_install.cmake")
    os.remove("CMakeCache.txt")
except OSError as e:
    print("Error: %s - %s" % (e.filename, e.strerror))

