import matplotlib.pyplot as plt
import scipy
import scipy.integrate
import waveforms

class DummyCell:

    def __init__(self,R1,R2,C,v0_func):
        self.R1 = R1
        self.R2 = R2
        self.C = C
        self.v0_func = v0_func 

    def dv1_dt(self,v1,t):
        v0 = self.v0_func(t)
        return (1.0/self.C)*(v0/self.R2 - v1*(1.0/self.R1 + 1.0/self.R2))

    def run(self,T, num_pts):
        t_sim = scipy.linspace(0.0,T,num_pts)
        v1_sim = scipy.integrate.odeint(self.dv1_dt,0.0,t_sim)
        dv1_dt_sim = scipy.array([self.dv1_dt(vv,tt) for (vv,tt) in zip(v1_sim,t_sim)])
        cur_sim = v1_sim/self.R1 + self.C*dv1_dt_sim
        return t_sim, v1_sim, cur_sim




# -----------------------------------------------------------------------------
if __name__ == '__main__':

    R1 = 100000.0
    R2 = 49900.0
    #C =  4.7e-6 
    C =  1.0e-6 

    vmin = -2
    vmax =  6
    period = 0.5 
    symm = 0.5
    saw_wave = waveforms.sawtooth_wave(vmin,vmax,period)
    sqr_wave = waveforms.square_wave(vmin,vmax,period,symm)

    num_period = 5 
    v0_func = saw_wave.value
    #v0_func = sqr_wave.value
    dcell = DummyCell(R1,R2,C,v0_func)
    t,v1,cur = dcell.run(num_period*period,5000*num_period)
    v0 = scipy.array([v0_func(tt) for tt in t])

    cur = cur*1.0e6

    plt.figure(1)
    plt.subplot(211)
    plt.plot(t,v0)
    plt.xlabel('t (sec)')
    plt.ylabel('V0')
    plt.grid('on')

    plt.subplot(212)
    plt.plot(t,cur)
    plt.xlabel('t (sec)')
    plt.ylabel('I (uA)')
    plt.grid('on')

    plt.figure(2)
    plt.plot(v0,cur)
    plt.xlabel('V0')
    plt.ylabel('I (uA)')
    plt.grid('on')

    plt.show()











