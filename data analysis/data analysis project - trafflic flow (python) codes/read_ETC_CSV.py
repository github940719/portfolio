import os
import pandas as pd
import csv
import requests
import tarfile  # to download tar.gz file


year = 2024
month = 6
day = 20
hour = [6, 7, 8, 9]

# download the tar.gz file
url = f"https://tisvcloud.freeway.gov.tw/history/TDCS/M03A/M03A_{year}{month:02}{day:02}.tar.gz"
response = requests.get(url)

# set the folder of tar.gz
folder_name = "C:/Users/jaspe/Desktop/課程/資料分析/data_analysis_module3/"
if not os.path.exists(folder_name):
    os.makedirs(folder_name)  # make the directory

# set the file name of tar.gz
tar_gz_file_name = f"ETC_{year}{month:02}{day:02}.tar.gz"

# download
with open(os.path.join(folder_name, tar_gz_file_name), "wb") as file:
    file.write(response.content)

# extract the tar.gz into csv., located in the same folder as tar.gz
with tarfile.open(os.path.join(folder_name, tar_gz_file_name), "r:gz") as file:
    file.extractall(path = folder_name)

# read the csv files in the tar.gz
output_csv_name = "ETC_output.csv"
with open(os.path.join(folder_name, output_csv_name), mode = "w", newline = "", encoding = "utf-8") as output:
    writer = csv.writer(output)

    # write the title in the output.csv
    writer.writerow(["年", "月", "日", "時", "分", "ETC", "小客車", "小貨車", "大客車", "大貨車", "聯結車"])

    for h in hour:

        # in M03A (extracted folder), there are many folders
        # we choose the targeted hour folder
        outer_folder_name = f"M03A/{year}{month:02}{day:02}/{h:02}/"
        for min in range(0, 60, 5):
            file_name = f"TDCS_M03A_{year}{month:02}{day:02}_{h:02}{min:02}00.csv"
            df = pd.read_csv(os.path.join(folder_name, outer_folder_name, file_name), header = None, names = ["時間", "ETC編號", "方向", "車種", "流量"])
            
            # cleaning
            df = df[df["ETC編號"] == "01F0467N"]
            df["時間"] = pd.to_datetime(df["時間"], format="%Y-%m-%d %H:%M")
            writer.writerow([df["時間"].iloc[0].year, \
                            df["時間"].iloc[0].month, \
                            df["時間"].iloc[0].day, \
                            df["時間"].iloc[0].hour, \
                            df["時間"].iloc[0].minute, \
                            "01F0467N", df["流量"].iloc[0], \
                            df["流量"].iloc[1], df["流量"].iloc[2], \
                            df["流量"].iloc[3], df["流量"].iloc[4]])