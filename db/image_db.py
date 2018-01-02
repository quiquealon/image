import matplotlib
import glob
import numpy
import pandas
from sklearn import cluster
from sklearn import decomposition
from sklearn import neighbors
from matplotlib import pyplot
from PIL import Image
import pathlib


path_1 = "1271/"
path_2 = "1808/"

# define the path
currentDirectory = pathlib.Path(path_2)

# define the pattern
currentPattern = "*.JPEG"


ms = 0
imgs = []

for currentFile in currentDirectory.glob(currentPattern):  
#    print(currentFile)
    imgs.append(str(currentFile))
    ms += 1
print(imgs)

print(ms)


im = [numpy.asarray(Image.open(x)) for x in imgs]
pyplot.imshow(im[5])
#pyplot.show()

flat_individual = [x.reshape(x.shape[0] * x.shape[1], 3) for x in im if len(x.shape) == 3]

print("OK !")

c = 0
def primary_colours(x):
    km = cluster.MiniBatchKMeans(5)
    km.fit(x)
    cc = km.cluster_centers_.copy()
    global c
    
    with open("imgs_features.csv", 'a') as w:
        w.write(imgs[c] + "," + str(cc[0][0]) + "," + str(cc[0][1]) + "," + str(cc[0][2]) \
                                + str(cc[1][0]) + "," + str(cc[1][1]) + "," + str(cc[1][2])\
                                + str(cc[2][0]) + "," + str(cc[2][1]) + "," + str(cc[2][2])\
                                + str(cc[3][0]) + "," + str(cc[3][1]) + "," + str(cc[3][2])\
                                + str(cc[4][0]) + "," + str(cc[4][1]) + "," + str(cc[4][2]) + "\n")
    w.close()
    c+=1
    print(c)
#    print(cc)
    return cc
    
print("OK !!")
features = [primary_colours(x) for x in flat_individual]

#for(i in features[0]):
#	print("MS: " i)

print("OK !!!")
#f, ax = pyplot.subplots(1)
#f.set_size_inches(10, 10)
#ax.set_title('5 primary colours per image')
#ax.imshow(numpy.array(features[5:15]).reshape(10, 5, 3) / 255, interpolation='nearest')
#pyplot.show()

#print("OK !!!!")


