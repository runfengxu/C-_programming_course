
from tkinter import *
import pickle
import math

global score
score={}
def getvar():
    s = var.get()
    list1=s.split(" ")
    r = open("TFIDF2.pkl","rb")
    tfidf = pickle.load(r)
    r.close() 
    f = open("fileName.pkl","rb")
    fileName=pickle.load(f)
    f.close()
    t.delete(0.0, END)
    for f in fileName:
        grade = 1
        for item in list1:
            try:
                grade = grade+ tfidf[item].get(f,0)
            except:
                continue
        score[f]=grade
    for b in range(10):
        c= max(score.items(),key = lambda d:d[1])
        t.insert(1.0,str(c[0]))
        t.insert(1.0,'\n')
        del score[c[0]]
    
root = Tk()


root.title("银联数据文档查询")
root.geometry('500x300')
root.resizable(width = True,height = True)


Label(root,text = "请输入搜索关键词".encode('utf8').decode("utf8"),font=('Arial',20)).pack()

t=Text(root)
var = StringVar()
e  = Entry(root,textvariable = var).pack()
Button(root,text="press",command=getvar).pack(side=TOP)
t.pack()

root.mainloop()
