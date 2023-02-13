from matplotlib import pyplot as plt
import pandas as pd


COLUMNS = ["MES", "AVALIACAO_MEDIA"]

dataframe = pd.read_csv("output.csv", usecols=COLUMNS)

plt.xlabel("Mês")
plt.ylabel("Avaliação Média")
plt.plot(dataframe.MES, dataframe.AVALIACAO_MEDIA)
plt.grid()
plt.savefig("graphic.png")
