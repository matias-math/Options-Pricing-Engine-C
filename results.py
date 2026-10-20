import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm

try:
    df = pd.read_csv("data.csv", skiprows=1,
                     names=['Volatility', 'Strike', 'Price', 'StdError'])
except FileNotFoundError:
    print("Error: 'research_results.csv' not found. Ensure it is in the same folder.")
    exit()

Z_price = df.pivot_table(index='Volatility', columns='Strike', values='Price')
Z_error = df.pivot_table(index='Volatility', columns='Strike', values='StdError')

X, Y = np.meshgrid(Z_price.columns, Z_price.index)

fig = plt.figure(figsize=(16, 7))

ax1 = fig.add_subplot(121, projection='3d')
surf1 = ax1.plot_surface(X, Y, Z_price.values, cmap=cm.viridis, edgecolor='k', linewidth=0.1)
ax1.set_title('Asian Option Pricing Surface (Control Variates)', pad=20, fontsize=12, fontweight='bold')
ax1.set_xlabel('Strike Price (K)', labelpad=10)
ax1.set_ylabel('Volatility (σ)', labelpad=10)
ax1.set_zlabel('Option Price', labelpad=10)
ax1.view_init(elev=25, azim=-135) 
fig.colorbar(surf1, ax=ax1, shrink=0.4, aspect=10, pad=0.1) # Fix applied here

ax2 = fig.add_subplot(122, projection='3d')
surf2 = ax2.plot_surface(X, Y, Z_error.values, cmap=cm.plasma, edgecolor='k', linewidth=0.1)
ax2.set_title('Model Uncertainty (Standard Error Surface)', pad=20, fontsize=12, fontweight='bold')
ax2.set_xlabel('Strike Price (K)', labelpad=10)
ax2.set_ylabel('Volatility (σ)', labelpad=10)
ax2.set_zlabel('Standard Error', labelpad=10)
ax2.view_init(elev=25, azim=-135)
fig.colorbar(surf2, ax=ax2, shrink=0.4, aspect=10, pad=0.1) # Fix applied here

plt.tight_layout()
plt.show()