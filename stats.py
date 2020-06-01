import statsmodels.api as sm
import numpy as np

H = [   1,50,
		1,53,
		1,54,
		1,55,
		1,56,
		1,59,
		1,62,
		1,65,
		1,67,
		1,71,
		1,72,
		1,74,
		1,75,
		1,76,
		1,79,
		1,80,
		1,82,
		1,85,
		1,87,
		1,90,
		1,93,
		1,94,
		1,95,
		1,97,
		1,100]

Z = [   122,
		118,
		128,
		121,
		125,
		136,
		144,
		142,
		149,
		161,
		167,
		168,
		162,
		171,
		175,
		182,
		180,
		183,
		188,
		200,
		194,
		206,
		207,
		210,
		219]

matH = np.transpose(np.array([[H[2*i] for i in range(25)],[H[2*i+1] for i in range(25)]]))
vecZ = np.transpose(np.array([Z]))

print(matH.shape)
print(vecZ.shape)

# mod = sm.OLS(vecZ,matH)

# res = mod.fit()
# print(res.summary())

# w = np.zeros(shape=(25))
w = [0]*25
# print(w)
# print(w.shape)
wls_model = sm.WLS(vecZ,matH,weights=list(range(1,26)))
res = wls_model.fit()
print(res.params)


# x = list(range(1,8))
# print(x)