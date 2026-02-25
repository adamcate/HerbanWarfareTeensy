#include "queue.hpp"
#include "motors.hpp"
#include "angles.hpp"

inline float lerp(float a, float b, float t)
{
    if (t > 1.f) t = 1.f;
    return a + t * (b - a);
}

Task::Task(){}

Task::Task(int args[], int numArgs,int ID){
    if (numArgs > MAX_PARAMS) return;
    for(int i = 0; i < numArgs; ++i)
        params[i] = args[i];
    this->ID = ID;
}
Task::Task(int a,int b,int c,int d,int e, int f, int ID){
    params[0] = a;
	params[1] = b;
	params[2] = c;
	params[3] = d;
	params[4] = e;
    params[5] = f;
    this->ID = ID;
}

Task::Task(const Task& task){
    ID = task.ID;
    for(int i = 0; i < MAX_PARAMS; ++i)
        params[i] = task.params[i];
    completionInterrupt = task.completionInterrupt;
    interruptID = task.interruptID;
}

// Queue constructors

Queue::Queue(){

}

Queue::Queue(Task init[], int sz){
	for(int i = 0; i < sz; ++i)
		setAbsolute(init[i],i);
}

Queue::~Queue(){ // take care of dangling pointers
	curr = nullptr;
	next = nullptr;
}
// add specified task to next empty index, return true if succeeded,
// return false if no empty slot was found
bool Queue::pushToNextEmpty(Task task){
	for(int i = 0; i < MAX_TASKS; ++i){
		if(tasks[(iter+i)%MAX_TASKS].ID == T_EMPTY){
			iter = 0;
			tasks[(iter+i)%MAX_TASKS] = task;
			return true;
		}
	}
	return false;
}
// set the task at an index relative to the current action:
// wraps around when exceeding size
void Queue::setRelative(Task task, int offset){
	tasks[(iter+offset)%MAX_TASKS] = task;
}
// set task at absolute index, unless out of bounds
void Queue::setAbsolute(Task task, int pos){
	if(pos < 0 || pos > MAX_TASKS - 1) return;
	tasks[pos] = task;
}
// step forward in Queue and reset timers
void Queue::beginNext(){
	currFlag = curr->interruptID;
	curr = next;
	next = &tasks[(iter+1)% MAX_TASKS];

    if(curr->ID == T_ROTATE)
    {
        targetAngle = curr->params[0];
    }
	timeAccumulator = deltaT / 1000.f;

	if(++iter >= MAX_TASKS)
		iter = 0;
}
// get the start time & reset flag to -1
void Queue::startFrame(){
	startTime = micros();
	currFlag = -1;
}
// calculate frame time by time difference from startTime
void Queue::endFrame(){
	deltaT = micros() - startTime + 1ul;
}

void Queue::executeAction(Motor &motors, IMU &myImu){	// really gross long switch statement
	timeAccumulator += (int)(deltaT / 1000.f);

    int frac = (timeAccumulator) / curr->params[5];

    switch(curr->ID){
        case T_EMPTY:
            beginNext();
            return;
        case T_DRIVE:
            wheelSpeed[LEFT] = curr->params[0];
		    wheelSpeed[RIGHT] = curr->params[1];
            motors.Drive(wheelSpeed[LEFT],wheelSpeed[RIGHT]);
            break;
        case T_DRIVE_T:
            wheelSpeed[LEFT] = lerp(curr->params[0],curr->params[1],frac);
		    wheelSpeed[RIGHT] = lerp(curr->params[2],curr->params[3],frac);
            motors.Drive(wheelSpeed[LEFT],wheelSpeed[RIGHT]);
            break;
        case T_REVERSE_T:
		    wheelSpeed[LEFT] = lerp(curr->params[0],-1.f * curr->params[0],frac);
		    wheelSpeed[RIGHT] = lerp(curr->params[1],-1.f * curr->params[1],frac);
            motors.Drive(wheelSpeed[LEFT],wheelSpeed[RIGHT]);
            break;
        case T_HALT:
            wheelSpeed[LEFT] = lerp(curr->params[0],0.f,frac);
		    wheelSpeed[RIGHT] = lerp(curr->params[1],0.f,frac);
            motors.Drive(wheelSpeed[LEFT],wheelSpeed[RIGHT]);
        case T_ROTATE:
            // TODO add watcher & ROTATE code
            currAngle = myImu.direction.z * 180.f / 3.14159f;

            float diff = angleDiff(currAngle,targetAngle);
            if(!(abs(diff) < 10.f))
            {
                float sign = 0.f;
                if (diff != 0.f)
                    sign = abs(diff) / diff;
                     
                motors.Drive(-255.f*sign, 255.f*sign);
            }
            else
            {
                beginNext();
            }
            return;
        case T_SPRAY:
            digitalWrite(PUMP_ENABLE, HIGH);
        default:
            break;
    }
    if(timeAccumulator >= curr->params[5] && curr->ID != T_ROTATE){
        beginNext();
        digitalWrite(PUMP_ENABLE, LOW);
        return;
    }
}