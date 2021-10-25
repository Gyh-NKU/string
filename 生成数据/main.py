import os
import random

with open(r'C:\Users\honor\Desktop\strings1.txt', 'a') as f:
    for j in range(0, 5):
        for i in range(0, 100000000):
            text = '%d' % random.randint(0, 1)
            f.write(text)
        f.write('\n')
        for i in range(0, 1000):
            text = '%d' % random.randint(0, 1)
            f.write(text)
        f.write('\n')
