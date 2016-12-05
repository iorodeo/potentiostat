
class square_wave:

    def __init__(self,vmin,vmax,period,symm):
        self.vmin = vmin
        self.vmax = vmax
        self.period = period
        self.symm = symm

    def value(self,t):
        s = (t%self.period)/self.period
        if s <= self.symm:
            return self.vmin
        else:
            return self.vmax


class sawtooth_wave:

    def __init__(self,vmin,vmax,period):
        self.vmin = vmin
        self.vmax = vmax
        self.period = period

    def value(self,t):
        s = (t%self.period)/self.period
        if s <= 0.5:
            slope = 2.0*(self.vmax - self.vmin)
            offset = self.vmin
        else:
            slope = -2.0*(self.vmax - self.vmin)
            offset = 2*self.vmax - self.vmin
        return slope*s + offset


# -----------------------------------------------------------------------------
if __name__ == '__main__':

    import matplotlib.pyplot as plt
    import scipy

    vmin = -0.2
    vmax =  0.6
    period = 2.0
    symm = 0.25

    saw_wave = sawtooth_wave(vmin,vmax,period)
    saw_t = scipy.linspace(0,2*period,500)
    saw_v = scipy.array([saw_wave.value(t) for t in saw_t])

    sqr_wave = square_wave(vmin,vmax,period,symm)
    sqr_t = scipy.linspace(0,2*period,500)
    sqr_v = scipy.array([sqr_wave.value(t) for t in sqr_t])

    plt.figure(1)
    plt.plot(saw_t,saw_v)
    plt.xlabel('t (sec)')
    plt.ylabel('V')
    plt.title('sawtooth')

    plt.figure(2)
    plt.plot(sqr_t,sqr_v)
    plt.xlabel('t (sec)')
    plt.ylabel('V')
    plt.title('square, symm = {0}'.format(symm))

    plt.show()



