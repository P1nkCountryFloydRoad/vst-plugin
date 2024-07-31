from scipy.signal import butter

# 设计带通滤波器，假设采样频率为 1000 Hz，带通频率为 100 Hz 到 300 Hz
b, a = butter(N=1, Wn=[100, 880], btype='band', fs=44100)
print("b coefficients: ", b)
print("a coefficients: ", a)
