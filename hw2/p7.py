import random
import numpy as np
import matplotlib.pyplot as plt

N = 20
EXP = 1000
flip_prob = 0.2

def findEinandTheta(data): # return Ein, Theta, S
    bestEin = N
    bestTheta = -1
    bestS = 1

    # all -1 at first, gradually turn into +1
    tempEin = 0
    for i in range(N):
        if not data[i][1] == -1:
            tempEin += 1;
    for i in range(N):
        if data[i][1] == +1:
            tempEin -= 1;
            if tempEin < bestEin:
                bestEin = tempEin;
                if i != (N - 1):
                    bestTheta = (data[i][0] + data[i + 1][0]) / 2
                else:
                    bestTheta = data[i][0]
                bestS = -1
        else:
            tempEin += 1;

    # all +1 at first, gradually turn into -1
    tempEin = 0
    for i in range(N):
        if not data[i][1] == 1:
            tempEin += 1;
    for i in range(N):
        if data[i][1] == -1:
            tempEin -= 1;
            if tempEin < bestEin:
                bestEin = tempEin;
                if i != (N - 1):
                    bestTheta = (data[i][0] + data[i + 1][0]) / 2
                else:
                    bestTheta = data[i][0]
                bestS = 1
        else:
            tempEin += 1
    return (bestEin / N), bestTheta, bestS

dtype = [('x', float), ('y', int)]
plotData = []
avgDiff = 0
avgEin = 0
avgEout = 0
for runtime in range(EXP):
    print("EXP:%d" %(runtime))
    x = np.random.uniform(-1, 1, N)
    # print(x)
    y = np.sign(x)
    tempdata = []
    for i in range(N):
        if np.random.random_sample() <= 0.2:
            y[i] = -y[i]
    for i in range(len(x)):
        tempdata.append(tuple([x[i], y[i]]))
    data = np.array(tempdata, dtype = dtype)
    data = np.sort(data, order = 'x')
    # print(data)
    bestEin, bestTheta, bestS = findEinandTheta(data)
    Eout = 0.5 + 0.3 * bestS * abs(bestTheta) - 0.3 * bestS
    plotData.append(bestEin - Eout)
    avgDiff += bestEin - Eout
    avgEin += bestEin
    avgEout += Eout
    print("Ein: %f, Eout: %f,\nEin - Eout: %f" %(bestEin, Eout, bestEin - Eout))

print("******** End of %d EXPs on Data of N = %d *********\navg. Ein - Eout = %f\navg. Ein = %f\navg. Eout = %f" \
        % (EXP, N, avgDiff / EXP, avgEin / EXP, avgEout / EXP))
# plot
plt.hist(plotData, bins = 100, color = "green")
plt.xlabel("Ein - Eout")
plt.ylabel("Frequency")
plt.tight_layout()
plt.savefig("img_7.png")
