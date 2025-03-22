import os
import csv
import numpy as np
import xml.etree.ElementTree as ET


def read_one_xml(folder_name, file_name, vd_id_list):

    # build the xml tree
    tree = ET.parse(os.path.join(folder_name, file_name))
    namespace = {"ns": "http://traffic.transportdata.tw/standard/traffic/schema/"}

    # output: results[vd_index] = result_row (see below)
    results = [None for i in range(len(vd_id_list))]
    vd_id_to_be_finished = len(vd_id_list)

    vd_lives = tree.findall("./ns:VDLives/ns:VDLive", namespaces = namespace)
    for vd_live in vd_lives:
        vdID = vd_live.find("./ns:VDID", namespaces = namespace)

        for vd_index in range(len(vd_id_list)):  # find the targeted vd_id
            if vdID.text != vd_id_list[vd_index]:
                continue
            
            # find tag: lane
            lanes = vd_live.findall("./ns:LinkFlows/ns:LinkFlow/ns:Lanes/ns:Lane", namespaces = namespace)
            
            # result_row[lane num] = a row with the following result
            # [avg_speed, occupancy, S_volume, S_speed, L_volume, L_speed, T_volume, T_speed]
            result_row = np.empty((len(lanes), 8), dtype = int)

            for i in range(len(lanes)):
                avg_speed = lanes[i].find("./ns:Speed", namespaces = namespace)
                result_row[i][0] = int(avg_speed.text)  # average speed
                occupancy = lanes[i].find("./ns:Occupancy", namespaces = namespace)
                result_row[i][1] = int(occupancy.text)  # occupancy
                
                vehicles = lanes[i].findall("./ns:Vehicles/ns:Vehicle", namespaces = namespace)
                for j in range(3):  # three types of vehicles
                    volume = int(vehicles[j].find("./ns:Volume", namespaces = namespace).text)  
                    result_row[i][2*j+2] = volume  # volume for S / L / T
                    speed = int(vehicles[j].find("./ns:Speed", namespaces = namespace).text) 
                    result_row[i][2*j+3] = speed   # speed for S / L / T
            
            results[vd_index] = result_row.reshape(-1)
            vd_id_to_be_finished -= 1
            break
        
        if vd_id_to_be_finished == 0:  # have found all of the vd_id
            return results
        

def read_all_xml(xml_folder_name, output_folder_name, output_file_name, vd_id_list):

    # files = [name of the xml files in the folder]
    files = [f for f in os.listdir(xml_folder_name) \
            if os.path.isfile(os.path.join(xml_folder_name, f))]

    with open(os.path.join(output_folder_name, output_file_name), \
        mode = "w", newline = "", encoding = "utf-8") as output:

        # set the csv writer
        writer = csv.writer(output)
        
        # write the title
        title = ["年", "月", "日", "時", "分", "偵測器編號"]
        for i in range(5):  # default: 5 lanes
            title += ["車道 "+str(i)+" 速率", "車道 "+str(i)+" 佔有率"]
            for j in [" S", " T", " L"]:
                title += ["車道 " + str(i) + j + " 流量", "車道 " + str(i) + j + " 速率"]
        
        writer.writerow(title)

        # read each xml
        for file_name in files :

            # read one xml, which return a numpy as outputs
            outputs = read_one_xml(xml_folder_name, file_name, vd_id_list)
            for i in range(len(vd_id_list)):

                # xml file name e.g. VDLive_20240327_0930.xml
                y = file_name[7:11]
                month = file_name[11:13]
                d = file_name[13:15]
                h = file_name[16:18]
                min = file_name[18:20]
                merged_row = np.concatenate \
                    (([y, month, d, h, min, vd_id_list[i]], outputs[i]), axis = 0)
                writer.writerow(merged_row)
            
            print(file_name, "read finished")


if __name__ == "__main__":

    # set the xml path
    xml_file_path = \
        "C:/Users/jaspe/Desktop/課程/資料分析/data_analysis_module3/xml/"

    # vd_id_list = [targeted vd_id]
    vd_id_list = ["VD-N1-N-42.050-M-LOOP", "VD-N1-N-43.320-M-LOOP", \
                "VD-N1-N-45.520-M-LOOP", "VD-N1-N-47.300-M-RS"]

    # set the output csv file path and name
    output_file_name = "VD_output.csv"
    output_folder_name = \
        "C:/Users/jaspe/Desktop/課程/資料分析/data_analysis_module3/"

    read_all_xml(xml_file_path, output_folder_name, output_file_name, vd_id_list)