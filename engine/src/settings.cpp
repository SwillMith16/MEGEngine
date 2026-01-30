#include "mINI/ini.h"

#include "MEGEngine/utils/log.h"
#include "MEGEngine/settings.h"

using namespace mINI;

namespace MEGEngine {

    Settings& Settings::instance() {
        static Settings instance;
        return instance;
    }

    void Settings::init() {
        INIFile file("../../../engine/engineSettings.ini");
        INIStructure ini;
        bool readSuccess = file.read(ini);
        if (!readSuccess) {
            Log(LogLevel::ERR, "Failed to read engine settings file");
            return;
        }

        general().shaderDirectory = ini.get("General").get("shaderDirectory");
        general().modelDirectory = ini.get("General").get("modelDirectory");

        graphics().maxFps = stoi(ini.get("Graphics").get("maxFps"));

        //TODO: get engine library location and store engine root directory

        _initialized = true;
    }

    bool Settings::isInitialized() {
        return _initialized;
    }

    const GeneralSettings& Settings::general() const {
        return _general;
    }
    GeneralSettings& Settings::general() {
        return _general;
    }

    const GraphicsSettings& Settings::graphics() const {
        return _graphics;
    }
    GraphicsSettings& Settings::graphics() {
        return _graphics;
    }
}