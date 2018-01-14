# -*- coding: utf-8 -*-
#!/user/bin/python
#codeing:gb18030
# coding=utf-8
import sys
import time
import os
import math
import os.path
import pickle
import jieba
global wordict1
wordict1 = {}
global wordict2
wordict2 = {}
global freq
freq = {}
global Bank
Bank={}

def opentext():
    t = open('list dictall2.pkl','rb')

    global text
    text= pickle.load(t)
    t.close()
def builddict():
    f = open('fileName.pkl','rb')
    s = open('stopdict.pkl','rb')
    b = open('bankdict.pkl','rb')
    c = open('cikudict.pkl','rb')
    global fileName
    fileName = pickle.load(f)
    global dstop
    dstop = pickle.load(s)
    global dbank
    dbank = pickle.load(b)
    global dciku
    dciku = pickle.load(c)

    f.close()
    s.close()
    b.close()
    c.close()

    global fnameLen
    fnameLen=len(fileName)

    
def process(n):
    wordlist=[]
    global Bank
    Bank= {}
    Bank[fileName[n]] = []
    result = text[fileName[n]]
####    for res in result:
####        g = jieba.cut(res)
####        for i in g:
####            wordlist.append(i)


    for res in result:
        head=0
        maxWordLen=12
     
        resultLen=len(res)
        wordLen=min(maxWordLen,resultLen)
    
        while head< resultLen:  # 从第一个字符循环到最后一个字符
            matched = False
            for i in range(maxWordLen, 0, -1):  # 从最大词长5递减到1
                string = res[head:head+i]#定下字长
                if string in dstop:                    
                    matched=True
                    break
                if string in dbank:
                    Bank[fileName[n]].append(string)
                if string in dciku:
                    wordlist.append(string)
                    matched=True
                    break
                        

            head += i
    allword= set(wordlist)
    wordict1[fileName[n]]=[]
    freq[fileName[n]] = {}
    for item in allword:
        wordict2[item] = wordict2.get(item,1)+1
        a = wordlist.count(item)
        b = len(wordlist)
        freq[fileName[n]].update({item:a/b})
        wordict1[fileName[n]].append(item)

   
def keyword(n):
    global TFIDF 
    TFIDF = {}
    TFIDF[fileName[n]] = {}
    for item in wordict1[fileName[n]]:

        TF = freq[fileName[n]][item]
        IDF = math.log(fnameLen/wordict2[item])
        
        b2 = 1.0
        a2 = b2*TF*IDF
        TFIDF[fileName[n]].update({item:a2})


    with open('KEYWORD9-4(2.txt',mode = 'a', encoding = 'utf-8') as fi:
        fi.write('\n')
        fi.write(fileName[n]+'\t')
       
        for i in range(10):
            c = max(TFIDF[fileName[n]].items(),key = lambda d:d[1])
            
            fi.write(str(c[0])+'\t')
            fi.write(str(c[1])+'\n')
            fi.write(fileName[n]+'\t')
            del TFIDF[fileName[n]][c[0]]

    
if __name__ == "__main__" :
    start = time.clock()
    success=0
    successfile=[]
    failure=0
    builddict()
    opentext()
    for n in range(0,fnameLen):
        print(n)
        try:
            process(n)
            print('successfully break '+fileName[n])
            success+=1
            successfile.append(fileName[n])
        except:
            print('can not break'+fileName[n]+'\n')
            failure+=1

            continue
    time.sleep(5)


    for k in range(0,len(successfile)):    
        print('No.',k)
        
        try:
            keyword(k)
        except:
            print('can not anlyze '+fileName[k]+'\n')
            continue
    
    time.sleep(3)


    print("success=",success)
    print("failure=",failure)
    end = time.clock()
    print(end-start)

                    
    
    
    
    
    
    
