
# coding: utf-8

# In[1]:


get_ipython().run_line_magic('matplotlib', 'inline')

import pandas as pd
import numpy as np
import math


# In[2]:


#2.4 GHz measurements
excel24 = pd.read_csv('./latency24_clean.csv')
excel868 = pd.read_csv('./latency868_clean.csv')


# In[3]:


excel24.head(n=5)


# In[4]:


latency24 = excel24['latency'].values
latency868 = excel868['latency'].values
latency24 = latency24/1000000
latency868 = latency868/1000000


# In[5]:


#determine amount of samples, mean and standard deviation
num24 = len(latency24)
mean24 = sum(latency24)/num24
std24 = np.std(latency24)

num868 = len(latency868)
mean868 = sum(latency868)/num868
std868 = np.std(latency868)

print("Number of samples: " + str(num24)  + "\nMean of samples: " + str(mean24) + "\nStandard Deviation: " + str(std24))
print("Number of samples: " + str(num868)  + "\nMean of samples: " + str(mean868) + "\nStandard Deviation: " + str(std868))


# In[6]:


#determine Z value of confidence interval (95%)
Z = 1.960

#Calculate intervals
left_border24 = mean24 + Z*(std24/math.sqrt(num24))
right_border24 = mean24 - Z*(std24/math.sqrt(num24))

#Calculate intervals
left_border868 = mean868 + Z*(std868/math.sqrt(num868))
right_border868 = mean868 - Z*(std868/math.sqrt(num868))

print("2.4GHz \nLeft border: " + str(left_border24) + "\nRight border: " + str(right_border24))
print("868MHz \nLeft border: " + str(left_border868) + "\nRight border: " + str(right_border868))


# In[9]:


import matplotlib.pyplot as plt
count24, bins24, ignored = plt.hist(latency24, 20, normed=True)
plt.plot(bins24, 1/(std24 * np.sqrt(2 * np.pi)) *
              np.exp( - (bins24 - mean24)**2 / (2 * std24**2) ),
              linewidth=2, color='r')
plt.ylabel('occurrence')
plt.xlabel('hundreth of a second')
plt.title('2.4 GHz Latency Confidence Intervals')
plt.savefig('latency24')

plt.show()


# In[8]:


count868, bins868, ignored = plt.hist(latency868, 20, normed=True)
plt.plot(bins868, 1/(std868 * np.sqrt(2 * np.pi)) *
              np.exp( - (bins868 - mean868)**2 / (2 * std868**2) ),
              linewidth=2, color='r')

plt.ylabel('occurrence')
plt.xlabel('hundreth of a second')
plt.title('868 MHz Latency Confidence Intervals')
plt.savefig('latency868')

plt.show()

