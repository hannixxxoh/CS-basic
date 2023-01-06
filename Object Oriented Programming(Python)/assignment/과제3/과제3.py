#!/usr/bin/env python
# coding: utf-8

# In[1]:


get_ipython().run_cell_magic('writefile', 'fibonacci.py', 'num = int(input("input: "))\nlst = [\'_\' for i in range(num+1)]\nlst[0] = 0\nlst[1] = 1\nlst[2] = 1\nfor i in range(3, num+1):\n                lst[i] = lst[i-1] + lst[i-2]\nprint(lst[num])')


# In[2]:


get_ipython().run_line_magic('run', 'fibonacci.py')


# In[3]:


get_ipython().run_cell_magic('writefile', 'fibona.py', "def fibo(num):\n    lst = ['_' for i in range(num+1)]\n    lst[0] = 0\n    lst[1] = 1\n    lst[2] = 1\n    for i in range(3, num+1):\n        lst[i] = lst[i-1] + lst[i-2]\n    print(lst[num])")


# In[4]:


import fibona
fibona.fibo(7)


# In[ ]:




