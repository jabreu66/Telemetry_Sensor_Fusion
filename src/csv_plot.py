import pandas as pd
import matplotlib.pyplot as plt

truth = pd.read_csv("logs.csv")
est = pd.read_csv("estimate.csv")
gps = pd.read_csv("gps.csv")
vel = pd.read_csv("vel.csv")

true_time = truth["t_s"]
true_x = truth["x_m"]
vx_truth = truth["vx_mps"]
ax_truth = truth["a_x"]