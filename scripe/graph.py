import matplotlib.pyplot as plt


ref = open("../scripe/ref_x.txt")
g_x1 = open("../scripe/g_x1.txt")

ref_x = []
ref_y = []
x1=[]
y1=[]

for i in ref:
    i = i.split(",")
    ref_x.append(float(i[0]))
    ref_y.append(float(i[1].strip("\n")))

for i in g_x1:
    i = i.split(",")
    x1.append(float(i[0]))
    y1.append(float(i[1].strip("\n")))
    # print(float(i[0]))

plt.plot(ref_x,ref_y,"ro")
plt.plot(x1,y1,"bo")
plt.show()