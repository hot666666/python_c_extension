import spam
import time

def py_add(_a, _b):
    temp = [None for i in _a]
    cnt = 0
    for i, j in zip(_a, _b):
        temp[cnt] = i + j
        cnt += 1
    return temp

cnt = 100000000
a = [i for i in range(cnt)]
b = [i for i in range(cnt)]

st = time.time()
ret_py=py_add(a, b)
print("normal python def time : ", time.time() - st)

st = time.time()
ret_c = spam.spadd(a, b)
print("Cpython def time : ", time.time() - st)

print("Same result : ",ret_py == ret_c)