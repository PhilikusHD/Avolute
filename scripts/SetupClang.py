import os
import subprocess
import sys
import platform
import time
import shutil

import scripts.Utils as Utils
from scripts.Utils import print_colored

# Class for managing Clang configuration and validation
class ClangConfiguration:
    requiredClangVersion = "16.0.0"

    @classmethod
    def Validate(cls):
        if not cls.CheckClangInstallation():
            print_colored("Clang is not installed or has an incompatible version. Engine needs clang >= 16.0.0", 31)
            cls.InstallClang()
    
    @classmethod
    def CheckClangInstallation(cls):
        try:
            # Check Clang version
            clangVersion = subprocess.check_output(["clang", "--version"], text=True)
            clangVersion = clangVersion.strip().split()[2]
            
            if clangVersion >= cls.requiredClangVersion:
                print_colored(f"Clang {clangVersion} is installed.", 32)
                return True
            else:
                print_colored(f"Clang {cls.requiredClangVersion} is required but version {clangVersion} is installed.", 33)
                return False
        except FileNotFoundError:
            return False
    
    @classmethod
    def InstallClang(cls):
        
        permissionGranted = False
        while not permissionGranted:
            reply = input(f"Would you like to install Clang {cls.requiredClangVersion}? [Y/N]: ").lower().strip()[:1]
            if reply == 'n':
                return
            
            permissionGranted = (reply == 'y')
        
        if sys.platform.startswith("win"):
            # Install MSYS2 if not already installed
            cls.InstallMSYS2()

            # Update MSYS2 key
            cls.UpdateMSYS2Keys()

            # Use MSYS2 to install Clang
            msys2_path = "C:/msys64"
            pacman_command = f"{msys2_path}/usr/bin/bash -lc 'pacman -Sy mingw-w64-x86_64-clang'"

            try:
                subprocess.run(pacman_command, shell=True, check=True)
                print_colored(f"Clang {cls.requiredClangVersion} has been installed successfully.", 32)
            except subprocess.CalledProcessError:
                print_colored(f"Failed to install Clang {cls.requiredClangVersion}. Please install it manually (https://github.com/llvm/llvm-project/releases/tag/llvmorg-16.0.0)", 31)

            # Add the installed Clang to PATH on Windows
            try:
                clang_path = os.path.join(msys2_path, "mingw64", "bin")
                os.environ["PATH"] = clang_path + os.pathsep + os.environ["PATH"]
                print_colored("Clang has been added to PATH.", 32)
            except KeyError:
                print_colored("Failed to add Clang to PATH. Please add it manually.", 31)

    @staticmethod
    def InstallMSYS2():
        # Download and install MSYS2
        msys2_installer = "https://github.com/msys2/msys2-installer/releases/download/2023-07-18/msys2-x86_64-20230718.exe"
        msys2_path = "C:/msys64"
        if not os.path.exists(msys2_path):
            # Download the MSYS2 installer to the current directory
            msys2_installer = "https://github.com/msys2/msys2-installer/releases/download/2023-07-18/msys2-x86_64-20230718.exe"
            msys2_installer_filename = os.path.basename(msys2_installer)
            msys2_installer_path = "Raven/vendor/" + msys2_installer_filename


            print("Downloading MSYS2 installer...")
            Utils.DownloadFile(msys2_installer, msys2_installer_path)

            # Run the installer
            print_colored("Running installer...", 36)
            os.system(os.path.abspath(msys2_installer_path))

            # Prompt the user to continue after the installer completes
            print_colored(input("Press Enter to continue after MSYS2 installation..."), 36)

            print_colored("MSYS2 installed successfully.", 32)
        else:
            print_colored("MSYS2 is already installed.", 32)
    
    @staticmethod
    def UpdateMSYS2Keys():
        msys2_path = "C:/msys64"
        subprocess.run(f"{msys2_path}/usr/bin/bash -lc 'pacman-key --init'", shell=True, check=True)
        subprocess.run(f"{msys2_path}/usr/bin/bash -lc 'pacman-key --refresh-keys'", shell=True, check=True)

if __name__ == "__main__":
    ClangConfiguration.Validate()

