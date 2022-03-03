/*
 * The Priority Task Scheduler
 * SKELETON IMPLEMENTATION TO BE FILLED IN FOR TASK 1
 */

#include <infos/kernel/sched.h>
#include <infos/kernel/thread.h>
#include <infos/kernel/log.h>
#include <infos/util/list.h>
#include <infos/util/lock.h>

using namespace infos::kernel;
using namespace infos::util;

/**
 * A Multiple Queue entity.priority() scheduling algorithm
 */
class MultipleQueuePriorityScheduler : public SchedulingAlgorithm
{
public:
    /**
     * Returns the friendly name of the algorithm, for debugging and selection purposes.
     */
    const char* name() const override { return "mq"; }

    /**
     * Called during scheduler initialisation.
     */
    void init()
    {
        // TODO: Implement me!
         
    }

    /**
     * Called when a scheduling entity becomes eligible for running.
     * @param entity
     */
    void add_to_runqueue(SchedulingEntity& entity) override
    {
        //check the priority of an entity and add it to the right queue
        UniqueIRQLock l;
        if (entity.priority() == SchedulingEntityPriority::REALTIME) {
            Rrunq.enqueue(&entity);
        }
         if (entity.priority() == SchedulingEntityPriority::INTERACTIVE) {
            Irunq.enqueue(&entity);
        }
         if (entity.priority() == SchedulingEntityPriority::NORMAL) {
            Nrunq.enqueue(&entity);
        }
         if (entity.priority() == SchedulingEntityPriority::DAEMON) {
            Drunq.enqueue(&entity);
        }
    }

    /**
     * Called when a scheduling entity is no longer eligible for running.
     * @param entity
     */
    void remove_from_runqueue(SchedulingEntity& entity) override
    {
        //check the priority of an entity and remove it from the right queue
        UniqueIRQLock l;
		
        if (entity.priority() == SchedulingEntityPriority::REALTIME) {
            Rrunq.remove(&entity);
        }
         if (entity.priority() == SchedulingEntityPriority::INTERACTIVE) {
            Irunq.remove(&entity);
        }
         if (entity.priority() == SchedulingEntityPriority::NORMAL) {
            Nrunq.remove(&entity);
        }
         if (entity.priority() == SchedulingEntityPriority::DAEMON) {
            Drunq.remove(&entity);
        }

    }

    /**
     * Called every time a scheduling event occurs, to cause the next eligible entity
     * to be chosen.  The next eligible entity might actually be the same entity, if
     * e.g. its timeslice has not expired.
     */
    SchedulingEntity *pick_next_entity() override
    {
        // TODO: Implement me!
        if (Rrunq.count() == 0 || Irunq.count() == 0 || Nrunq.count() == 0 || Drunq.count() == 0) return NULL; // if all the queues are empty
		SchedulingEntity::EntityRuntime quantum = 10;
		SchedulingEntity *next_entity = NULL;
        //if there are processes in the realtime queue
        if(Rrunq.count() > 0){
            while(1){ 
                for (const auto& entity : Rrunq) {
                    next_entity = Rrunq.first(); 
                    remove_from_runqueue(&entity);
                    int run_time = entity->cpu_runtime();
                    int rem_time = entity->cpu_runtime() - quantum; //remaining cpu_run_time for a process
                    if(run_time > quantum){
                        entity->cpu_runtime() = quantum; // the entity only runs for a max of quantum time at a given time slot
                    }
                    if(rem_time > 0) {
                        add_to_runqueue(&entity); //if the process is not complete add it to the end of the respective priority queue
                    }
                }
                if(Rrunq.empty(){
                    break;  // if all processes in this priority are complete
                }
            }
        }

        else{
            //if there are no processes in the realtime queue and there are processes in the interactive queue
            if(Irunq.count() > 0){
                while(1){ 
                    for (const auto& entity : Irunq) {
                        next_entity = entity; 
                        remove_from_runqueue(&entity);
                        int run_time = entity->cpu_runtime();
                        int rem_time = entity->cpu_runtime() - quantum;
                        if(run_time > quantum){
                            entity->cpu_runtime() = quantum;
                        }
                        if(rem_time > 0) {
                            add_to_runqueue(&entity);
                        }
                    }
                    if(Irunq.empty(){
                        break;
                    }
                }
            }
            else{
                //if there are no processes in the realtime and interactive queues and there are processes in the normal queue
                if(Nrunq.count() > 0){
                    while(1){
                        for (const auto& entity : Nrunq) {
                            next_entity = Nrunq.first(); 
                            remove_from_runqueue(&entity);
                            int run_time = entity->cpu_runtime();
                            int rem_time = entity->cpu_runtime() - quantum;
                            if(run_time > quantum){
                                entity->cpu_runtime() = quantum;
                            }
                            if(rem_time > 0) {
                                add_to_runqueue(&entity);
                            }
                        }
                        if(Nrunq.empty(){
                            break;
                        }
                    }
                }
                else{
                    //if there are no processes in the realtime,interactive and norma queues and there are processes in the daemon queue
                    while(1){
                        for (const auto& entity : Drunq) {
                            next_entity = Drunq.first(); 
                            remove_from_runqueue(&entity);
                            int run_time = entity->cpu_runtime();
                            int rem_time = entity->cpu_runtime() - quantum;
                            if(run_time > quantum){
                                entity->cpu_runtime() = quantum;
                            }
                            if(rem_time > 0) {
                                add_to_runqueue(&entity);
                            }
                        }
                        if(Drunq.empty(){
                            break;
                        }
                    }
                }
            }
        }

		return next_entity;
    }
    private:
        List<SchedulingEntity *> Rrunq; //Realtime queue
        List<SchedulingEntity *> Irunq; //Interactive queue
        List<SchedulingEntity *> Nrunq; //Normal queue
        List<SchedulingEntity *> Drunq; //Daemon queue
    };

/* --- DO NOT CHANGE ANYTHING BELOW THIS LINE --- */

RegisterScheduler(MultipleQueuePriorityScheduler);