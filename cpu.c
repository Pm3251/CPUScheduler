#include "oslabs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

struct PCB handle_process_arrival_pp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp) {
    if ((current_process.total_bursttime == 0) && (current_process.process_id == 0) && (current_process.execution_starttime == 0) && (current_process.execution_endtime == 0) && (current_process.arrival_timestamp == 0) && (current_process.process_priority == 0) && (current_process.remaining_bursttime == 0)) {
        new_process.execution_starttime = timestamp;
        new_process.execution_endtime = timestamp + new_process.total_bursttime;
        new_process.remaining_bursttime = new_process.total_bursttime;
    return new_process;
    }
    else if (new_process.process_priority >= current_process.process_priority) { 
        new_process.execution_starttime = 0;
        new_process.execution_endtime = 0;
        new_process.remaining_bursttime = new_process.total_bursttime;
        ready_queue[*queue_cnt] = new_process;
        *queue_cnt = *queue_cnt + 1;
    return current_process;
    }
    else { 
        new_process.execution_starttime = timestamp;
        new_process.execution_endtime = timestamp + new_process.total_bursttime;
        new_process.remaining_bursttime = new_process.total_bursttime;
        current_process.remaining_bursttime = current_process.execution_endtime - timestamp;
        current_process.execution_endtime = 0;
        ready_queue[*queue_cnt] = current_process;
        *queue_cnt = *queue_cnt + 1;
    return new_process;
    }
}

struct PCB handle_process_completion_pp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp) {
    if (*queue_cnt > 0) {
        struct PCB PCB_is_next_process;
        int priorty = ready_queue[0].process_priority;
        int placehldr_queue = 0;
        for (int i = 1 ; i <= *queue_cnt - 1; i++){
            if (priorty > ready_queue[i].process_priority){
                priorty = ready_queue[i].process_priority;
                placehldr_queue = i;
            }
        }
        PCB_is_next_process = ready_queue[placehldr_queue];
        if (*queue_cnt == 1) {
            ready_queue[0].process_id = 0;
            ready_queue[0].arrival_timestamp = 0;
            ready_queue[0].total_bursttime = 0;
            ready_queue[0].execution_starttime = 0;
            ready_queue[0].execution_endtime = 0;
            ready_queue[0].remaining_bursttime = 0;
            ready_queue[0].process_priority = 0;
        }
        else
            ready_queue[placehldr_queue] = ready_queue[*queue_cnt - 1];
            *queue_cnt = *queue_cnt - 1;
            PCB_is_next_process.execution_starttime = timestamp;
            PCB_is_next_process.execution_endtime = timestamp + PCB_is_next_process.total_bursttime;
        return PCB_is_next_process;
        }
    else {
        struct PCB PCB_is_Null;
        PCB_is_Null.process_id = 0;
        PCB_is_Null.arrival_timestamp = 0;
        PCB_is_Null.total_bursttime = 0;
        PCB_is_Null.execution_starttime = 0;
        PCB_is_Null.execution_endtime = 0;
        PCB_is_Null.remaining_bursttime = 0;
        PCB_is_Null.process_priority = 0;
    return PCB_is_Null;
  
    }
}

struct PCB handle_process_arrival_srtp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int time_stamp){
    if ((current_process.total_bursttime == 0) && (current_process.process_id == 0) && (current_process.execution_starttime == 0) && (current_process.execution_endtime == 0) && (current_process.arrival_timestamp == 0) && (current_process.process_priority == 0) && (current_process.remaining_bursttime == 0)) {
        new_process.execution_starttime = time_stamp;
        new_process.execution_endtime = time_stamp + new_process.total_bursttime;
        new_process.remaining_bursttime = new_process.total_bursttime;
    return new_process;
}
    else if (new_process.total_bursttime > current_process.remaining_bursttime) { 
        new_process.execution_starttime = 0;
        new_process.execution_endtime = 0;
        new_process.remaining_bursttime = new_process.total_bursttime;
        ready_queue[*queue_cnt] = new_process;
        *queue_cnt = *queue_cnt + 1;
    return current_process;
    }
    else { 
        new_process.execution_starttime = time_stamp;
        new_process.execution_endtime = time_stamp + new_process.total_bursttime;
        new_process.remaining_bursttime = new_process.total_bursttime;
        current_process.remaining_bursttime = current_process.execution_endtime - time_stamp;
        current_process.execution_endtime = 0;
        current_process.execution_starttime = 0;
        ready_queue[*queue_cnt] = current_process;
        *queue_cnt = *queue_cnt + 1;
    return new_process;
    }
}

