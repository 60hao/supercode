import matplotlib.pyplot as plt
import numpy as np

x = [8, 16,32, 64, 128, 256, 512, 1024, 2048]
gflops_naive  = [0.256, 0.356, 0.352, 0.237, 0.34, 0.853, 0.559, 0.58,0.554]
gflops_pthread = [0.00088, 0.024, 0.054, 0.712, 1.25, 2.938, 4.7, 4.44,1.065]
gflops_openmp = [0.00077, 0.0156, 0.154, 0.826, 2.26, 2.07,0.45, 0.41, 0.36]
gflops_cblas  = [0.00004, 2.73, 10.92, 23.83, 0.595, 156.8, 9.81, 67.8,162.4]

# 设置图表的大小和字体
plt.rcParams.update({'font.size': 20})
fig, ax = plt.subplots(figsize=(20, 10))

# 绘制各个方法的性能曲线
plt.plot(x, gflops_naive, label='naive', color='purple', linestyle='-', linewidth=1.0)
plt.plot(x, gflops_cblas, label='cblas', color='brown', linestyle='-.', linewidth=5.0)
plt.plot(x, gflops_openmp, label='openmp', color='blue', linestyle=':', linewidth=1.0)
plt.plot(x, gflops_pthread, label='pthread', color='red', linestyle='--', linewidth=1.0)

# 设置标题和坐标轴标签
plt.title('Performance')
plt.xlabel('Matrix Size')
plt.ylabel('Gflops')

# 显示图例
plt.legend()

# 保存图像到文件
plt.savefig('output_image.png')  # 这里会将图像保存为 output_image.png 文件
