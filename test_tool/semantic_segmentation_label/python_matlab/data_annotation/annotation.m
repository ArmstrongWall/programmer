field1 = 'road';       value1   = [128,64,128]/256;
field2 = 'sidewalk';   value2   = [244, 35, 232]/256;
field3 = 'building';   value3   = [70, 70, 70]/256;
field4 = 'wall';       value4   = [102, 102, 156]/256;
field5 = 'fence';      value5   = [190, 153, 153]/256;
field6 = 'pole';       value6   = [153, 153, 153]/256;
field7 = 'light';      value7   = [250, 170, 30]/256;
field8 = 'sign';       value8   = [220, 220, 0]/256;
field9 = 'vegetation'; value9   = [107, 142, 35]/256;
field10 = 'terrain';   value10  = [152, 251, 152]/256;
field11 = 'sky';       value11  = [70, 130, 180]/256;
field12 = 'person';    value12  = [220, 20, 60]/256;
field13 = 'rider';     value13  = [255, 0, 0]/256;
field14 = 'car';       value14  = [0, 0, 142]/256;
field15 = 'truck';     value15  = [0, 0, 70]/256;
field16 = 'bus';       value16  = [0, 60, 100]/256;
field17 = 'train';     value17  = [0, 80, 100]/256;
field18 = 'motorcycle';value18  = [0, 0, 230]/256;
field19 = 'bicycle';   value19  = [119, 11, 32]/256;

s = struct(field1,value1,field2,value2,field3,value3,field4,value4,field5,value5,field6,value6,field7,value7,field8,value8,field9,value9,field10,value10,field11,value11,field12,value12,field13,value13,field14,value14,field15,value15,field16,value16,field17,value17,field18,value18,field19,value19);

label=char('road', 'sidewalk', 'building','wall' ,'fence', 'pole' ,'light','sign' , 'vegetation','terrain', 'sky' , 'person','rider', 'car','truck','bus' , 'train' ,'motorcycle' ,'bicycle');
imgPath = 'label_pic/';        % 图像库路径
imgDir  = dir([imgPath '*.png']); % 遍历所有jpg格式文件
for i = 1:length(imgDir)          % 遍历结构体就可以一一处理图片了
    importfile([imgPath imgDir(i).name]); %读取每张图片
    match = ["label_pic/",".png"];
    matrix_name = ['x',erase([imgPath imgDir(i).name],match)];
    disp (matrix_name);
    matrix=eval(matrix_name);
    [m,n] = size(matrix);
    txt_name = strrep([imgPath imgDir(i).name],"png","yaml");
    disp (txt_name);
    X = YAML.read(txt_name); % load X from a yaml file
    for r=1:m
        for c=1:n
                if  isfield(X.label_names,'road' ) == 1
                    if matrix(r,c) == X.label_names.road
                        imgData(r,c,:) = s.road;
                    end
                end
                if  isfield(X.label_names,'sidewalk' ) == 1
                    if matrix(r,c) == X.label_names.sidewalk
                        imgData(r,c,:) = s.sidewalk;
                    end
                end
                if  isfield(X.label_names,'building' ) == 1
                    if matrix(r,c) == X.label_names.building
                        imgData(r,c,:) = s.building;
                    end
                end
                if  isfield(X.label_names,'wall' ) == 1
                    if matrix(r,c) == X.label_names.wall
                        imgData(r,c,:) = s.wall;
                    end
                end
                if  isfield(X.label_names,'fence' ) == 1
                    if matrix(r,c) == X.label_names.fence
                        imgData(r,c,:) = s.fence;
                    end
                end
                if  isfield(X.label_names,'pole' ) == 1
                    if matrix(r,c) == X.label_names.pole
                        imgData(r,c,:) = s.pole;
                    end
                end
                if  isfield(X.label_names,'light' ) == 1
                    if matrix(r,c) == X.label_names.light
                        imgData(r,c,:) = s.light;
                    end
                end
                if  isfield(X.label_names,'sign' ) == 1
                    if matrix(r,c) == X.label_names.sign
                        imgData(r,c,:) = s.sign;
                    end
                end
                if  isfield(X.label_names,'vegetation' ) == 1
                    if matrix(r,c) == X.label_names.vegetation
                        imgData(r,c,:) = s.vegetation;
                    end
                end
                if  isfield(X.label_names,'terrain' ) == 1
                    if matrix(r,c) == X.label_names.terrain
                        imgData(r,c,:) = s.terrain;
                    end
                end
                if  isfield(X.label_names,'sky' ) == 1
                    if matrix(r,c) == X.label_names.sky
                        imgData(r,c,:) = s.sky;
                    end
                end
                if  isfield(X.label_names,'person' ) == 1
                    if matrix(r,c) == X.label_names.person
                        imgData(r,c,:) = s.person;
                    end
                end
                if  isfield(X.label_names,'rider' ) == 1
                    if matrix(r,c) == X.label_names.rider
                        imgData(r,c,:) = s.rider;
                    end
                end
                if  isfield(X.label_names,'car' ) == 1
                    if matrix(r,c) == X.label_names.car
                        imgData(r,c,:) = s.car;
                    end
                end
                if  isfield(X.label_names,'truck' ) == 1
                    if matrix(r,c) == X.label_names.truck
                        imgData(r,c,:) = s.truck;
                    end
                end
                if  isfield(X.label_names,'bus' ) == 1
                    if matrix(r,c) == X.label_names.bus
                        imgData(r,c,:) = s.bus;
                    end
                end
                if  isfield(X.label_names,'train' ) == 1
                    if matrix(r,c) == X.label_names.train
                        imgData(r,c,:) = s.train;
                    end
                end
                if  isfield(X.label_names,'motorcycle' ) == 1
                    if matrix(r,c) == X.label_names.motorcycle
                        imgData(r,c,:) = s.motorcycle;
                    end
                end
                if  isfield(X.label_names,'bicycle' ) == 1
                    if matrix(r,c) == X.label_names.bicycle
                        imgData(r,c,:) = s.bicycle;
                    end
                end
                
                
         
        end
    end
    file_name = ['out_pic',erase([imgPath imgDir(i).name],'label_pic')];
    disp (file_name);
    imwrite(imgData,file_name,'png','Comment','My png file')%写图片
end

