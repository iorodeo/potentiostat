from __future__ import print_function
import unittest
import potentiostat
import time
import sys

class Basic(unittest.TestCase):

    def setUp(self):
        self.dev = potentiostat.Potentiostat(PORT)


    def tearDown(self):
        self.dev.close()


    def test_get_hardware_variant(self):
        hw_variant = self.dev.get_hardware_variant()
        self.assertTrue(hw_variant in potentiostat.HwVariantToCurrRangeList)


    def test_set_volt(self):
        self.dev.set_volt(-0.5)
        time.sleep(0.1)
        self.dev.set_volt( 0.5)
        time.sleep(0.1)
        self.dev.set_volt( 0.0)


    def test_get_curr(self):
        curr = self.dev.get_curr()


    def test_get_test_names(self):
        test_names = self.dev.get_test_names()


    def test_get_param(self):
        test_names = self.dev.get_test_names()
        for name in test_names:
            param = self.dev.get_param(name)


    def test_set_param(self):
        test_names = self.dev.get_test_names()
        for name in test_names:
            param = self.dev.get_param(name)
            self.dev.set_param(name,param)


    def test_set_volt_range(self):
        for volt_range in potentiostat.VoltRangeList:
            self.dev.set_volt_range(volt_range)
            volt_range_rsp = self.dev.get_volt_range()
            self.assertTrue(volt_range == volt_range_rsp)


    def test_get_volt_range(self):
        volt_range = self.dev.get_volt_range()
        self.assertTrue(volt_range in potentiostat.VoltRangeList)


    def test_set_curr_range(self):
        hw_variant = self.dev.get_hardware_variant()
        curr_range_list = potentiostat.HwVariantToCurrRangeList[hw_variant]
        for curr_range in curr_range_list:
            self.dev.set_curr_range(curr_range)
            curr_range_rsp = self.dev.get_curr_range()
            self.assertTrue(curr_range == curr_range_rsp)


    def test_get_curr_range(self):
        hw_variant = self.dev.get_hardware_variant()
        curr_range_list = potentiostat.HwVariantToCurrRangeList[hw_variant]
        curr_range = self.dev.get_curr_range()
        self.assertTrue(curr_range in curr_range_list)


    def test_get_device_id(self):
        device_id = self.dev.get_device_id()


    def test_set_device_id(self):
        new_device_id = 1
        old_device_id = self.dev.get_device_id()

        rsp_device_id = self.dev.set_device_id(new_device_id)
        self.assertTrue(new_device_id == rsp_device_id)

        rsp_device_id = self.dev.get_device_id()
        self.assertTrue(new_device_id == rsp_device_id)

        rsp_device_id = self.dev.set_device_id(old_device_id)
        self.assertTrue(old_device_id == rsp_device_id)

        rsp_device_id = self.dev.get_device_id()
        self.assertTrue(old_device_id == rsp_device_id)


    def test_get_sample_period(self):
        period = self.dev.get_sample_period()


    def test_set_sample_period(self):
        old_period = self.dev.get_sample_period()
        new_period = 15 

        rsp_period = self.dev.set_sample_period(new_period)
        self.assertTrue(new_period == rsp_period)

        rsp_period = self.dev.get_sample_period()
        self.assertTrue(new_period == rsp_period)

        rsp_period = self.dev.set_sample_period(old_period)
        self.assertTrue(old_period == rsp_period)

        rsp_period = self.dev.get_sample_period()
        self.assertTrue(old_period == rsp_period)


    def test_get_test_done_time(self):
        test_names = self.dev.get_test_names()
        for name in test_names:
            test_done_time = self.dev.get_test_done_time(name)


    def test_get_firmware_version(self):
        ver = self.dev.get_firmware_version()


if __name__ == '__main__':

    if (len(sys.argv) > 1):
        PORT = sys.argv[1]
        del sys.argv[1]
    else:
        PORT = '/dev/ttyACM0'


    unittest.main()
    




