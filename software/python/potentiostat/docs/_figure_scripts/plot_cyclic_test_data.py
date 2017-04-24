import scipy
import matplotlib.pyplot as plt

filename = 'cyclic_test_data.txt'

data = scipy.loadtxt(filename,delimiter=',')

t = data[:,0]
v = data[:,1]

figsize = 12, 8
xlim = t.min(), t.max()
ylim = -0.2, 1.2
linewidth = 2

fig = plt.figure(1,figsize=figsize)

vpos_arrow_low = -0.15

# Quiet time fill
plt.fill([0.0,1.0,1.0,0.0],[-0.2, -0.2, 1.2, 1.2], color=(0.3,0.3,0.3), alpha=0.1)

# Quiet time label
plt.text(0.5,vpos_arrow_low,'quiet time',ha='center')
plt.arrow(0.2,vpos_arrow_low+0.01,-0.158, 0.0, ec='k', fc='k')
plt.arrow(0.8,vpos_arrow_low+0.01, 0.17, 0.0, ec='k', fc='k')

# 1st Period label
plt.text(2.0, vpos_arrow_low, 'period (cycle 1)', ha='center')
plt.arrow(1.6, vpos_arrow_low+0.01, -0.56, 0.0, fc='k', ec='k')
plt.arrow(2.4, vpos_arrow_low+0.01,  0.57, 0.0, fc='k', ec='k')

# 2nd Period label
plt.text(4.0, vpos_arrow_low, 'period (cycle 2)', ha='center')
plt.arrow(3.6, vpos_arrow_low+0.01, -0.56, 0.0, fc='k', ec='k')
plt.arrow(4.4, vpos_arrow_low+0.01,  0.57, 0.0, fc='k', ec='k')

# Midline
plt.plot([1.0, xlim[1]], [0.5, 0.5], 'k',linewidth=linewidth)

# Offset lines and labels
hpos_offset_arrow = 1.6 
plt.plot([1.0, hpos_offset_arrow+0.03], [0.0, 0.0], 'k', linewidth=linewidth)
plt.text(hpos_offset_arrow,0.25,'offset',va='center',rotation=90)
plt.arrow(hpos_offset_arrow+0.034, 0.18, 0.0, -0.13, fc='k', ec='k')
plt.arrow(hpos_offset_arrow+0.034, 0.32, 0.0,   0.13, fc='k', ec='k')

# Amplitude lines and labels
hpos_amp_arrow = 1.4 
plt.plot([hpos_amp_arrow-0.03,2.0], [1.1, 1.1], 'k', linewidth=linewidth)
plt.text(hpos_amp_arrow,0.8,'amplitude', va='center', rotation=90)
plt.arrow(hpos_amp_arrow+0.034, 0.7, 0.0, -0.15, fc='k', ec='k')
plt.arrow(hpos_amp_arrow+0.034, 0.9, 0.0, 0.15, fc='k', ec='k')

plt.plot(t,v,'b',linewidth=linewidth)
plt.xlabel('time (s)')
plt.ylabel('potential (V)')
plt.xlim(*xlim)
plt.ylim(*ylim)
plt.grid('on')
plt.title('Cyclic Voltammetry Example')
plt.savefig('cyclic_test_fig.png')
plt.show()
