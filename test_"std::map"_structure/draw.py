import matplotlib.pyplot as plt

with open('out-py.txt') as f:
    lines = f.readlines()
    x1 = [int(line.split()[0]) for line in lines]
    y1 = [int(line.split()[1]) for line in lines]

with open('out.txt') as f:
    lines = f.readlines()
    x2 = [int(line.split()[0]) for line in lines]
    y2 = [int(line.split()[1]) for line in lines]

plt.xlabel("время")
plt.ylabel("память")

plt.plot(x1, y1, label = "Python")
#plt.twiny()
plt.plot(x2, y2, label = "C++")

plt.legend()

plt.show()