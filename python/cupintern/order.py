import pickle
import math

global score
score={}

def readneed():
    
    str1 = input("please enter your keyword,split by")
    global list1
    list1=str1.split(" ")

def opendict():
    t = open("TFIDF2.pkl","rb")
    global tfidf
    tfidf = pickle.load(t)
    t.close()
    f = open("fileName.pkl","rb")
    global fileName
    fileName=pickle.load(f)
    f.close()
def calculate(f):
    grade = 1
    for item in list1:
        try:
            grade = grade+ tfidf[item].get(f,0)
        except:
            continue
    score[f]=   grade 

if __name__ == "__main__":
    
    
    readneed()
    opendict()
    for i in fileName:
        calculate(i)

    for b in range(10):
        c= max(score.items(),key = lambda d:d[1])
        print(c)
        del score[c[0]]
    
    
