import matplotlib.pyplot as plt

file = open("result_7", "r")
data = file.readlines()
data = list(map(float, data))
# print(data)
plt.hist(data, bins = 100, color = "green")
plt.xlabel("Error rate")
plt.ylabel("Frequency")
plt.tight_layout()
if not os.path.isdir("img"):
    os.mkdir("img")
plt.savefig("img/img_7.png")
