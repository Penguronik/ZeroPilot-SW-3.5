#ifndef ZP_D_MOTOR_CHANNEL_HPP_
#define ZP_D_MOTOR_CHANNEL_HPP_

#include <cstdint>

class MotorChannel {
    public:
        virtual void set(uint8_t percent) = 0;

        uint8_t percent_;
};

#endif // ZP_D_MOTOR_CHANNEL_HPP_
