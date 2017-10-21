import time, os

while 1:
    localtime=time.asctime(time.localtime(time.time()))
    print("Current time is: {}".format(localtime))
    time.sleep(0.01)
    os.system('clear')