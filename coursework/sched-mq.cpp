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
        // TODO: Implement me!
        //add to the right queue
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
        // TODO: Implement me!
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
        if (Rrunq.count() == 0 || Irunq.count() == 0 || Nrunq.count() == 0 || Drunq.count() == 0) return NULL;
		if (Rrunq.count() == 1) return Rrunq.first();
        if (Rrunq.count() == 0 && Irunq.count() == 1) return Irunq.first();
        if (Rrunq.count() == 0 && Irunq.count() == 0 && Nrunq.count() == 1) return Nrunq.first();  
        if (Rrunq.count() == 0 && Irunq.count() == 0 && Nrunq.count() == 0 && Drunq.count() == 1) return Drunq.first();
		
		SchedulingEntity::EntityRuntime min_runtime = 0;
		SchedulingEntity *min_runtime_entity = NULL;
        if(Rrunq.count() > 1){
            for (const auto& entity : Rrunq) {
                if (min_runtime_entity == NULL || entity->cpu_runtime() < min_runtime) {
                    min_runtime_entity = entity;
                    min_runtime = entity->cpu_runtime();
                }
            }
        }	
        else{
            if(Irunq.count() > 1){
            for (const auto& entity : Irunq) {
                if (min_runtime_entity == NULL || entity->cpu_runtime() < min_runtime) {
                    min_runtime_entity = entity;
                    min_runtime = entity->cpu_runtime();
                }
            }
        }
        else{
            if(Nrunq.count() > 1){
            for (const auto& entity : Nrunq) {
                if (min_runtime_entity == NULL || entity->cpu_runtime() < min_runtime) {
                    min_runtime_entity = entity;
                    min_runtime = entity->cpu_runtime();
                }
            }
        }
        else{
            for (const auto& entity : Drunq) {
                if (min_runtime_entity == NULL || entity->cpu_runtime() < min_runtime) {
                    min_runtime_entity = entity;
                    min_runtime = entity->cpu_runtime();
                }
            }
        }

        }
        
        }
		return min_runtime_entity;
    }
    private:
        List<SchedulingEntity *> Rrunq;
        List<SchedulingEntity *> Irunq;
        List<SchedulingEntity *> Nrunq;
        List<SchedulingEntity *> Drunq;
    };

/* --- DO NOT CHANGE ANYTHING BELOW THIS LINE --- */

RegisterScheduler(MultipleQueuePriorityScheduler);