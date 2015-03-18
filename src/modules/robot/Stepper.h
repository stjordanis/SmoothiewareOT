/*
      This file is part of Smoothie (http://smoothieware.org/). The motion control part is heavily based on Grbl (https://github.com/simen/grbl).
      Smoothie is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
      Smoothie is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
      You should have received a copy of the GNU General Public License along with Smoothie. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef STEPPER_H
#define STEPPER_H

#include "libs/Module.h"
#include <stdint.h>

class Block;
class Hook;
class StepperMotor;

class Stepper : public Module
{
public:
    Stepper();
    void on_module_loaded();
    void on_config_reload(void *argument);
    void on_block_begin(void *argument);
    void on_block_end(void *argument);
    void on_gcode_received(void *argument);
    void on_gcode_execute(void *argument);
    void on_play(void *argument);
    void on_pause(void *argument);
    void on_halt(void *argument);
    uint32_t main_interrupt(uint32_t dummy);
    void trapezoid_generator_reset();
    void set_step_events_per_second(float);

    void set_a_step_events_per_second(float);
    void set_b_step_events_per_second(float);
    void set_c_step_events_per_second(float);

    uint32_t trapezoid_generator_tick(uint32_t dummy);

    uint32_t a_trapezoid_generator_tick(uint32_t dummy);
    uint32_t b_trapezoid_generator_tick(uint32_t dummy);
    uint32_t c_trapezoid_generator_tick(uint32_t dummy);

    uint32_t stepper_motor_finished_move(uint32_t dummy);
    int config_step_timer( int cycles );
    void turn_enable_pins_on();
    void turn_enable_pins_off();
    uint32_t synchronize_acceleration(uint32_t dummy);

    int get_acceleration_ticks_per_second() const { return acceleration_ticks_per_second; }

    int get_a_acceleration_ticks_per_second() const { return a_acceleration_ticks_per_second; }
    int get_b_acceleration_ticks_per_second() const { return b_acceleration_ticks_per_second; }
    int get_c_acceleration_ticks_per_second() const { return c_acceleration_ticks_per_second; }

    unsigned int get_minimum_steps_per_second() const { return minimum_steps_per_second; }
    float get_trapezoid_adjusted_rate() const { return trapezoid_adjusted_rate; }
    const Block *get_current_block() const { return current_block; }

private:
    Block *current_block;
    int counters[3];
    int stepped[3];
    int offsets[3];
    float counter_alpha;
    float counter_beta;
    float counter_gamma;
    unsigned int out_bits;
    float trapezoid_adjusted_rate;

    float a_trapezoid_adjusted_rate, b_trapezoid_adjusted_rate, c_trapezoid_adjusted_rate;

    int trapezoid_tick_cycle_counter;
    int cycles_per_step_event;
    int microseconds_per_step_pulse;
    int acceleration_ticks_per_second;

    int a_acceleration_ticks_per_second;
    int b_acceleration_ticks_per_second;
    int c_acceleration_ticks_per_second;

    unsigned int minimum_steps_per_second;
    int base_stepping_frequency;
    unsigned short step_bits[3];
    int counter_increment;
    Hook *acceleration_tick_hook;

    Hook *a_acceleration_tick_hook;
    Hook *b_acceleration_tick_hook;
    Hook *c_acceleration_tick_hook;

    StepperMotor *main_stepper;

    StepperMotor *chi_stepper;
    StepperMotor *psi_stepper;
    StepperMotor *omega_stepper;

    bool ready_to_release[4];

    struct {
        bool enable_pins_status:1;
        bool force_speed_update:1;

        bool a_force_speed_update:1;
        bool b_force_speed_update:1;
        bool c_force_speed_update:1;

        bool paused:1;
        bool trapezoid_generator_busy:1;
        bool halted:1;
    };

};




#endif
