#!/usr/bin/python
# -*- coding: utf-8 -*
import xlrd
import xlwt
#�������д����ģ��

workbook = xlrd.open_workbook(r'demo.xls')
#�Զ���ʽ�򿪡�demo.xls��������Ϊworkbook
print workbook.sheet_names()
SheetRead = workbook.sheet_by_name('Sheet1')
print SheetRead.name,SheetRead.nrows,SheetRead.ncols

RowsNumber=SheetRead.nrows
#��sheet1��������ֵ��RowsNumber

BookToWrite = xlwt.Workbook()
SheetWrite = BookToWrite.add_sheet(u'sheet1')

#ʹ��һ��ѭ������ÿһ�ж�����Client
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