import pandas as pd
import matplotlib.pyplot as plt
import scipy.stats as stats
import numpy as np

def plot(vd_id):
    df = pd.read_csv("VD_output.csv")

    # filter the targeted vd
    df = df[df["偵測器編號"] == vd_id].copy()

    colors = ["red", "blue", "green", "orange", "purple"]
    for lane in range(3):

        # filtered velosity = -99 (error) or 0 (to avoid ln(0) -> undefined)
        df = df[(df["車道 " + str(lane) + " S 速率"] != -99) & (df["車道 " + str(lane) + " S 速率"] != 0)].copy()
        
        # calculate the flow rate and density
        df["車道 " + str(lane) + " S 流率"] = df["車道 " + str(lane) + " S 流量"] * 60
        df["車道 " + str(lane) + " S 密度"] = df["車道 " + str(lane) + " S 流率"] / df["車道 " + str(lane) + " S 速率"]

        # scatter plot of velocity and flow rate
        plt.scatter(df["車道 " + str(lane) + " S 速率"], \
                    df["車道 " + str(lane) + " S 流率"], \
                    color = colors[lane], \
                    label = f"Lane {lane}", \
                    s = 8)
        
    
    plt.title("Flow Rate vs Velocity for Different Lanes")
    plt.xlabel("Velocity (km/h)")
    plt.ylabel("Flow Rate (veh/hour)")
    plt.legend(title = "Lane")
    plt.show()


if __name__ == "__main__":
    vd_id = "VD-N1-N-45.520-M-LOOP"
    plot(vd_id)