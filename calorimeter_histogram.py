#!/usr/bin/env python
"""This Python script displays histogram as saved in 4c in CSV format.

How to run it:
  - python calorimeter_histogram.py
  - python calorimeter_histogram.py name_of_a_file.csv

If your data is written into task4_h1_eDep.csv, your don't have to
specify the file name as argument.
"""

import numpy as np
import matplotlib.pyplot as plt
import codecs
import numpy as np
import sys
import os


def load_csv(path):
    """Loads a histogram as output from Geant4 analysis tools in CSV format.

    Parameters
    ----------
    path: str
        Path to the CSV file
    """
    meta = {}
    data = []
    with codecs.open(path, encoding="ASCII") as in_file:
        for line in in_file:
            if line.startswith("#"):
                key, value = line[1:].strip().split(" ", 1)
                meta[key] = value   # TODO: There are duplicit entries :-()
            else:
                try:
                    data.append([float(frag) for frag in line.split(",")])
                except:
                    pass
    data = np.asarray(data)
    return data, meta

def plot_histogram(path):
    try:
        import seaborn as sns
    except:
        pass
    if not os.path.isfile(path):
        print("File {0} does not exist. Make sure you created it.".format(path))
        return
    data, meta = load_csv(path)
    fig, ax = plt.subplots()
    if data[1,0] > 0:
        data[:,1] /= (data[1,0] * 1000.0)
    nbin, minbin, maxbin = (int(z) for z in meta["axis"].split(" ")[1:])
    x = np.linspace(minbin, maxbin, nbin + 1)
    print(x)
    bin_width = (maxbin - minbin) / (nbin * 1.0)
    ax.bar(x[:-1], data[1:-1,1], bin_width, color=["red", "green"] * 10)
    ax.bar([-100], [10], color="red", label="absorber")
    ax.bar([-100], [10], color="green", label="scintillator")
    ax.set_xlim(minbin, maxbin)
    ax.legend()
    ax.set_title(meta["title"])
    ax.set_xlabel("x [cm]")
    ax.set_ylabel("deposited energy [MeV]")
    plt.show()
    fig.savefig("histogram.png")
    print("Histogram has been saved to histogram.png")

if __name__ == "__main__":
    if len(sys.argv) == 2:
        path = sys.argv[1]
    else:
        path = "task4_h1_eDep.csv"
        plot_histogram(path)
