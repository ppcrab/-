from ctypes import *
from pwn import *
context.log_level = "debug"

class StructPointer(Structure):  
    _fields_ = [("dir", c_char * 30),
                ("size", c_int)]

p = remote('120.79.29.135',9999)
p.recvuntil("Good luck\n")
di = []
d = [[0 for i in range(13)] for j in range(13)]
a = [[0 for i in range(13)] for j in range(13)]
b = p.recv().split('\n')
for i in range(13):
  a[i] = b[i]

c = (c_char_p*13)(*a)


so = cdll.LoadLibrary
dll = so("./libpymazing.so")

dll.seta.restype = POINTER(StructPointer)

cjia = dll.seta(c)

di = cjia.contents.dir[0:cjia.contents.size]
p.send(di)
p.recv()

  
    

