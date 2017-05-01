import code
from spi import write_2bytes

data = [90, 90, 90, 90]

def moveTo(i, a):
  data[i] = a
  for ii in range(4):
    write_byte(data[ii])

def shoulder(a):
  moveTo(0, a)

def hand(a):
  moveTo(1, a)

def wrist(a):
  moveTo(2, a)

def elbow(a):
  moveTo(3, a)

code.interact(local=locals())
