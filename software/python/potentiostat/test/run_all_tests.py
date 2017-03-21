from __future__ import print_function
import unittest
import potentiostat
import sys

class RunTests(unittest.TestCase):


    def setUp(self):
        self.dev = potentiostat.Potentiostat(PORT)


    def tearDown(self):
        self.dev.close()


    def test_constant(self):
        name = 'constant'
        param = {
                'quietValue' : 0.0,
                'quietTime'  : 1000,
                'value'      : 0.5,
                'duration'   : 5000,
                }
        param_rsp = self.dev.set_param(name,param)
        t, curr, volt = self.dev.run_test(name)


    def test_cyclic(self):
        name = 'cyclic'
        param = { 
                'quietValue' : 0.0,
                'quietTime'  : 1000,
                'amplitude'  : 2.0,
                'offset'     : 0.0,
                'period'     : 1000,
                'numCycles'  : 2,
                'shift'      : 0.0,
                }
        param_rsp = self.dev.set_param(name,param)
        t, curr, volt = self.dev.run_test(name)


    def test_sinusoid(self):
        name = 'sinusoid'
        param = {
                'quietValue' : 0.0,
                'quietTime'  : 1000,
                'amplitude'  : 1.0,
                'offset'     : 0.0,
                'period'     : 1000,
                'numCycles'  : 2,
                'shift'      : 0.0,
                }
        param_rsp = self.dev.set_param(name,param)
        t, curr, volt = self.dev.run_test(name)


    def test_linearsweep(self):
        name = 'linearSweep'
        param = {
                'quietTime'  : 0, 
                'quietValue' : 0.0, 
                'startValue' : -0.5, 
                'finalValue' : 0.5, 
                'duration'   : 2000, 
                }
        param_rsp = self.dev.set_param(name,param)
        t, curr, volt = self.dev.run_test(name)

    
    def test_multistep(self):
        step_list = []
        for i in range(0,10):
            step_list.append((250,round(0.2*(i+1),5)))
        name = 'multiStep'
        param = {
                'quietValue' : 0.0,
                'quietTime'  : 1000,
                'step'       : step_list,
                }
        param_rsp = self.dev.set_param(name,param)
        t, curr, volt = self.dev.run_test(name)


    def test_chronoamp(self):
        name = 'chronoamp'
        param = {
                'quietValue' : 0.0,
                'quietTime'  : 1000,
                'step'       : [(1000,-0.25), (1000,0.5)],
                }
        param_rsp = self.dev.set_param(name,param)
        t, curr, volt = self.dev.run_test(name)


if __name__ == '__main__':

    if (len(sys.argv) > 1):
        PORT = sys.argv[1]
        del sys.argv[1]
    else:
        PORT = '/dev/ttyACM0'
    unittest.main()
    
