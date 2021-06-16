import matplotlib.pyplot as plt

file = open("result_8", "r")
data = file.readlines()
t = []
Eout = []
Eout_stochastic = []
for i in range(len(data)):
    data[i] = data[i].split(" ")
    t.append(int(data[i][0]))
    Eout.append(float(data[i][1]))
    Eout_stochastic.append(float(data[i][2]))
# data = list(map(float, data))
# print(data)
plt.figure(figsize = (10, 4))
plt.subplot(121)
plt.plot(t, Eout, color = "red")
plt.xlabel("t")
plt.ylabel("Eout(w_t)")
plt.subplot(122)
plt.plot(t, Eout_stochastic, color = "purple")
plt.xlabel("t")
plt.ylabel("Eout(w_t) (stochastic)")
plt.savefig("img_8.png")
