'info process module'

import time
import thread
from mysnmp import snmpSessionBaseClass 

class InfoProc(object):
    def __init__(self,
                 intv = 2,
                dest="localhost",
                comstr="yidong"):
        self.interval = intv
        self.idle = 0   #cpu idle
        self.total = 0  #cpu
        self.mem = 0
        self.cpu = 0
        self.disk = 0
        self.netin = 0  
        self.netout = 0
        self.niOld = 0  #net in old value 
        self.noOld = 0  #net out old value
        self.ss = snmpSessionBaseClass(DestHost=dest,Community = comstr)#create retriving session
        thread.start_new_thread(self.deamon,())#fork deamon thread
    def deamon(self):   #constant info retriveing process
        while True:
            result = self.ss.query()
            self.mem =int( result[1] )
            self.disk = int (result[2] )

            pos = result[0].find(':')
            idleNew = int( result[0][:pos] )
            totalNew = int( result[0][pos + 1:] )
            if(totalNew != self.total):     #calc cpu usage
                self.cpu = 100 - 100* (idleNew - self.idle)/(totalNew - self.total)
            self.idle = idleNew
            self.total = totalNew

            pos = result[3].find(':')
            niNew = int( result[3][:pos])
            noNew = int( result[3][pos+1:])
            
            if(self.niOld != 0  and self.noOld != 0):
                self.netin = (niNew - self.niOld)/self.interval
                self.netout = (noNew - self.noOld)/self.interval
            self.niOld = niNew
            self.noOld = noNew
            time.sleep(self.interval)
    
    def retval(self):
        return (self.mem,self.cpu,self.disk,self.netin,self.netout)

def test():
    mp = InfoProc(dest='192.168.254.133',comstr='yidong')
    while True:
        time.sleep(1)
        print mp.retval()


if __name__ == '__main__':
    test()
