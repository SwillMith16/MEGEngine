#ifndef TIMER_H
#define TIMER_H

#include "common.h"

namespace MEGEngine {
    /**
     * @class   TimerKey
     * @brief   A key class to grant write access to specific variables in the Timer class. Any friend functions can use
     *          the key to access selected private Timer variables.
     */
    class ENGINE_API TimerKey {
    private:
        friend int main();
        TimerKey() = default;
    };

    /**
     * @class   Timer
     * @brief   A class that can be used for synchronised timing throughout the application.
     */
    class ENGINE_API Timer {
    public:
        /**
         * @brief   Gets the time taken to render the previous frame. Used for synchronising timing regardless of FPS and
         *          loop speeds.
         * @return  float deltaTime
         */
        float deltaTime();

        static void processTime(TimerKey key);

        static float FPS;

    private:
        static float _deltaTime;
        static float lastTime;
    };

    inline Timer Time;
}



#endif //TIMER_H