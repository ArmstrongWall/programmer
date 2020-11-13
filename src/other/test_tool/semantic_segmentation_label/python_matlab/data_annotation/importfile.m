function importfile(fileToRead1)
%IMPORTFILE(FILETOREAD1)
%  从指定文件中导入数据
%  FILETOREAD1:  要读取的文件
% 导入文件
rawData1 = importdata(fileToRead1);

% 对于一些简单文件(如 CSV 或 JPEG 文件)，IMPORTDATA 可能会
% 返回一个简单数组。如果是这样，将生成一个结构体，以便该输出
% 与导入向导的输出匹配。
[~,name] = fileparts(fileToRead1);
newData1.(matlab.lang.makeValidName(name)) = rawData1;

% 在基础工作区中从这些字段创建新变量。
vars = fieldnames(newData1);
for i = 1:length(vars)
    assignin('base', vars{i}, newData1.(vars{i}));
end

