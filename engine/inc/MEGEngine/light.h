#ifndef MEGENGINEPROJECT_LIGHT_H
#define MEGENGINEPROJECT_LIGHT_H

#include "MEGEngine/colour.h"
#include "MEGEngine/common.h"
#include "MEGEngine/entity.h"


namespace MEGEngine {
    enum LightType {
        pointLight,
        spotLight,
        directionalLight,
    };

    struct ENGINE_API LightData {
        Vec3 position;
        Colour colour;
        float intensity;
        LightType type;
    };

    class ENGINE_API Light : public Entity {
    public:
        void setType(LightType type);
        LightType type();

        void setColour(const Colour& colour);
        void setIntensity(float intensity);

        Colour colour();
        float intensity();

        bool isDirty() const;
        void clearDirty();
    protected:
        Colour _colour = {1.0f, 1.0f, 1.0f, 1.0f};
        float _intensity = 1.0f;
        bool _dirty = true;
        LightType _type;
    };
} // MEGEngine

#endif //MEGENGINEPROJECT_LIGHT_H