struct PCB handle_process_completion_srtp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp) {
    if (*queue_cnt > 0) {
        struct PCB PCB_is_next_process;
        int temp_burst_time = ready_queue[0].remaining_bursttime;
        int placehldr_queue = 0;
        for (int i = 1 ; i <= *queue_cnt - 1; i++){
            if (temp_burst_time > ready_queue[i].remaining_bursttime){
            temp_burst_time = ready_queue[i].remaining_bursttime;
            placehldr_queue = i;
            }
        }
    PCB_is_next_process = ready_queue[placehldr_queue];
    if (*queue_cnt == 1) {
        ready_queue[0].process_id = 0;
        ready_queue[0].arrival_timestamp = 0;
        ready_queue[0].total_bursttime = 0;
        ready_queue[0].execution_starttime = 0;
        ready_queue[0].execution_endtime = 0;
        ready_queue[0].remaining_bursttime = 0;
        ready_queue[0].process_priority = 0;
        }
    else
        ready_queue[placehldr_queue] = ready_queue[*queue_cnt - 1];
        *queue_cnt = *queue_cnt - 1;
        PCB_is_next_process.execution_starttime = timestamp;
        PCB_is_next_process.execution_endtime = timestamp + PCB_is_next_process.remaining_bursttime;
    return PCB_is_next_process;
    }
    else {
        struct PCB PCB_is_Null;
        PCB_is_Null.process_id = 0;
        PCB_is_Null.arrival_timestamp = 0;
        PCB_is_Null.total_bursttime = 0;
        PCB_is_Null.execution_starttime = 0;
        PCB_is_Null.execution_endtime = 0;
        PCB_is_Null.remaining_bursttime = 0;
        PCB_is_Null.process_priority = 0;
    return PCB_is_Null;
  
    }
}

struct PCB handle_process_arrival_rr(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp, int time_quantum) {
    if ((current_process.total_bursttime == 0) && (current_process.process_id == 0) && (current_process.execution_starttime == 0) && (current_process.execution_endtime == 0) && (current_process.arrival_timestamp == 0) && (current_process.process_priority == 0) && (current_process.remaining_bursttime == 0)) {
        new_process.execution_starttime = timestamp;
            if (time_quantum <= new_process.total_bursttime){
                new_process.execution_endtime = timestamp + time_quantum;
            }
            else {
                new_process.execution_endtime = timestamp + new_process.total_bursttime;
            }
        new_process.remaining_bursttime = new_process.total_bursttime;
        return new_process;
    }
    else {
        new_process.execution_starttime = 0;
        new_process.execution_endtime = 0;
        new_process.remaining_bursttime = new_process.total_bursttime;
        ready_queue[*queue_cnt] = new_process;
        *queue_cnt = *queue_cnt + 1;
    return current_process;
    }
}

struct PCB handle_process_completion_rr(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp, int time_quantum) {
    if (*queue_cnt > 0) {
        struct PCB PCB_is_next_process;
        int temp_arrival_timestamp = ready_queue[0].arrival_timestamp;
        int placehldr_queue = 0;
        for (int i = 1 ; i <= *queue_cnt - 1; i++){
            if (temp_arrival_timestamp > ready_queue[i].arrival_timestamp){
            temp_arrival_timestamp = ready_queue[i].arrival_timestamp;
            placehldr_queue = i;
        }
    }
        PCB_is_next_process = ready_queue[placehldr_queue];
        if (*queue_cnt == 1) {
            ready_queue[0].process_id = 0;
            ready_queue[0].arrival_timestamp = 0;
            ready_queue[0].total_bursttime = 0;
            ready_queue[0].execution_starttime = 0;
            ready_queue[0].execution_endtime = 0;
            ready_queue[0].remaining_bursttime = 0;
            ready_queue[0].process_priority = 0;
            }
        else
            ready_queue[placehldr_queue] = ready_queue[*queue_cnt - 1];
            *queue_cnt = *queue_cnt - 1;
            PCB_is_next_process.execution_starttime = timestamp;
        if (time_quantum <= PCB_is_next_process.remaining_bursttime){
            PCB_is_next_process.execution_endtime = timestamp + time_quantum;
}
        else {
            PCB_is_next_process.execution_endtime = timestamp + PCB_is_next_process.remaining_bursttime;
}
        return PCB_is_next_process;
}
    else {
        struct PCB PCB_is_Null;
        PCB_is_Null.process_id = 0;
        PCB_is_Null.arrival_timestamp = 0;
        PCB_is_Null.total_bursttime = 0;
        PCB_is_Null.execution_starttime = 0;
        PCB_is_Null.execution_endtime = 0;
        PCB_is_Null.remaining_bursttime = 0;
        PCB_is_Null.process_priority = 0;
    return PCB_is_Null;
  
    }
}