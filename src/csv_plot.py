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

t_est = est["t_s"] if "t_s" in est.columns else est["time"]
x_est = est["x"]
vx_est = est["vx"]
ax_est = est["ax"]

t_gps = gps["time"] if "time" in gps.columns else gps["t_s"]
x_gps = gps["x"]

t_vel = vel["time"] if "time" in vel.columns else vel["t_s"]
vx_meas = vel["vx"]

plt.figure()
plt.plot(true_time, true_x, label = "true_x")
plt.plot(t_est, x_est, label = "estiamted x")
plt.scatter(t_gps, x_gps, label = "gps x", s = 12)
plt.xlabel("time (s)")
plt.ylabel("position x (m)")
plt.legend()
plt.title("Position")