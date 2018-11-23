# RTOS Integration Project

### What is happening now? 18.11.23

- I have successfully figured out how to set the current of chassis motors (But still needs testing, maybe I will do it later?) in `chassis_task.c`. Line 150-153 are for the input test. Do remember that the array starts with index 0.

```c
chassis.wheel_spd_ref[0] = CM1_SPEED;
chassis.wheel_spd_ref[1] = CM2_SPEED;
chassis.wheel_spd_ref[2] = CM3_SPEED;
chassis.wheel_spd_ref[3] = CM4_SPEED;
```

- There is one more thing needs noticing. In the original code in RTOS, the feedback of the motor (the speed of the motor) is in *rpm* unit. However, we use `filter_rate` in `Hero_Canon` and if we change the unit, all inputs may require readjustment. So I change the feedback unit back to `filter_rate`. This change is in `info_interactive.c`, line 56-57.

```c
//chassis.wheel_spd_fdb[i] = moto_chassis[i].speed_rpm;
chassis.wheel_spd_fdb[i] = moto_chassis[i].filter_rate;
```

- I also disable the gimbal task transmition in order to focus on the chassis test. I disable it in `gimbal_task.c`, line 252-255. Remember to uncomment it before working on gimbal.

```c
/*
  osSignalSet(can_msg_send_task_t, GIMBAL_MOTOR_MSG_SEND);
  osSignalSet(shoot_task_t, SHOT_TASK_EXE_SIGNAL);
*/
```

===end of log 18.11.23===