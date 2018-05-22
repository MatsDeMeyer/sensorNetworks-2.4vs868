
# coding: utf-8

# In[15]:


import pandas as pd
excel = pd.read_excel('./latencyraw24.xlsx')


# In[16]:


#split rows of excel
def split_fields(row):
    
    sent = row['sent']
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


# In[17]:


excel_new = excel.apply(split_fields, axis=1)

excel_new.drop(['sent', 'received'], axis=1)


# In[18]:


#calculate difference of timestamps
def get_difference(row):
    
    row['latency'] = pd.to_datetime(row['received_timestamp']) - pd.to_datetime(row['sent_timestamp'])
    
    return row


# In[20]:


excel_latency = excel_new.apply(get_difference, axis=1)

excel_latency.to_csv('latency24_clean.csv')

