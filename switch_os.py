import os
import sys
import shutil
from pathlib import Path

print("Welcome to switch_os.py")

ostype = 0

while ostype != 1 and ostype != 2:
    print(
        """Choose OS:
        1. Mac
        2. Linux"""
    )
    user = input()
    ostype = int(user)

for folderName, subfolders, filenames in os.walk(Path.cwd()):
    # print("Folder:" + folderName)
    for subfolder in subfolders:
        # print("subfolder: " + subfolder)
        if str(subfolder) == "cmake-build-debug":
            shutil.rmtree(Path(str(Path.cwd()) + "/cmake-build-debug"))

cMakeFile = open(Path.cwd() / "CMakeLists.txt")

cMakeFileAsString = cMakeFile.read()

cMakeFileAsLines = cMakeFileAsString.split("\n")

i = 0

# Change a bunch of lines based on

for line in cMakeFileAsLines:

    if ostype == 1:
        if "#MAC" in line:
            cMakeFileAsLines[i + 1] = "add_subdirectory(/Users/edwardgallyot/JUCE bin)"

        if "#LINUX" in line:
            cMakeFileAsLines[
                i + 1
            ] = "#add_subdirectory(/home/edgallyot/drives/2TB_SSD/Documents/JUCE bin)"

    if ostype == 2:
        if "#MAC" in line:
            cMakeFileAsLines[i + 1] = "#add_subdirectory(/Users/edwardgallyot/JUCE bin)"

        if "#LINUX" in line:
            cMakeFileAsLines[
                i + 1
            ] = "add_subdirectory(/home/edgallyot/drives/2TB_SSD/Documents/JUCE bin)"

    i += 1

newCMakeLists = open(str(Path.cwd()) + "/new_CMakeLists.txt", "a")

for line in cMakeFileAsLines:
    newCMakeLists.write(line + "\n")

cMakeFile.close()
newCMakeLists.close()

shutil.move(
    str(Path.cwd()) + "/new_CMakeLists.txt", str(Path.cwd()) + "/CMakeLists.txt"
)
