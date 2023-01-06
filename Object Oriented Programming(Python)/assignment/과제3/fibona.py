def fibo(num):
    lst = ['_' for i in range(num+1)]
    lst[0] = 0
    lst[1] = 1
    lst[2] = 1
    for i in range(3, num+1):
        lst[i] = lst[i-1] + lst[i-2]
    print(lst[num])
