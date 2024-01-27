/*
 * AM.hpp
 *
 * Attitude Manager Header
 *
 * Created on: Oct 12, 2022
 * Author(s): Anthony (anni) Luo; Dhruv Upadhyay
 */
#ifndef ZPSW3_AM_HPP
#define ZPSW3_AM_HPP

#include "AM_ControlAlgorithm.hpp"
#include "CommonDataTypes.hpp"
#include "FreeRTOS.h"
#include "semphr.h"
// #include "config_foundation.hpp"
#include "ZP_D_MotorChannel.hpp" // for testing
#ifdef TESTING
#include <gtest/gtest_prod.h>
#endif

namespace config { // for testing
    typedef enum {
        yaw,
        pitch,
        roll,
        throttle,
        NUM_CONTROL_AXIS
    } ControlAxis_t;
}

namespace AM {

typedef struct {
        MotorChannel *motorInstance;
        bool isInverted;
    } MotorInstance_t;

class AttitudeManager {
   public:
    static void setControlInputs(const AttitudeManagerInput& new_control_inputs);

    static AttitudeManagerInput getControlInputs();

    AttitudeManager(Flightmode* controlAlgorithm,  MotorInstance_t *(&motorInstances)[], uint8_t (&numMotorsPerAxis)[]);

    ~AttitudeManager();

    void runControlLoopIteration(const AttitudeManagerInput& instructions);

   private:
    #ifdef TESTING
    FRIEND_TEST(AttitudeManager, MotorInitializationAndOutput); // Remove FRIEND_TEST when updating tests with setControlInputs
    FRIEND_TEST(AttitudeManagerOutputToMotor, NoMotors);
    FRIEND_TEST(AttitudeManagerOutputToMotor, MotorsOfSameAxis);
    FRIEND_TEST(AttitudeManagerOutputToMotor, setOutputInRandomAxisOrder);
    FRIEND_TEST(AttitudeManagerOutputToMotor, InvertedTest);
    FRIEND_TEST(AttitudeManagerOutputToMotor, CombinedTest);
    #endif

    AttitudeManager();
    void outputToMotor(config::ControlAxis_t axis, uint8_t percent);

    static SemaphoreHandle_t control_inputs_mutex;

    static struct AttitudeManagerInput control_inputs;

    Flightmode *controlAlgorithm_;
    MotorInstance_t *(&motorInstances_)[];
    uint8_t (&numMotorsPerAxis_)[];
    
};

}  // namespace AM

#endif  // ZPSW3_AM_HPP
