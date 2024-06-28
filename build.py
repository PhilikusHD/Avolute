import os
import subprocess
import time
import sys
from scripts.Utils import print_colored
import scripts.Setup as Setup


# Get the current working directory before changing it
current_directory = os.getcwd()

def setup_check():
    """
    Checks whether setup.py has been run before on the machine.
    If not, performs the initial setup process.
    """
    os.chdir('./scripts/')
    Setup.Validate()



def debug_or_release():
    """
    Asks the user whether to build in debug or release mode.
    Configures the project accordingly using CMake.
    """
    choice = input("Do You Want To Debug Or Release: ").capitalize()
    if choice == "Debug" or choice == "Release":

        cmake_cmd = f"cmake -G \"Ninja\" -S ../ -DCMAKE_BUILD_TYPE={choice} -B ."

        os.system(cmake_cmd)
    else:
        print_colored("Wrong Choice", 31)

def compiling():
    """
    Compiles the project using Ninja.
    """

    print_colored("Compiling...", 36)
    start = time.time()
    os.system("ninja -j 20")
    end = time.time()
    print_colored(f"Compilation finished, took: {end - start:.2f}s", 32)



def run_build_setup():
    # Compile and build the project
    compiling()

def main():
    setup_check()

    os.chdir(current_directory)

    build_start = time.time()

    try:
        print_colored("Creating build directory...", 36)
        os.mkdir("build/")
    except FileExistsError:
        print_colored("Directory exists, moving on...", 36)

    os.chdir("build/")
    # Check command-line arguments
    if len(sys.argv) > 1:
        arg = sys.argv[1].lower()
        if arg == "--release":
            cmake_cmd = "cmake -G \"Ninja\" -S ../ -DCMAKE_BUILD_TYPE=Release -B ."
            os.system(cmake_cmd)
            run_build_setup()
        elif arg == "--debug":
            cmake_cmd = "cmake -G \"Ninja\" -S ../ -DCMAKE_BUILD_TYPE=Debug -B ."
            os.system(cmake_cmd)
            run_build_setup()
        else:
            print("Invalid argument. Usage: python3 build.py [--release|--debug]")
            sys.exit(1)
    else:

        # Configure and build the project
        print_colored("Configuring project...", 36)
        debug_or_release()
        print_colored("Configuration done", 32)

        compiling()


    build_end = time.time()
    total_compilation_time = (build_end - build_start)
    print_colored(f"Total Compilation Time: {total_compilation_time:.2f}s", 35)

if __name__ == "__main__":
    main()
