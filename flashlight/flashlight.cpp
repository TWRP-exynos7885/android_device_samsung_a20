// Simple code to symlink our flashlight sysfs

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <sys/stat.h>

const int MAX_BRIGHTNESS = 1;
const std::string TARGET_FLASHLIGHT_PATH = "/system/flashlight";
const std::string FLASHLIGHT_SYSFS = "/sys/devices/virtual/camera/flash/rear_torch_flash";

bool mkdirp(const std::string& path) {
    mode_t mode = S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;
    if (path[0] == '\0') {
        return false;
    }

    char* p = const_cast<char*>(path.c_str());

    while (*p != '\0') {
        p++;
        while (*p != '\0' && *p != '/') p++;
        char v = *p;
        *p = '\0';
        if (mkdir(path.c_str(), mode) != 0 && errno != EEXIST) {
            *p = v;
            return false;
        }
        *p = v;
    }

    return true;
}

int main() {
    // Create all parent directories
    if (!mkdirp(TARGET_FLASHLIGHT_PATH)) {
        std::cerr << "E: Failed to create parent directories." << std::endl;
        return 1;
    }

    // Initialize max brightness with defined value
    std::string maxBrightnessFilePath = TARGET_FLASHLIGHT_PATH + "/max_brightness";
    if (access(maxBrightnessFilePath.c_str(), F_OK) != 0) {
        std::ofstream maxBrightnessFile(maxBrightnessFilePath.c_str());
        if (!maxBrightnessFile.is_open()) {
            std::cerr << "E: Failed to open max_brightness file." << std::endl;
            return 1;
        }
        maxBrightnessFile << MAX_BRIGHTNESS;
        maxBrightnessFile.close();
    } else {
        std::cout << "I: max_brightness already initialized." << std::endl;
    }

    // Symlink current brightness sysfs
    std::string symlinkPath = TARGET_FLASHLIGHT_PATH + "/brightness";
    if (access(symlinkPath.c_str(), F_OK) != 0) {
        if (access(FLASHLIGHT_SYSFS.c_str(), F_OK) != 0) {
            std::cerr << "E: Flashlight sysfs does not exist." << std::endl;
            return 1;
        }

        if (symlink(FLASHLIGHT_SYSFS.c_str(), symlinkPath.c_str()) != 0) {
            std::cerr << "E: Failed to create symlink." << std::endl;
            return 1;
        }
    } else {
        std::cout << "I: brightness already initialized." << std::endl;
    }
    return 0;
}
