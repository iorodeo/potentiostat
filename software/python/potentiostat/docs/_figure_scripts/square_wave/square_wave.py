from __future__ import print_function
import scipy
import numpy
import matplotlib.pyplot as plt

def square_wave(param, sample_rate, pts_per_step=200, pts_quiet=200):

    # Number of staircase steps
    num_steps = numpy.round(scipy.absolute(param['finalValue'] - param['startValue'])/param['stepValue'])

    # Times in seconds for squarewave period, quiet time, test time and total time
    period = 1.0/sample_rate
    quiet_time = msec_to_sec(param['quietTime'])
    test_time = (num_steps+1)*period
    total_time =  quiet_time + test_time

    # Signed step value for staircase
    signed_step = param['stepValue']
    if param['startValue'] > param['finalValue']:
        signed_step = -signed_step

    # Get pts arrays for quiet time and test time
    t_pts_quiet = scipy.linspace(0,quiet_time, pts_quiet)
    v_pts_quiet = param['quietValue']*scipy.ones(t_pts_quiet.shape)
    t_pts_test = scipy.linspace(0,test_time,(num_steps+1)*pts_per_step)
    v_pts_test = []

    min_val = min(param['startValue'],param['finalValue'])
    max_val = max(param['startValue'],param['finalValue'])

    for i, t in enumerate(t_pts_test):
        t_mod = t%period
        curr_step_value = clamp(param['startValue'] + scipy.floor(t/period)*signed_step, min_val, max_val)
        if i == 0:
            v_pts_test.append(param['startValue'])
        elif i == t_pts_test.shape[0]-1:
            v_pts_test.append(param['finalValue'])
        else:
            if t_mod < period/2.0:
                v_pts_test.append(curr_step_value + param['amplitude'])
            else:
                v_pts_test.append(curr_step_value - param['amplitude'])

    v_pts_test = scipy.array(v_pts_test)
    t_pts_test = t_pts_test + t_pts_quiet[-1]
    t_pts = scipy.concatenate([t_pts_quiet, t_pts_test])
    v_pts = scipy.concatenate([v_pts_quiet,v_pts_test])
    return t_pts, v_pts


def clamp(val, min_val, max_val):
    return max(min(val,max_val),min_val)


def msec_to_sec(val):
    return (1.0e-3)*val


# -----------------------------------------------------------------------------
if __name__ == '__main__':

    sample_rate = 2.0          
    
    test_param = {
            'quietValue' : -0.4,
            'quietTime'  :  3000,
            'amplitude'  :  0.15,
            'startValue' : -0.4,
            'finalValue' :  0.3,
            'stepValue'  :  0.1,
            'window'     : 0.2,
            }
    
    t, v = square_wave(test_param, sample_rate)
    
    plt.plot(t,v)
    plt.grid('on')
    plt.xlabel('time (sec)')
    plt.ylabel('potential (V)')
    plt.xlim(0,t.max()*(1.1))
    plt.ylim(v.min()*1.2, v.max()*1.2)
    plt.show()
