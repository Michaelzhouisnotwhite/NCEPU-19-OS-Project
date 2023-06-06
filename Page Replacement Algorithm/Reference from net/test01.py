# write on 2019/5/6 12:49
from numpy import *
import random
 
class pageReplacement:
    page_length = 0    #ҳ�泤��
    available_memory_block = 0    #�����ڴ��
    n  = 0    #�������������������
    page = []    #���ʵ�...
    memory = []    #�ڴ�
    k = 0    #ȱҳ�жϵĴ���
    page_fault_rate = 0.0    #ȱҳ�� = k/page_length
 
    def __init__(self, page_length = 0 ,available_memory_block = 0 ,n = 0):
        self.available_memory_block = available_memory_block
        self.n = n
        self.page_length = page_length
        for i in range(available_memory_block):
            self.memory.append(None)
        for i in range(page_length):
            self.page.append(random.randint(0,n-1))
 
    def __FIFO__(self):
        index = 0
        for i in range(self.page_length):
            index = index % self.available_memory_block
            if self.page[i] not in self.memory  :    #������ڴ���û�У��������аᵽ�ڴ棬�ҷ�����ȱҳ�ж�
                self.memory[index] = self.page[i]
                self.k += 1
                index += 1
        self.page_fault_rate = self.k/self.page_length
 
    def __LRU__(self):
        for i in range(self.page_length):
            if (self.page[i] not in self.memory) :    #������ڴ���û��,�������аᵽ�ڴ棬�ҷ�����ȱҳ�ж�
                if None in self.memory:
                    for j in range(self.available_memory_block):
                        if self.memory[j] == None:
                            self.memory[j] = self.page[i]
                            self.k += 1
                            break
                else:
                    for j in range(self.available_memory_block-1):
                        self.memory[j] = self.memory[j+1]
                    self.memory[-1] = self.page[i]
                    self.k += 1
            else:
                if None in self.memory:
                    for j in range(self.available_memory_block):
                        #if j == self.available_memory_block -1:
                            #break
                        if self.memory[j] == self.page[i]:
                            for k in range(j,self.available_memory_block-1):
                                if self.memory[k+1] == None:
                                    self.memory[k] = self.page[i]
                                    break
                                else:
                                    self.memory[k] = self.memory[k+1]
                            break
                else:
                    for j in range(self.available_memory_block):
                        if j == self.available_memory_block - 1:
                            break
                        if self.memory[j] == self.page[i]:
                            for k in range(j,self.available_memory_block-1):
                                    self.memory[k] = self.memory[k+1]
                            self.memory[-1] = self.page[i]
                            break
        self.page_fault_rate = self.k/self.page_length
 
if __name__ == '__main__':
    al = pageReplacement(40,3,7)
    '''
     al.__FIFO__()
    print(al.page)
    print(al.k,al.page_length)
    print(al.page_fault_rate)
    '''
    al.__LRU__()
    print(al.page)
    print(al.k, al.page_length)
    print(al.page_fault_rate)