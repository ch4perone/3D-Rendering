import numpy as np
import matplotlib
import matplotlib.pyplot as plt

# data to plot
n_groups = 4
means_frank = (1.19673,  1.22234, 1.88018, 2.61831)
means_guido = (0.999303, 1.21171, 266.508, 1331.44)

# create plot
fig, ax = plt.subplots()
index = np.arange(n_groups)
bar_width = 0.35
opacity = 0.8

rects1 = plt.bar(index, means_frank, bar_width,
alpha=opacity,
color='gold',
label='Grid Acceleration')

rects2 = plt.bar(index + bar_width, means_guido, bar_width,
alpha=opacity,
color='teal',
label='Naive Ray Tracer')

plt.xlabel('Scenes')
plt.ylabel('Runtime (s)')
plt.title('Runtime comparison')
plt.xticks(index + bar_width, ('balls (low)', 'mount (low)', 'balls (high)', 'mount (very high)'))
plt.yscale('symlog')
ax.get_yaxis().set_major_formatter(
matplotlib.ticker.FuncFormatter(lambda x, p: format(int(x), ',')))
#plt.ticklabel_format(axis='y', style='plain', scilimits=(0, 4))
plt.legend()

plt.tight_layout()
plt.show()
