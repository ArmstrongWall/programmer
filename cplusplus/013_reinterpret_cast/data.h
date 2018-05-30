//
// Created by wzq on 18-5-30.
//

#ifndef INC_13_REINTERPRET_CAST_DATA_H
#define INC_13_REINTERPRET_CAST_DATA_H

static constexpr size_t BUFFER_SIZE = 2048;
uint8_t _buffer[BUFFER_SIZE] = {0};

struct VehicleState {
    int32_t id;
    int64_t time_stamp;
    int32_t gps_level;
    float steering_angle = 0.0f;
    float forward_speed = 0.0f;
    int32_t current_gear;

    VehicleState(int32_t id0,int64_t time_stamp0):id(id0),time_stamp(time_stamp0)
    {}
};

#endif //INC_13_REINTERPRET_CAST_DATA_H
