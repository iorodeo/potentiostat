from __future__ import print_function
from potentiostat import Potentiostat
import time
import sched
import math


def run_custom_test(pstat, volt_func, dt, t_stop):

    scheduler = sched.scheduler(time.time, time.sleep)

    cnt = 0
    time_list, volt_list, curr_list = [], [], []

    t = 0 
    t_start = time.time()

    while t < t_stop:

        volt = volt_func(t)
        pstat.set_volt(volt)
        curr = pstat.get_curr()

        print('{0:1.2f}, {1:1.2f}, {2:1.2f}'.format(t, volt, curr))

        time_list.append(t)
        volt_list.append(volt)
        curr_list.append(curr)
        
        t_next = t_start + (cnt+1)*dt
        scheduler.enterabs(t_next, 1, lambda:None, ()) 
        scheduler.run()

        t = time.time() - t_start
        cnt+=1

    return time_list, volt_list, curr_list


def create_sin_plus_linear_func(t0, t1, v0, v1, amp, per):

    def func(t):
        if t < t0:
            return v0 
        elif t < t1:
            dt_trans = t1-t0
            v_lin = (v1-v0)*(t-t0)/dt_trans + v0
            v_sin = amp*math.sin(2*math.pi*(t-t1)/per)
            return v_lin + v_sin
        else:
            return v1

    return func 


if __name__ == '__main__':

    import scipy
    import matplotlib.pyplot as plt

    # Run parameters
    t0 = 10.0  # Transition start time (s)
    t1 = 50.0  # Transition stop time (s)

    v0 = -0.9  # Initial voltage (V)
    v1 =  1.2  # Final voltage (V)

    amp = 0.1  # Sinusoid ampliude (V)
    per = 2.0  # Sinusoid period (s)

    dt = 0.05  # Time step for setting voltage and measurements
    t_total = 60.0 # Total experiment duration 

    volt_func = create_sin_plus_linear_func(t0,t1,v0,v1,amp,per)

    # Create device object and set voltage and current ranges
    pstat = Potentiostat('/dev/ttyACM0')
    pstat.set_volt_range('2V')
    pstat.set_curr_range('100uA')

    # Run test 
    t, volt, curr = run_custom_test(pstat, volt_func, dt, t_total)

    # Plot results
    plt.subplot(211)
    plt.plot(t,volt)

    plt.subplot(212)
    plt.plot(t,curr)

    plt.show()

