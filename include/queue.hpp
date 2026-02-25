#ifndef QUEUE_H
#define QUEUE_H

#include "taskID.hpp"
#include "types.h"
#include "motors.hpp"
#include "imu.hpp"

#define LEFT 0
#define RIGHT 1

#define MAX_PARAMS 5
#define MAX_TASKS 9

// Type to hold Task information, uses ID for identification
struct Task{
    int ID = T_EMPTY;
    int params[MAX_PARAMS]{};

    bool completionInterrupt = false;
    int interruptID = INTR_COMPLETE;

    Task();
    Task(int args[], int numArgs,int ID);
    Task(int a,int b,int c,int d,int e, int f, int ID); 
    Task(const Task& task);
};

// Type to hold list of task, execute them & read frame time info
struct Queue{
    Task tasks[MAX_TASKS]{};

    Task * curr = &tasks[0];
    Task * next = &tasks[1];

    int iter = 0;
    int currFlag = INTR_EMPTY;

    int wheelSpeed[2]{};

    int startTime = 0ull;
    int deltaT = 1ul;
    int timeAccumulator = 0l;

    float currAngle = 0.f;
    float targetAngle = 0.f;

    float * sentinel = nullptr;
    bool sentinelSet = false;
    int sNumbers = 0;

    Queue();
    Queue(Task init[], int sz);
    ~Queue();

    void setRelative(Task task, int offset);
    void setAbsolute(Task task, int pos);
    bool pushToNextEmpty(Task task);

    void startFrame();
    void executeAction(Motor &motors, IMU &myImu);
    void endFrame();

    void beginNext();
};

#endif