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
 * A Multiple Queue priority scheduling algorithm
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
         private:
	List<SchedulingEntity *> REALTIME;
    List<SchedulingEntity *> INTERACTIVE;
    List<SchedulingEntity *> NORMAL;
    List<SchedulingEntity *> DAEMON;
    }

    /**
     * Called when a scheduling entity becomes eligible for running.
     * @param entity
     */
    void add_to_runqueue(SchedulingEntity& entity) override
    {
        // TODO: Implement me!
        //add to the right queue
        UniqueIRQLock l;
        if (priority == SchedulingEntityPriority::REALTIME) {
            REALTIME.enqueue(&entity);
        }
         if (priority == SchedulingEntityPriority::INTERACTIVE) {
            INTERACTIVE.enqueue(&entity);
        }
         if (priority == SchedulingEntityPriority::NORMAL) {
            NORMAL.enqueue(&entity);
        }
         if (priority == SchedulingEntityPriority::DAEMON) {
            DAEMON.enqueue(&entity);
        }
    }

    /**
     * Called when a scheduling entity is no longer eligible for running.
     * @param entity
     */
    void remove_from_runqueue(SchedulingEntity& entity) override
    {
        // TODO: Implement me!
        UniqueIRQLock l;
		
        if (priority == SchedulingEntityPriority::REALTIME) {
            REALTIME.remove(&entity);
        }
         if (priority == SchedulingEntityPriority::INTERACTIVE) {
            INTERACTIVE.remove(&entity);
        }
         if (priority == SchedulingEntityPriority::NORMAL) {
            NORMAL.remove(&entity);
        }
         if (priority == SchedulingEntityPriority::DAEMON) {
            DAEMON.remove(&entity);
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
        if (REALTIME.count() == 0 || INTERACTIVE.count() == 0 || NORMAL.count() == 0 || DAEMON.count() == 0) return NULL;
		if (REALTIME.count() == 1) return REALTIME.first();
        if (REALTIME.count() == 0 && INTERACTIVE.count() == 1) return INTERACTIVE.first();
        if (REALTIME.count() == 0 && INTERACTIVE.count() == 0 && NORMAL.COUNT() == 1) return NORMAL.first();  
        if (REALTIME.count() == 0 && INTERACTIVE.count() == 0 && NORMAL.COUNT() == 0 && DAEMON.count() == 1) return DAEMON.first();
		
		SchedulingEntity::EntityRuntime min_runtime = 0;
		SchedulingEntity *min_runtime_entity = NULL;
        if(REALTIME.count() > 1){
            for (const auto& entity : REALTIME) {
                if (min_runtime_entity == NULL || entity->cpu_runtime() < min_runtime) {
                    min_runtime_entity = entity;
                    min_runtime = entity->cpu_runtime();
                }
            }
        }	
        else{
            if(INTERACTIVE.count() > 1){
            for (const auto& entity : INTERACTIVE) {
                if (min_runtime_entity == NULL || entity->cpu_runtime() < min_runtime) {
                    min_runtime_entity = entity;
                    min_runtime = entity->cpu_runtime();
                }
            }
        }
        else{
            if(NORMAL.count() > 1){
            for (const auto& entity : NORMAL) {
                if (min_runtime_entity == NULL || entity->cpu_runtime() < min_runtime) {
                    min_runtime_entity = entity;
                    min_runtime = entity->cpu_runtime();
                }
            }
        }
        else{
            for (const auto& entity : DAEMON) {
                if (min_runtime_entity == NULL || entity->cpu_runtime() < min_runtime) {
                    min_runtime_entity = entity;
                    min_runtime = entity->cpu_runtime();
                }
            }
        }

        }
        }
        }
		return min_runtime_entity;
    }
   
};

/* --- DO NOT CHANGE ANYTHING BELOW THIS LINE --- */

RegisterScheduler(MultipleQueuePriorityScheduler);