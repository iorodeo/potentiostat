import scipy
import matplotlib.pyplot as plt

filename = 'linear_sweep_data.txt'

figsize = 12, 8
xlim = 0, 10 
ylim = -1.0, 1.3 
linewidth = 2

data = scipy.loadtxt(filename,delimiter=',')

t = data[:,0]
v = data[:,1]
fig = plt.figure(1,figsize=figsize)
plt.plot(t,v,'b',linewidth=linewidth)

# Plot quietTime label
plt.text(1,0.1,'quietTime',ha='center',va='center')
plt.plot([2.0, 2.0], [0.03, 0.15], 'k', linewidth=linewidth)
plt.arrow(0.5,0.1,-0.4, 0.0, ec='k', fc='k', head_width=0.04, head_length=0.08)
plt.arrow(1.5,0.1, 0.4, 0.0, ec='k', fc='k', head_width=0.04, head_length=0.08)

# Plot quietValue label
plt.text(2.9,0.0, 'quietValue', ha='center', va='center')
plt.plot([2.08, 2.38],[0.0, 0.0], 'k', linewidth=linewidth)

# Plot startValue label
plt.text(1.1,-0.8, 'startValue', ha='center', va='center')
plt.plot([1.6, 1.92],[-0.8, -0.8], 'k', linewidth=linewidth)

# Plot finalValue label 
plt.text(9.1,1.2, 'finalValue', ha='center', va='center')
plt.plot([9.6, 9.92],[1.2,1.2], 'k', linewidth=linewidth)

# Plot duration label
plt.text(6.0,-0.8, 'duration', ha='center', va='center')
plt.arrow(5.55, -0.8, -3.4, 0.0, ec='k', fc='k', head_width=0.04, head_length=0.08)
plt.arrow(6.5, -0.8,  3.4, 0.0, ec='k', fc='k', head_width=0.04, head_length=0.08)


plt.xlabel('time (s)')
plt.ylabel('potential (V)')
plt.xlim(*xlim)
plt.ylim(*ylim)
plt.grid('on')
plt.title('Linear sweep example')
plt.legend()
plt.savefig('linear_sweep_fig.png')
plt.show()
