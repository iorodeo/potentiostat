import scipy
import matplotlib.pyplot as plt

filename_list = [ 'data_shift_00.txt', 'data_shift_25.txt']
color_list = ['b', 'g']
label_list = ['shift = 0.0', 'shift = 0.25']

figsize = 12, 8
xlim = 0, 2 
ylim = -0.6, 0.6 
linewidth = 2


for filename, color, label in zip(filename_list,color_list,label_list):

    data = scipy.loadtxt(filename,delimiter=',')
    
    t = data[:,0]
    v = data[:,1]
    fig = plt.figure(1,figsize=figsize)
    plt.plot(t,v,color,linewidth=linewidth,label=label)

plt.text(0.25,0.0,'shift x period',ha='center',va='center')
plt.arrow(0.12,0.0,-0.07, 0.0, ec='k', fc='k')
plt.arrow(0.38,0.0, 0.07, 0.0, ec='k', fc='k')

plt.xlabel('time (s)')
plt.ylabel('potential (V)')
plt.xlim(*xlim)
plt.ylim(*ylim)
plt.xticks([0, 0.5, 1.0, 1.5, 2.0],['0', '0.25T', '0.5T', '0.75T', 'T=period'])
plt.grid('on')
plt.title('Cyclic voltammetry shift example')
plt.legend()
plt.savefig('cyclic_shift_fig.png')
plt.show()
