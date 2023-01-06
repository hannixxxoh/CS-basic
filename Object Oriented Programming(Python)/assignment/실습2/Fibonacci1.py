
def Fibo_func(N):
    a, b = 0, 1
    i = 0
    while i<=N:
        yield a
        a, b = b, a+b
        i+=1
