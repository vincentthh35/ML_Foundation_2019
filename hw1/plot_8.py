import matplotlib.pyplot as plt
import os

file = open("result_8", "r")
data = file.readlines()
data = list(map(float, data))
# print(data)
plt.hist(data, bins = 100, color = "purple")
plt.xlabel("Error rate")
plt.ylabel("Frequency")
plt.tight_layout()
if not os.path.isdir("img"):
    os.mkdir("img")
plt.savefig("img/img_8.png")
