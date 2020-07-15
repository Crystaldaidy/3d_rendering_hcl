import heterocl as hcl 
import numpy as np 

def find_min(a,b):
    def fm(a,b):
        with hcl.if_(a<b):
            hcl.return_(a)
        with hcl.else_():
            hcl.return_(b)
    result = hcl.compute((1,),lambda x: fm(a,b),"result")
    return result
    
hcl.init()

a = hcl.placeholder((),"a")
b = hcl.placeholder((),"b")
    
s = hcl.create_schedule([a,b],find_min)

print(hcl.lower(s))
f = hcl.build(s)

_a = 5
_b = 1
_result = hcl.asarray(np.zeros(1))

f(_a,_b,_result)

output = _result.asnumpy()
print(output)