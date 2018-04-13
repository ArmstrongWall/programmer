#!/bin/bash
clear
rm -rf label_pic
mkdir label_pic
ls *.json > ls.txt
for line in $(cat ls.txt)
	do 
     		labelme_json_to_dataset ${line}
     		dirname=${line/./_}
		pngfilename=${line%.*}'.png'
		txtfilename=${line%.*}'.yaml'
		cp ${dirname}/label.png ./label_pic/${pngfilename}
		cp ${dirname}/info.yaml ./label_pic/${txtfilename}
 	done

