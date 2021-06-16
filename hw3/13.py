import numpy as np

def f(x_1, x_2):
    if (x_1 ** 2 + x_2 ** 2 - 0.6) > 0 :
        return 1
    else :
        return -1

def sign(x):
    if x > 0:
        return 1
    else :
        return -1

N = 1000
EXP = 1000
lucky_number = 7
Ein_sum = 0
Eout_sum = 0
for _ in range(EXP):
    X = []
    X.append(np.random.uniform(1, 1, N))
    X.append(np.random.uniform(-1, 1, N))
    X.append(np.random.uniform(-1, 1, N))
    X.append([])
    for i in range(N):
        X[3].append(X[1][i] * X[2][i])
    X.append([])
    for i in range(N):
        X[4].append(X[1][i] ** 2)
    X.append([])
    for i in range(N):
        X[5].append(X[2][i] ** 2)

    # print(X)
    y = []
    for i in range(N):
        y.append(f(X[1][i], X[2][i]))
        flip = np.random.randint(10);
        if flip == 7:
            y[i] *= -1
    # print(y)
    X = np.transpose(X)
    X_pinv = np.linalg.pinv(X)
    W = X_pinv.dot(y)
    # print(W)
    # gen X_prime
    X_prime = []
    X_prime.append(np.random.uniform(1, 1, N))
    X_prime.append(np.random.uniform(-1, 1, N))
    X_prime.append(np.random.uniform(-1, 1, N))
    X_prime.append([])
    for i in range(N):
        X_prime[3].append(X_prime[1][i] * X_prime[2][i])
    X_prime.append([])
    for i in range(N):
        X_prime[4].append(X_prime[1][i] ** 2)
    X_prime.append([])
    for i in range(N):
        X_prime[5].append(X_prime[2][i] ** 2)
    y_prime = []
    for i in range(N):
        y_prime.append(f(X_prime[1][i], X_prime[2][i]))
        flip = np.random.randint(10);
        if flip == 7:
            y_prime[i] *= -1
    wrong_count = 0
    for i in range(N):
        sum = 0
        for j in range(6):
            sum += W[j] * X_prime[j][i]
        if y_prime[i] != sign(sum):
            wrong_count += 1
    Eout_sum += wrong_count / N
print(f'Avg. Eout is {Eout_sum / EXP}')
