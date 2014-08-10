#!/usr/bin/python
#-*- coding: utf-8 -*-
import sqlite3
import os
import sys
import time
import markdown


#config
articlePath ='content'
dbName = 'blog.db'
#


def listfile(articlePath):
	if not os.path.exists(articlePath):
		print "Article path not existed.Please recheck you article path."
		sys.exit(-1)
	allfile = os.listdir(articlePath)
	mdFile = []
	for file in allfile:
		temp=file.split('.')
		if temp[-1] == 'md':
			mdFile.append(file)
	return mdFile

def readfile(filename):
	filePath =  articlePath+'/'+filename
	fileHandle = open(filePath,'r')
	lines = fileHandle.readlines()
	articleDic = {}
	#read article info 
	for line in lines[0:7]:
		line= line.strip('\n')
		splitLine = line.split(':',1)
		articleDic[splitLine[0]] = splitLine[1].strip(' ')
	#read article content
	articleDic['Content'] = markdown.markdown(''.join(lines[8:]).decode('utf-8'))
	articleDic['Time'] = time.mktime(time.strptime(articleDic['Date'],'%Y-%m-%d %H:%M'))

	fileHandle.close()
	return articleDic


def timesort (articleContainer):
	articleNum = len(articleContainer)
	for i in xrange(0,articleNum):
		for j in xrange(i,articleNum):
			if float(articleContainer[i]['Time']) > float(articleContainer[j]['Time']) :
				temp = articleContainer[i]
				articleContainer[i] =  articleContainer[j]
				articleContainer[j] =  temp
	return articleContainer


def savedb(article,articleId):
	insert_sql = "insert into articles (Id,Time,Title,Date,Catagory,Tags,Slug,Author,Summary,Content) values (?,?,?,?,?,?,?,?,?,?)"
	connection = sqlite3.connect(dbName);
	connection.text_factory = str
	cursor = connection.cursor()
	cursor.execute(insert_sql,(articleId,article['Time'],article['Title'],article['Date'],article['Category'],\
			article['Tags'],article['Slug'],article['Author'],article['Summary'],article['Content']))
	connection.commit()
	connection.close()

def createdb():
	#if sqlitedb exists then delete it 
	if os.path.exists(dbName):
		os.remove(dbName)
		print "Delete the old db"
	create_table_sql="""
	create table articles(
		Id integer primary key autoincrement unique not null,
		Time text not null,
		Title text not null,
		Date text not null,
		Catagory text,
		Tags text,
		Slug text not null,
		Author text not null,
		Summary text not null,
		Content text
	);
	"""
	connection = sqlite3.connect(dbName);
	connection.text_factory = str
	cursor = connection.cursor()
	cursor.execute(create_table_sql)
	connection.close()

def debug():
	#debug code
	connection = sqlite3.connect(dbName);
	connection.text_factory = str
	cursor = connection.cursor()
	select_sql = "SELECT * FROM articles"
	cursor.execute(select_sql)
	data = cursor.fetchall()
	for t in data:
		print t[0]
		for x in t[1:]:
		    print  x.decode('utf-8')
	connection.close()

def markfile(fileName):
	filePath = articlePath+'/'+fileName
	os.rename(filePath,filePath+'.marked')

def clearmark():
	allFile = os.listdir(articlePath)
	for fileName in allFile:
		if fileName.split('.')[-1] == 'marked':
			newName = '.'.join(fileName.split('.')[:-1])
			filePath = articlePath+'/'+fileName
			filePathC = articlePath+'/'+newName
			os.rename(filePath,filePathC)

def getid():
	connection = sqlite3.connect(dbName);
	connection.text_factory = str
	cursor = connection.cursor()
	select_sql = "SELECT Id FROM articles"
	cursor.execute(select_sql)
	data = cursor.fetchall()
	connection.close()
	return data[-1][0]


			
def run_rebuild_mode():
	currentPath = os.getcwd()
	articleContainer = []
	createdb()
	clearmark()
	mdFile = listfile(articlePath)
	for fileName in mdFile:
		articleContainer.append(readfile(fileName))
		markfile(fileName)
	articleContainer = timesort(articleContainer)
	for article in articleContainer:
		articleId = articleContainer.index(article)
		savedb(article,articleId)
	print "rebuild db sucessful!"
	#debug()
	#print articleContainer


def run_refresh_mode():
	articleContainer = []
	mdFile = listfile(articlePath)
	if mdFile == []:
		print "Non new article"
		sys.exit(-1)
	else:
		print "new article:"
		for new in mdFile:
			print new
	for fileName in mdFile:
		articleContainer.append(readfile(fileName))
		markfile(fileName)
	articleContainer = timesort(articleContainer)
	for article in articleContainer:
		articleId = getid()+articleContainer.index(article)+1
		savedb(article,articleId)
	print "refresh db sucessful!"
	#debug()


def test():
	print getid()



if __name__ == '__main__':

	if len(sys.argv) > 1 and sys.argv[1] == "refresh":
		run_refresh_mode()
	elif len(sys.argv) > 1 and  sys.argv[1] == "rebuild":
		run_rebuild_mode()
	else:
		print 'usage:\npython autodb.py refresh\t#refresh your db\npython autodb.py rebuild\t#rebuild your db'
		#test()

