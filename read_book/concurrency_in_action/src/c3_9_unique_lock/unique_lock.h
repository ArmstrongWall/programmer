//
// Created by wzq on 18-10-20.
//

#ifndef CONCURRENCYINACTION_UNIQUE_LOCK_H
#define CONCURRENCYINACTION_UNIQUE_LOCK_H

#include <mutex>
#include <thread>
#include <chrono>

struct Box {
    explicit Box(int num) : num_things{num} {}

    int num_things;
    std::mutex m;
};


void unique_lock_demo();

#endif //CONCURRENCYINACTION_UNIQUE_LOCK_H
