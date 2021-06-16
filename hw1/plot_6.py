import matplotlib.pyplot as plt

file = open("result_6", "r")
data = file.readlines()
data = list(map(int, data))
# print(data)
plt.hist(data, bins = 100, color = "orange")
plt.xlabel("Number of updates")
plt.ylabel("Frequency")
plt.tight_layout()
if not os.path.isdir("img"):
    os.mkdir("img")
plt.savefig("img/img_6.png")
