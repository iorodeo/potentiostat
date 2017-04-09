from __future__ import print_function
from potentiostat import Potentiostat
import time
import sched


class TestScheduler(object):

    def __init__(self):
        self.dt = 0.05
        self.t_stop = 5.0
        self.priority = 1
        self.scheduler = sched.scheduler(time.time, time.sleep)

    def on_scheduler(self):
        self.t_elapsed = time.time() - self.tabs_start

    def run(self):
        self.tabs_start = time.time()
        self.t_elapsed = 0 
        cnt = 0
        while self.t_elapsed < self.t_stop:
            tabs_next = self.tabs_start + (cnt+1)*self.dt
            self.scheduler.enterabs(tabs_next,self.priority, self.on_scheduler,()) 
            self.scheduler.run()
            print(cnt, self.t_elapsed)
            cnt += 1

if __name__ == '__main__':

    myTest = TestScheduler()
    myTest.run()
