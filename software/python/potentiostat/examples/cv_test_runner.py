import time
import signal
import itertools
import numpy as np
import matplotlib.pyplot as plt
from potentiostat import Potentiostat

class CVTestRunner:
    """
    Simple class for running repeated cyclic voltammetry tests at different
    scan rates.
    """

    def __init__(self, port, param):
        self.port = port
        self.param = param
        self.dev = None

        # Setup sigint handler to ensure proper device shutdown on
        # ctl-c when running using idle or other repl.
        self.sigint_flag = False 
        signal.signal(signal.SIGINT, self.sigint_handler)


    def sigint_handler(self, signum, frame):
        """ Handle SIGINT signal when user hits Ctl-C to abort tests."""
        if self.dev is not None:
            self.dev.stop_test(rsp=False)
        self.sigint_flag = True


    def create_device_param(self, scanrate):
        """
        Convert parameters to form suitable for sending to device when runing
        the 'cyclic' test, e.g., amplitude, offset, period, phase shift for
        triangle waveform
        """
        volt_max = self.param['volt_max']
        volt_min = self.param['volt_min']

        amplitude = (volt_max - volt_min)/2.0       # Waveform peak amplitude (V) 
        offset = (volt_max + volt_min)/2.0          # Waveform offset (V) 
        period_ms = int(1000*4*amplitude/scanrate)  # Waveform period in (ms)
        shift = 0.0                                 # Waveform phase shift, [0,1] number

        # Create dictionary of waveform parameters for cyclic voltammetry test
        test_param = {
                'quietValue' : self.param['quiet_value'],
                'quietTime'  : self.param['quiet_time'],
                'amplitude'  : amplitude,
                'offset'     : offset,
                'period'     : period_ms,
                'numCycles'  : self.param['num_cycles'],
                'shift'      : self.param['shift'],
                }
        return test_param

    def get_num_dropped(self, t):
        """
        Check the return sample times and count the number of dropped samples
        """
        dt = np.diff(t)
        mask = dt > 1.5/self.param['sample_rate']
        num_dropped = dt[mask].shape[0]
        return num_dropped

    def run(self):

        set_range = range(self.param['numsets'])
        scanrates = self.param['scanrates']

        self.dev = Potentiostat(self.port)  

        for n, rate in itertools.product(set_range, scanrates):

            # Set current range and sample rate
            self.dev.set_curr_range(self.param['curr_range'])   
            self.dev.set_sample_rate(self.param['sample_rate'])

            # Set test parameters
            test_name = self.param['test_name']
            test_param = self.create_device_param(rate)
            self.dev.set_param(test_name,test_param)
            
            rate_ms = rate*1000
            datafile = f'CV_{rate_ms:1.0f}_{n}.txt'

            print()
            print(f'set #: {n+1}/{len(set_range)}')
            print(f'scanrate: {rate}')
            print(f'datafile: {datafile}')
            
            # Run the CV and save files to the current cwd
            t, volt, curr = self.dev.run_test(test_name, display=self.param['display'] , filename=datafile)

            # Convert output lists to numpy arrays
            t = np.array(t)
            volt = np.array(volt)
            curr = np.array(curr)

            # Get number dropped sample points
            num_points = t.shape[0]
            num_dropped = self.get_num_dropped(t)
            print(f'dropped:   ({num_dropped}/{num_points})')
        
            # Plot the data
            plt.figure(2)
            plt.plot(volt, curr)

            # Has user entered Ctl-C. If so break out of loop.
            if self.sigint_flag:
                print('acquisition aborted!!')
                break

        # Close and delete device object
        self.dev.close()
        del self.dev

        plt.show()

# ------------------------------------------------------------------------------------
if __name__ == '__main__':

    #port = '/dev/ttyACM0'
    port = 'COM5'

    param = {
        'test_name'   : 'cyclic',    # Name of voltammetric test
        'curr_range'  : '100uA',     # Potentiostat current range 
        'numsets'     : 3,           # Number of times to repeat the tests
        'scanrates'   : [0.15, 0.2], # List of output voltage scan rates (V/s)
        'sample_rate' : 1000,        # Rate at which to acquire samples (Hz)
        'quiet_time'  : 1000,        # Pretrial quiet time  (ms)
        'quiet_value' :-0.1,         # Output voltage during pre-test quiet time (V)
        'volt_min'    :-0.2,         # Minimum voltage of the waveform (V)
        'volt_max'    : 0.6,         # Maximum voltage of the waveform (V)
        'num_cycles'  : 1,           # Number of waveform cycles in a test
        'shift'       : 0.0,         # Waveform phase shift - dimensionless number [0,1]
        'display'     : None,        # run_test display style - None or 'pbar' 
        }

    test_runner = CVTestRunner(port, param)
    test_runner.run()
