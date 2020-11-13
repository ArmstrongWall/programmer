#!/usr/bin/python
# -*- coding: utf-8 -*
import xlrd
import xlwt
#导入读和写两个模块

workbook = xlrd.open_workbook(r'demo.xls')
#以读方式打开“demo.xls”，命名为workbook
print workbook.sheet_names()
SheetRead = workbook.sheet_by_name('Sheet1')
print SheetRead.name,SheetRead.nrows,SheetRead.ncols

RowsNumber=SheetRead.nrows
#将sheet1的行数赋值给RowsNumber

BookToWrite = xlwt.Workbook()
SheetWrite = BookToWrite.add_sheet(u'sheet1')

#使用一个循环，把每一行都加上Client
for i in range(0,RowsNumber):
    Name=SheetRead.cell_value(i,0)
    Tell=SheetRead.cell_value(i,1)
    print Tell
    Name='Client'+Name
    if Name == 'Client':
        Name = ''
    SheetWrite.write(i,0,Name)
    SheetWrite.write(i,1,Tell)

BookToWrite.save('demo1.xls')