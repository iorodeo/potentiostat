import scipy
import matplotlib.pyplot as plt

filename = 'const_test_data.txt'

figsize = 12, 8
xlim = 0, 10 
ylim = -0.1, 1.0 
linewidth = 2

data = scipy.loadtxt(filename,delimiter=',')

t = data[:,0]
v = data[:,1]
fig = plt.figure(1,figsize=figsize)
plt.plot(t,v,'b',linewidth=linewidth)

# Quiet time fill
plt.fill([0.0,2.0,2.0,0.0],[-0.1, -0.1, 1.0, 1.0], color=(0.3,0.3,0.3), alpha=0.1)

# Plot quietTime label
plt.text(1,0.05,'quietTime',ha='center',va='center')
plt.arrow(0.5,0.05,-0.4, 0.0, ec='k', fc='k', head_width=0.01, head_length=0.08)
plt.arrow(1.5,0.05, 0.4, 0.0, ec='k', fc='k', head_width=0.01, head_length=0.08)

# Plot quietValue label
plt.text(2.9,0.0, 'quietValue', ha='center', va='center')
plt.plot([2.08, 2.38],[0.0, 0.0], 'k', linewidth=linewidth)

# Plot value label
plt.text(1.4, 0.7, 'value', ha='center', va='center')
plt.plot([1.7,1.93],[0.7, 0.7], 'k', linewidth=linewidth)

# Plot duration label
plt.text(6.0,0.75, 'duration', ha='center', va='center')
plt.plot([2.0, 2.0],[0.71, 0.76], 'k', linewidth=linewidth)
plt.arrow(5.55, 0.75, -3.45, 0.0, ec='k', fc='k', head_width=0.01, head_length=0.08)
plt.arrow(6.5, 0.75,  3.4, 0.0, ec='k', fc='k', head_width=0.01, head_length=0.08)

plt.xlabel('time (s)')
plt.ylabel('potential (V)')
plt.xlim(*xlim)
plt.ylim(*ylim)
plt.grid('on')
plt.title('Constant voltage example')
plt.legend()
plt.savefig('const_voltage_fig.png')
plt.show()
