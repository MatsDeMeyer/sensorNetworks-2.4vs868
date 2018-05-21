
# coding: utf-8

# In[57]:


import pandas as pd
excel = pd.read_excel('./latency868.xlsx')


# In[62]:


def split_fields(row):
    
    sent = row['sent:']
    received = row['received']
    
    sent_split = sent.split(',')
    received_split = received.split(',')
    
    row['sent_data'] = sent_split[0]
    row['sent_timestamp'] = sent_split[1]
    row['sent_packet'] = sent_split[2]
    
    row['received_data'] = received_split[0]
    row['received_timestamp'] = received_split[1]
    row['received_packet'] = received_split[2]
    
    return row


# In[63]:


excel


# In[64]:


excel_new = excel.apply(split_fields, axis=1)


# In[65]:


excel_new


# In[67]:


excel_new.drop(['sent:', 'received'], axis=1)


# In[68]:


def get_difference(row):
    
    row['latency'] = pd.to_datetime(row['received_timestamp']) - pd.to_datetime(row['sent_timestamp'])
    
    return row


# In[69]:


excel_latency = excel_new.apply(get_difference, axis=1)


# In[70]:


excel_latency


# In[71]:


excel_latency.to_csv('latency868_clean.csv')

