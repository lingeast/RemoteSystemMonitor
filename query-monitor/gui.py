'gui module'

import time 
import thread
from Tkinter import *
from proc import InfoProc

WIDTH = 1000
HEIGHT = 400
RECH = 50
RECW = 800
GAP = 15
WORD = 70

class Gui(object):
    def __init__(self,Dest='localhost',Comm='yidong',Master=None):
        self.top = Master
        self.canvas = Canvas(width = WIDTH, height = HEIGHT, bg = 'white')
        self.canvas.pack()
        self.myinfo = InfoProc(dest=Dest,comstr=Comm)
        self.cpuTH = Scale(self.top,from_=0,to=100,orient=HORIZONTAL)
        self.cpuTH.set(90)
        self.cpuTH.pack()
        w1 =Label(self.top,text="CPU threshold")
        w1.pack()
        self.memTH = Scale(self.top,from_=0,to=100,orient=HORIZONTAL)
        self.memTH.set(90)
        self.memTH.pack()
        w2 =Label(self.top,text="Memory threshold")
        w2.pack()
        self.diskTH = Scale(self.top,from_=0,to=100,orient=HORIZONTAL)
        self.diskTH.set(90)
        self.diskTH.pack()
        w3 =Label(self.top,text="Disk threshold")
        w3.pack()
        self.alert = False
        for i in range(3):
            self.canvas.create_rectangle(0, (HEIGHT/4) * i, RECW, (HEIGHT/4) * i + RECH ,fill='gray')
        self.canvas.create_text(RECW,(HEIGHT/4)*3+RECH,text = 'Destination: '+Dest)
        self.canvas.create_text(RECW,(HEIGHT/4)*3+RECH+GAP,text = 'Community String: '+Comm)
        thread.start_new_thread(self.Update(self.myinfo,self.canvas),())
      #  thread.start_new_thread(self.Beep,())
    def Beep(self):
        while True:
           # if (result[1] > self.cpuTH.get() or \
            #    result[0] > self.memTH.get() or \
             #   result[2] > self.diskTH.get()):
            print 'a'
            time.sleep(1)
            
    def Update(self,myinfo,canvas):
        while True:
            result = myinfo.retval()
            strBuf = repr(result[1])
            tx1 = canvas.create_text(WORD,(HEIGHT/4) * 0 + RECH + GAP,text = 'CPU usage: ' + strBuf + '%' )
            if (result[1] > self.cpuTH.get()):
                fillcolor = 'red'
                print '\a'
            else:
                fillcolor = 'green'
            rt1 = canvas.create_rectangle(0, (HEIGHT/4) * 0,\
                                        result[1]*RECW/100,\
                                        (HEIGHT/4)*0 + RECH,\
                                        fill=fillcolor)
            strBuf = repr(result[0])
            tx2 = canvas.create_text(WORD,(HEIGHT/4)*1 + RECH + GAP,text = 'MEM usage: ' + strBuf + '%')
            if (result[0] > self.memTH.get() ):
                fillcolor = 'red'
                print '\a'
            else:
                fillcolor = 'green'
            rt2 = canvas.create_rectangle(0,(HEIGHT/4) * 1,\
                                        result[0]*RECW/100,\
                                        (HEIGHT/4) * 1 + RECH,\
                                        fill = fillcolor)
            strBuf = repr(result[2])
            tx3 = canvas.create_text(WORD,(HEIGHT/4)*2 + RECH +GAP, text = 'DISK usage: '+ strBuf + '%')
            if(result[2] > self.diskTH.get() ):
                fillcolor = 'red'
                print '\a'
            else:
                fillcolor = 'green'
            rt3 = canvas.create_rectangle(0, (HEIGHT/4) *2,\
                                        result[2]*RECW/100,\
                                        (HEIGHT/4)*2 + RECH,\
                                        fill = fillcolor)
            strBuf = repr(result[3]/1024)
            tx4 = canvas.create_text(WORD+30,(HEIGHT/4)*3 + RECH,text = 'Net traffic(recv): '+strBuf + 'kb/s')

            strBuf = repr(result[4]/1024)
            tx5 = canvas.create_text(WORD+30,(HEIGHT/4)*3 + RECH + GAP,text = 'Net traffic(send): '+strBuf + 'kb/s')


            canvas.update()
            time.sleep(1)
            canvas.delete(tx1)
            canvas.delete(tx2)
            canvas.delete(tx3)
            canvas.delete(tx4)
            canvas.delete(tx5)
            canvas.delete(rt1)
            canvas.delete(rt2)
            canvas.delete(rt3)
def Show(dest='127.0.0.1',comm='yidong'):
    myG = Gui(dest,comm)

def test():
    master = Tk()

    addr = StringVar()
    e1 = Entry(master,textvariable=addr,width=40)
    e1.pack()
    addr.set("Enter ip addr here")

    community = StringVar()
    e2 = Entry(master,textvariable=community,width=40)
    e2.pack()
    community.set("Enter community string here")
    def callback():
        myG = Gui(Master=master,Dest=addr.get(),Comm=community.get())
    b=Button(master,text="get",width=10,command=callback)
    b.pack()

    #b1=Button(master,test="confirm",command=master.quit)
    #b1.pack()
    mainloop()
   # myG = Gui()


if __name__ == '__main__':
    test()
