import numpy as np
import pandas as pd

data = np.loadtxt("ex0.txt")
arrayOnes = np.ones((200, 197))
data = np.concatenate([data, arrayOnes], axis=1)
dataT = data.T

dataN = np.linalg.inv(dataT * data)
