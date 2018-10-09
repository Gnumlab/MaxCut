

import matplotlib.pyplot as plt
from scipy import stats
import pandas as pd
import numpy as np
dir = "Data/"
dirImg = "Results/"
nameGraph = 'tourspm3-8-50'
namesAlg = ['prob', 'greedy', 'greedyProb', 'greedyProbFixed']
numbersOfRun = [10000, 1000, 1000, 1000]
nameAlg = 'prob'
numberOfRun = 10000
opt = 1050

d = pd.read_csv(dir + nameGraph + '-' + nameAlg, sep=',', header=None)	# read file
data = d[0].copy()	# take the first and only one column


def histogram():

    binNumber = max(int(round(np.log(max(data)-min(data)))), 15)

    plt.hist(data, bins=range(min(data), max(data) + 10, (max(data)-min(data))/binNumber ), color='red')

    plt.xlabel("Cut Value")
    plt.ylabel("Frequency")
    plt.title('Graph ' + nameGraph + ' Algorithm ' + nameAlg + "\nNumber of run " + str(numberOfRun))

    plt.savefig(dirImg + nameGraph + '-' + nameAlg + '-hist.png')

    plt.show()


def scatter():

    area = 1
    plt.scatter(range(0, numberOfRun), data, s=area, marker='s')
    #plt.plot([1, numberOfRun], [5000, 5000], color='red')	#draw an horizontal line

    plt.xlabel("Run")
    plt.ylabel("Cut Value")
    plt.title('Graph ' + nameGraph + ' Algorithm ' + nameAlg + "\nNumber of run " + str(numberOfRun))

    plt.savefig(dirImg + nameGraph + '-' + nameAlg + '-scatter.png')

    plt.show()

def normalityTest():
    k2, p = stats.normaltest((data-data.mean())/data.std())	#D'Agostino-Pearson test
    alpha = 0.05
    # pts = 1000
    # np.random.seed(28041990)
    # #a = np.random.normal(0, 1, size=pts)
    # b = np.random.poisson(2, size=pts)
    # x = b
    # k2, p = stats.normaltest(x)
    print("p = {:g}".format(p))

    if p < alpha:  # null hypothesis: x comes from a normal distribution
        print("The null hypothesis can be rejected")
    else:
        print("The null hypothesis cannot be rejected")


def shapiroWilkTest():
    numberOfData = numberOfRun
    if (numberOfRun > 5000):
        numberOfData = numberOfRun/2 - 1

    k2, p = stats.shapiro(((data-data.mean())/data.std())[0:numberOfData])

    alpha = 0.05
    print("p = {:g}".format(p))

    if p < alpha:  # null hypothesis: x comes from a normal distribution
        print("The null hypothesis can be rejected")
    else:
        print("The null hypothesis cannot be rejected")


def kolmogorovSmirnovTest():
    k2, p = stats.kstest((data-data.mean())/data.std(), 'norm')


    alpha = 0.05
    print(k2)
    print("p = {:g}".format(p))

    if p < alpha:  # null hypothesis: x comes from a normal distribution
        print("The null hypothesis can be rejected")
    else:
        print("The null hypothesis cannot be rejected")



def qqplot():


    stats.probplot((data-data.mean())/data.std(), plot=plt)
    plt.title('Graph ' + nameGraph + ' Algorithm ' + nameAlg + "\nNumber of run " + str(numberOfRun))
    plt.savefig(dirImg + nameGraph + '-' + nameAlg + '-qqplot.png')

    plt.show()


def mean_stdPlot():


    names = namesAlg# ['prob', 'greedy', 'greedyProb', 'greedyProbFixed']
    colors = ['blue', 'orange', 'red', 'green']
    #names = ['prob']
    means = []
    stds = []
    max = []
    y = []
    for i in range(0, len(names)):
        d = pd.read_csv(dir + nameGraph + '-' + names[i], sep=',', header=None)  # read file
        means.append(d[0].mean())
        stds.append(d[0].std())
        max.append(d[0].max())
        y.append(i)

    x = np.array(y)
    y = np.array(means)
    e = np.array(stds)

    for i in range(0, len(names)):
        plt.errorbar(x[i], means[i], stds[i], linestyle='None', marker='s', color=colors[i])



    # plt.plot([0, 3], [opt, opt], color='purple')	#draw an horizontal line

    plt.title('Graph ' + nameGraph)
    plt.savefig(dirImg + nameGraph + 'total.png')

    plt.show()

    # plt.plot([0, 4], [1100, 1100], color='blue')	#draw an horizontal line
    # plt.plot([1, 1], [0, max[0]], color='red')  # draw an horizontal line
    # plt.plot([2, 2], [0, max[1]], color='orange')  # draw an horizontal line
    # plt.plot([3, 3], [0, max[2]], color='green')  # draw an horizontal line
    # plt.plot([4, 4], [0, max[3]], color='purple')  # draw an horizontal line
    #
    # plt.title('Graph ' + nameGraph)
    # plt.savefig(nameGraph + 'compare.png')
    #
    # plt.show()

if(__name__ == "__main__"):



    for i in range(0, len(namesAlg)):
        print("Algoritmo " + namesAlg[i])
        nameAlg = namesAlg[i]
        numberOfRun = numbersOfRun[i]

        d = pd.read_csv(dir + nameGraph + '-' + nameAlg, sep=',', header=None)  # read file
        data = d[0].copy()  # take the first and only one column

        histogram()
        scatter()

        normalityTest()
        shapiroWilkTest()
        kolmogorovSmirnovTest()

        qqplot()

        print("max " + str(max(data)))
        print("min " + str(min(data)))
        print("mean" + str(data.mean()))
        print("std " + str(data.std()))
        print("median " + str(data.median()))
        print

    mean_stdPlot()
