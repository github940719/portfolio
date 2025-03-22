import requests
import os
import gzip
import shutil


def download_one_file(y, month, d, h, min, gz_file_path, xml_file_path):

    # request response from the url
    url = "https://tisvcloud.freeway.gov.tw/history/motc20/VD/"
    url_file = f"{y}{month:02}{d:02}/VDLive_{h:02}{min:02}.xml.gz"
    response = requests.get(url + url_file)

    # set the gz_file path and name
    gz_file_name = f"VDLive_{y}{month:02}{d:02}_{h:02}{min:02}.xml.gz"
    if not os.path.exists(gz_file_path):
        os.makedirs(gz_file_path)  # make the directory

    # download the gz file
    with open(os.path.join(gz_file_path, gz_file_name), "wb") as file:
        file.write(response.content)

    # set the xml_file path and name
    xml_file_name = f"VDLive_{y}{month:02}{d:02}_{h:02}{min:02}.xml"
    if not os.path.exists(xml_file_path):
        os.makedirs(xml_file_path)  # make the directory

    # extract gz into xml
    with gzip.open(os.path.join(gz_file_path, gz_file_name), "rb") as gz_file, \
        open(os.path.join(xml_file_path, xml_file_name), "wb") as xml_file:
        shutil.copyfileobj(gz_file, xml_file)
    
    print(xml_file_name, "download finished")


def for_loop(y, month, d, h_start, min_start, h_end, min_end, gz_file_path, xml_file_path):
    # h_start = h_end : min from min_start to min_end
    if (h_start == h_end):
        for min in range(min_start, min_end+1):
            download_one_file(y, month, d, h_start, min, gz_file_path, xml_file_path)
    
    else:
        # the first hour : min from min_start to 59
        for min in range(min_start, 60):
            download_one_file(y, month, d, h_start, min, gz_file_path, xml_file_path)

        # middle hour: min from 0 to 59
        for h in range(h_start+1, h_end):
            for min in range(60):
                download_one_file(y, month, d, h, min, gz_file_path, xml_file_path)

        # the last hour: min from 0 to min_end
        for min in range(min_end+1):
            download_one_file(y, month, d, h_end, min, gz_file_path, xml_file_path)


if __name__ == "__main__":

    # set the timeline we would like to study
    [year, month, day] = [2024, 6, 20]
    [hour_start, min_start] = [6, 0]
    [hour_end, min_end] = [10, 0]

    # set the gz and xml path
    gz_file_path = \
        "C:/Users/jaspe/Desktop/課程/資料分析/data_analysis_module3/xml_gz/"
    xml_file_path = \
        "C:/Users/jaspe/Desktop/課程/資料分析/data_analysis_module3/xml/"

    for_loop(year, month, day, hour_start, min_start, hour_end, min_end, \
            gz_file_path, xml_file_path)