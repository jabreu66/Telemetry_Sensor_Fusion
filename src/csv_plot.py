import pandas as pd
import matplotlib.pyplot as plt

truth = pd.read_csv("build/logs.csv", header = None)
# print(truth.columns)
est = pd.read_csv("build/estimate.csv", header = None)
gps = pd.read_csv("build/gps.csv", header = None)
vel = pd.read_csv("build/vel.csv", header = None)

truth.columns = ["t_s", "x_m", "y_m", "z_m", "vx_mps", "vy_mps", "vz_mps"]
est.columns = ["x", "vx", "ax"]
gps.columns = ["t_s", "x", "y", "z"]
vel.columns = ["t_s", "vx", "vy", "vz"]

true_time = truth["t_s"]
true_x = truth["x_m"]
true_vx = truth["vx_mps"]
# true_ax = truth["a_x"]

# t_est = est["t_s"] if "t_s" in est.columns else est["time"]
x_est = est["x"]
vx_est = est["vx"]
ax_est = est["ax"]

t_gps = gps["time"] if "time" in gps.columns else gps["t_s"]
x_gps = gps["x"]

t_vel = vel["time"] if "time" in vel.columns else vel["t_s"]
vx_meas = vel["vx"]

plt.figure()
plt.plot(true_time, true_x, label = "true_x")
plt.plot(true_time, x_est, label = "estiamted x")
plt.scatter(t_gps, x_gps, label = "gps x", s = 12)
plt.xlabel("time (s)")
plt.ylabel("position x (m)")
plt.legend()
plt.title("Position")

plt.figure()
plt.plot(true_time, true_vx, label = "true velocity(x)")
plt.plot(true_time, vx_est, label = "estimated vx")
plt.scatter(t_vel, vx_meas, label = "measured velocity vx", s = 12)
plt.xlabel("time (s)")
plt.ylabel("velocity vx (m/s)")
plt.legend()
plt.title("Velocity")

plt.figure()
plt.plot(true_time, ax_est, label = "true ax") # Make sure to change this to true_ax 
# plt.plot(ax_est, label = "estimated ax")
plt.xlabel("time (s)")
plt.ylabel("acceleration ax (m/s^2)")
plt.legend()
plt.title("Acceleration")

plt.show()