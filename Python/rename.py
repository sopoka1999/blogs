import os
path='C:/Users/Administrator/Desktop/歌曲/'  

#获取该目录下所有文件，存入列表中
fileList=os.listdir(path)
print(path)
for i in fileList:
    
    #设置旧文件名（就是路径+文件名）
    oldname=path+ os.sep + i   # os.sep添加系统分隔符
    if i == "a.py":
        continue
    str1 = i.split("-")[0]
    str2 = i.split("-")[1].split(".")[0]
    print( str2+" - "+str1+".mp3")
    #设置新文件名
    newname=path + os.sep+ str2+" - "+str1+".mp3"
    
    os.rename(oldname,newname)   #用os模块中的rename方法对文件改名
   # print(oldname,'======>',newname)
