import sys
import os
import subprocess
import platform
import shutil

with open('config.txt') as file:
    for line in file:
        cmake_path = line.strip().split("=")[1]

def build(build_type):
    try:
        os.mkdir("build")
    except:
        pass
        
    os.chdir("build")
    args = " -DCMAKE_BUILD_TYPE=" + build_type + " -DCMAKE_PREFIX_PATH=" + cmake_path + " .."

    if platform.system() == "Windows":
        args = "cmake -G \"NMake Makefiles\"" + args
        args2 = "mt.exe -manifest ../bin/RubiksCube.exe.manifest -outputresource:../bin/RubiksCube.exe;1"
        subprocess.run(args, shell=True)
        subprocess.run("nmake", shell=True)
        subprocess.run(args2, shell=True)
        os.remove("../bin/RubiksCube.exe.manifest")
    else:
        args = "cmake -G \"Unix Makefiles\"" + args
        subprocess.run(args, shell=True)
        subprocess.run("make", shell=True)
        
    os.chdir("..")

if sys.argv[1] == "init":
    subprocess.run("git submodule update --init --recursive", shell=True)
    os.chdir("thirdparty/boost")
    if platform.system() == "Windows":
        subprocess.run("bootstrap", shell=True)
    else:
        subprocess.run("bootstrap.sh", shell=True)
    subprocess.run("b2 headers", shell=True)
    os.chdir("../..")

if sys.argv[1] == "release":
    build("release")

if sys.argv[1] == "debug":
    build("debug")

if sys.argv[1] == "clean":
    shutil.rmtree("build", ignore_errors=True)
    os.mkdir("build")
    shutil.rmtree("bin", ignore_errors=True)
    os.mkdir("bin")