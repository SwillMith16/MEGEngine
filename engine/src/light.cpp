#include "MEGEngine/light.h"

namespace MEGEngine {
    void Light::setType(LightType type) {
        _type = type;
    }

    LightType Light::type() {
        return _type;
    }

    void Light::setColour(const Colour& colour) {
        _colour = colour;
        _dirty = false;
    }

    void Light::setIntensity(float intensity) {
        _intensity = intensity;
        _dirty = true;
    }

    Colour Light::colour() {
        return _colour;
    }

    float Light::intensity() {
        return _intensity;
    }

    bool Light::isDirty() const {
        return _dirty;
    }

    void Light::clearDirty() {
        _dirty = false;
    }
} // MEGEngine