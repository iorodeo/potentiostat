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
        pass

    
    def test_multistep(self):
        pass


if __name__ == '__main__':

    if (len(sys.argv) > 1):
        PORT = sys.argv[1]
    else:
        PORT = '/dev/ttyACM0'
    unittest.main()
    
