import matplotlib.pyplot as plt

file = open("result_7", "r")
data = file.readlines()
t = []
Ein = []
Ein_stochastic = []
for i in range(len(data)):
    data[i] = data[i].split(" ")
    t.append(int(data[i][0]))
    Ein.append(float(data[i][1]))
    Ein_stochastic.append(float(data[i][2]))
# data = list(map(float, data))
# print(data)
plt.figure(figsize = (10, 4))
plt.subplot(121)
plt.plot(t, Ein, color = "green")
plt.xlabel("t")
plt.ylabel("Ein(w_t)")
plt.subplot(122)
plt.plot(t, Ein_stochastic, color = "orange")
plt.xlabel("t")
plt.ylabel("Ein(w_t) (stochastic)")
plt.savefig("img_7.png")
