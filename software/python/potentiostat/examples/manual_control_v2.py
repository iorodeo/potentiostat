from __future__ import print_function
from potentiostat import Potentiostat
import time
import sched
import math
import scipy
import matplotlib.pyplot as plt


def run_manual_test(pstat, volt_func, dt, t_stop):
    """
    Run a voltammetric test in maunal/direct mode. 

    pstat      = potentiostat
    volt_func  = output voltage function
    dt         = sample time step
    t_stop     = duration of the trial
    """
    t = 0 
    cnt = 0
    t_start = time.time()
    time_list, volt_list, curr_list = [], [], []
    scheduler = sched.scheduler(time.time, time.sleep)

    while t < t_stop:
        # Set potentiostat output voltage and samle current 
        volt = volt_func(t)
        pstat.set_volt(volt)
        curr = pstat.get_curr()
        print('{0:1.2f}, {1:1.2f}, {2:1.2f}'.format(t, volt, curr))
        time_list.append(t)
        volt_list.append(volt)
        curr_list.append(curr)
        # Run scheduler to until time for the next sample (dt seconds)
        t_next = t_start + (cnt+1)*dt
        scheduler.enterabs(t_next, 1, lambda:None, ()) 
        scheduler.run()
        t = time.time() - t_start
        cnt+=1
    return time_list, volt_list, curr_list


def create_sin_linear_func(t0, t1, v0, v1, amp, per):
    """
    Returns a function which in the interval [t0,t1] is a sum of linear
    function and a sine wave.

    t0   = time at which linear transition, from v0 to v1, begins
    t1   = time at which linear transition, from v0 to v1, ends
    v0   = initial value
    v1   = final value
    amp  = amplitude of superimposed sinewave
    per  = period on superimposed sinewave

    """
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

    # Run parameters
    t0 = 10.0  # Transition start time (s)
    t1 = 50.0  # Transition stop time (s)

    v0 = -0.9  # Initial voltage (V)
    v1 =  1.2  # Final voltage (V)

    amp = 0.1  # Sinusoid ampliude (V)
    per = 2.0  # Sinusoid period (s)

    dt = 0.05  # Time step for setting voltage and measurements
    t_total = 60.0 # Total experiment duration 

    volt_func = create_sin_linear_func(t0,t1,v0,v1,amp,per)

    # Create device object, set voltage/current ranges and run test
    pstat = Potentiostat('/dev/ttyACM0')
    pstat.set_volt_range('2V')
    pstat.set_curr_range('100uA')
    pstat.set_all_elect_connected(True)
    t, volt, curr = run_manual_test(pstat, volt_func, dt, t_total)
    pstat.set_all_elect_connected(False)

    # Plot results
    plt.subplot(211)
    plt.plot(t,volt)
    plt.ylabel('potential (V)')
    plt.grid('on')

    plt.subplot(212)
    plt.plot(t,curr)
    plt.xlabel('time (s)')
    plt.ylabel('current (uA)')
    plt.grid('on')
    plt.show()

