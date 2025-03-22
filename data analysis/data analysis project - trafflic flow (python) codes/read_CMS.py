import os
import csv
import xml.etree.ElementTree as ET


def read_one_CMS(folder_name, file_name, CMS_list):

    # build the xml tree
    tree = ET.parse(os.path.join(folder_name, file_name))
    namespace = {"ns": "http://traffic.transportdata.tw/standard/traffic/schema/"}

    # output: results[CMS_index] = its message
    results = ["" for i in range(len(CMS_list))]
    CMS_to_be_finished = len(CMS_list)

    CMS_lives = tree.findall("./ns:CMSLives/ns:CMSLive", namespaces = namespace)
    for CMS_live in CMS_lives:
        CMSID = CMS_live.find("./ns:CMSID", namespaces = namespace)

        for CMS_index in range(len(CMS_list)):  # find the targeted CMS
            if CMSID.text != CMS_list[CMS_index]:
                continue
            
            # find the message
            results[CMS_index] = CMS_live.find("./ns:Messages/ns:Message/ns:Text", namespaces = namespace).text
            CMS_to_be_finished -= 1
            break
        
        if CMS_to_be_finished == 0:  # have found all of the CMS
            return results
        

def read_all_CMS(xml_folder_name, output_folder_name, output_file_name, CMS_list):

    # files = [name of the xml files in the folder]
    files = [f for f in os.listdir(xml_folder_name) \
            if os.path.isfile(os.path.join(xml_folder_name, f))]

    with open(os.path.join(output_folder_name, output_file_name), \
        mode = "w", newline = "", encoding = "utf-8") as output:

        # set the csv writer
        writer = csv.writer(output)
        
        # write the title
        title = ["年", "月", "日", "時", "分", "CMS編號", "顯示資訊"]
        writer.writerow(title)

        # read each CMS
        for file_name in files :

            # read one CMS, which return a list of string
            messages = read_one_CMS(xml_folder_name, file_name, CMS_list)

            # CMS file name e.g. CMSLive_20240327_0930.xml
            y = file_name[8:12]
            month = file_name[12:14]
            d = file_name[14:16]
            h = file_name[17:19]
            min = file_name[19:21]
            
            for i in range(len(CMS_list)):
                writer.writerow([y, month, d, h, min, CMS_list[i], messages[i]])
            print(file_name, "read finished")


if __name__ == "__main__":

    # set the CMS path
    xml_file_path = \
        "C:/Users/jaspe/Desktop/課程/資料分析/data_analysis_module3/CMS/"

    # CMS_list = [targeted CMS]
    CMS_list = ["CMS-N1-N-43.470-M", "CMS-N1-N-45.700-M", "CMS-N1-N-51.160-M"]

    # set the output csv file path and name
    output_file_name = "CMS_output.csv"
    output_folder_name = \
        "C:/Users/jaspe/Desktop/課程/資料分析/data_analysis_module3/"

    read_all_CMS(xml_file_path, output_folder_name, output_file_name, CMS_list)