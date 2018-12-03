Import("env", "projenv")
import string, os, shutil

PROJECT_DIR = projenv['PROJECT_DIR']
PROJECT_NAME = projenv['PROJECT_DIR'].rsplit('\\', 1)[1]
SOURCE_FILE = os.path.join(projenv['PROJECTSRC_DIR'], "main.cpp")
ARDUINO_DIR = os.path.join(PROJECT_DIR, "..\..", PROJECT_NAME)
INO_FILE = PROJECT_NAME + ".ino"
ARDUINO_INO = os.path.join(ARDUINO_DIR, INO_FILE)
if os.path.exists(ARDUINO_DIR) is False:
    print "Creating Arduino directory."
    os.mkdir(ARDUINO_DIR)

if os.path.isfile(ARDUINO_INO) is False:
    print "Creating Arduino .ino file"
    open(ARDUINO_INO, 'w').close()


shutil.copy(SOURCE_FILE, ARDUINO_INO)        