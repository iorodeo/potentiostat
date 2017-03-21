from __future__ import print_function
import potentiostat
import unittest
import optparse 
import sys

class RunStreamTest(unittest.TestCase):


    def setUp(self):
        self.dev = potentiostat.Potentiostat(options.port)


    def tearDown(self):
        self.dev.close()


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
        for i in range(0,options.numrep):
            print('i = {0}/{1}'.format(i+1,options.numrep))
            print()
            t, curr, volt = self.dev.run_test(name)
            print()



if __name__ == '__main__':

    PORT = '/dev/ttyACM0'
    NUMREP = 2

    usage = "usage: %prog [options] <start_number> <final_number>"
    
    parser = optparse.OptionParser(usage=usage)
    parser.add_option('-p', '--port', dest='port', help='specify port used by potentiostaa, e.g /dev/ttyACM0',  default='/dev/ttyACM0')
    parser.add_option('-n', '--numrep', dest='numrep', type='int', help='specify number of repititions',default=5)
    
    (options,args) = parser.parse_args()

    sys.argv = [sys.argv[0]] + args

    unittest.main()
    
