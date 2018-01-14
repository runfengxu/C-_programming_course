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

global wordict1
wordict1 = {}
global wordict2
wordict2 = {}
global freq
freq = {}
global Bank
Bank={}

def opentext():   #打开pkl文件读取 文档内容
    t = open('list dictall2.pkl','rb')
    global text
    text= pickle.load(t)
    t.close()
def builddict():  #建立分词的素材字典
    s = open('stopdict.pkl','rb')
    b = open('bankdict.pkl','rb')
    c = open('cikudict.pkl','rb')
    global fileName
    fileName =[]
    for key in text:
        fileName.append(key)
    global dstop
    dstop = pickle.load(s)
    global dbank
    dbank = pickle.load(b)
    global dciku
    dciku = pickle.load(c)
    s.close()
    b.close()
    c.close()

    global fnameLen
    fnameLen=len(fileName)

    
def process(n):   #进行分词，对每篇文章进行分词统计记录，每个n代表一篇文章
    wordlist=[]

    Bank[fileName[n]] = []
    result = text[fileName[n]]
    for res in result:          
        head=0
        maxWordLen=12
     
        resultLen=len(res)
        wordLen=min(maxWordLen,resultLen)
    
        while head< resultLen:  
            matched = False
            for i in range(maxWordLen, 0, -1):  
                string = res[head:head+i]
                if string in dstop:                    
                    matched=True
                    break
                if string in dbank:
                    Bank[fileName[n]].append(string)
                    break
                if string in dciku:
                    wordlist.append(string)
                    matched=True
                    break
                        

            head += i
    allword= set(wordlist)                 #分词结束，统计分词结果
    wordict1[fileName[n]]=[]
    freq[fileName[n]] = {}
    for item in allword:
        wordict2[item] = wordict2.get(item,1)+1
        a = wordlist.count(item)
        b = len(wordlist)
        freq[fileName[n]].update({item:a/b})
        wordict1[fileName[n]].append(item)

def keyword(n):                         #计算tfidf值
##    TFIDF[fileName[n]] = {}
    for item in wordict1[fileName[n]]:
        TF = freq[fileName[n]][item]
        IDF = math.log(fnameLen/wordict2[item])        
        b2 = 1.0
        a2 = b2*TF*IDF
##        TFIDF[fileName[n]].update({item:a2})
        TFIDF2[item]=TFIDF2.get(item,{})
        TFIDF2[item].update({fileName[n]:a2})
    
if __name__ == "__main__" :
    start = time.clock()
    success=0
    failure=0
    opentext()
    builddict()
    
    for n in range(0,fnameLen):              #对每篇文章进行分词
        
        try:
            process(n)
##            print('successfully break '+fileName[n])
            success+=1
##            success.append(fileName[n])
        except:
            print('can not break'+fileName[n]+'\n')
            failure+=1
##            failname.append(fileName[n])
            continue
    time.sleep(5)
##    out3 = open('BANK.pkl','wb')
##    pickle.dump(Bank,out3)
##    out3.close()
    global TFIDF               #字典结构{“文档名”：{“词”：tfidf值}}
    TFIDF = {}
    global TFIDF2              #字典结构{“词”：{“文档名”：tfidf值}}
    TFIDF2 = {}
    for k in range(0,fnameLen):     #对每篇文章提取关键词
        try:
            keyword(k)
        except:
            print('can not anlyze '+fileName[k]+'\n')
            continue
##    out = open('TFIDF.pkl','wb')            #将两个tfidf字典存入pkl文件
##    pickle.dump(TFIDF,out)
##    out.close()
    out2 = open('TFIDF2.pkl','wb')
    pickle.dump(TFIDF2,out2)
    out2.close()
    time.sleep(3)


    print("success=",success)
    print("failure=",failure)
    end = time.clock()
    print(end-start)

                    
    
    
    
    
    
    
