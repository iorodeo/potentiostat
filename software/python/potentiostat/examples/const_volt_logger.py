"""
const_volt_logger.py

Example of a constant voltage test data logger which is intended for very long
duration experiments with low sample rates. Uses Python's sched module for
timing. Data is logged to output file specified in the params. The test runs
indefinitely, but can  be interrupted with ctl-c. It can then restarted and
will continue to append data to the same data file. 

Potentiostat Shield is operated manual/direct control mode where output voltage
is set directly from python.

"""
from __future__ import print_function
from potentiostat import Potentiostat
import time
import os.path
import signal
import sched



class ConstVoltLogger(object):

    def __init__(self, param):
        """
        param - dictionary of parameters for the test. Should contain 
        the following items.

        filename      Data log filename
        port          Potentiostat serial port
        volt_range    Output voltage range
        curr_range    Measurement current range
        sample_dt     Sample period (s)
        volt          # Output voltage (V)

        """
        self.param = param
        self.done = False
        self.sep = ','

        self.pstat = Potentiostat(self.param['port'])
        self.pstat.set_volt_range(self.param['volt_range'])
        self.pstat.set_curr_range(self.param['curr_range'])
        self.pstat.set_volt(self.param['volt'])

        self.scheduler = sched.scheduler(time.time, time.sleep)
        self.scheduler_event = None

        signal.signal(signal.SIGINT,self.sigint_handler)


    def get_file_start_time(self):
        t_start_file = None
        if os.path.exists(self.param['filename']):
            line_list = []
            with open(self.param['filename'],'r') as fid:
                try:
                    line_list = fid.readlines()
                    start_line = line_list[0]
                    start_line = start_line.split(self.sep)
                    t_start_file = float(start_line[0])
                except: 
                    pass
        return t_start_file


    def run(self):
        t_start = time.time()
        t_start_file = self.get_file_start_time()
        if t_start_file is None:
            t_start_file = t_start

        print()
        print('press ctl-c to exit')
        print()
        print('t (s), current (A)')
        print('------------------')

        with open(self.param['filename'],'a') as fid:
            cnt = 0
            while not self.done:
                curr = self.pstat.get_curr()
                t_current = time.time()
                t_elapsed = t_current - t_start_file

                fid.write('{0}{1} {2}{3}'.format(t_current,self.sep,curr,os.linesep))
                print('{0:1.2f}{1} {2:1.4f}'.format(t_elapsed,self.sep,curr))

                t_next = t_start + (cnt+1)*self.param['sample_dt']
                self.scheduler_event = self.scheduler.enterabs(t_next, 1, lambda:None, ()) 
                self.scheduler.run()
                cnt += 1


    def sigint_handler(self,signum,frame):
        self.scheduler.cancel(self.scheduler_event)
        self.done = True 


if __name__ == '__main__':

    param = { 
            'filename'   : 'logfile.txt',   # Data log filename
            'port'       : '/dev/ttyACM0',  # Potentiostat serial port
            'volt_range' : '1V',            # Output voltage range
            'curr_range' : '1uA',           # Measurement current range
            'sample_dt'  : 5.0,             # Sample period
            'volt'       : 0.5,             # Output voltage
            }

    data_logger = ConstVoltLogger(param)

    data_logger.run()












