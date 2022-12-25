import os

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from matplotlib import colors
from matplotlib.ticker import PercentFormatter
import re
from termcolor import colored
from pyfiglet import Figlet
from rich.console import Console
from rich.table import Table


console = Console()
def to_table(pandas_dataframe, rtbl):

    rtbl.add_column("Sno.", style="blue")
    for column in pandas_dataframe.columns:
        rtbl.add_column(str(column))

    for index, value_list in enumerate(pandas_dataframe.values.tolist()):
        row = [str(index)]
        row += [str(x) for x in value_list]
        rtbl.add_row(*row)

    return rtbl

def compile_and_run_cpp():

    # compile the cpp file
    os.system("g++ ./First_Come_First_Service.cpp -std=c++20 -o ./bin/main1 -std=c++20")
    print("[*] Compilation Successful, Executing ./bin/main1 \n")
    # run the binary file
    os.system("./bin/main1 ")
    os.system("g++ ./multi_level_feedback_queue.cpp -o ./bin/main2 -std=c++20")
    print("[*] Compilation Successful, Executing ./bin/main2 \n")
    # run the binary file
    os.system("./bin/main2 ")
    os.system("g++ ./multi_level_queue.cpp -o ./bin/main3 -std=c++20")
    print("[*] Compilation Successful, Executing ./bin/main3 \n")
    # run the binary file
    os.system("./bin/main3 ")
    os.system("g++ ./Priority_Preemtive_Schedule.cpp -o ./bin/main4 -std=c++20")
    print("[*] Compilation Successful, Executing ./bin/main4 \n")
    # run the binary file
    os.system("./bin/main4 ")
    os.system("g++ ./Priority_schedule.cpp -o ./bin/main5 -std=c++20")
    print("[*] Compilation Successful, Executing ./bin/main5 \n")
    # run the binary file
    os.system("./bin/main5 ")
   
    os.system("g++ ./Round_Robin.cpp -o ./bin/main6 -std=c++20")
    print("[*] Compilation Successful, Executing ./bin/main6 \n")
    # run the binary file
    os.system("./bin/main6 ./Input/inp6.txt")

    os.system("g++ ./Shortest_Job_First_Preemtive.cpp -o ./bin/main7 -std=c++20")
    print("[*] Compilation Successful, Executing ./bin/main7 \n")
    # run the binary file
    os.system("./bin/main7 ")

    os.system("g++ ./Shortest_Job_First.cpp -o ./bin/main8 -std=c++20")
    print("[*] Compilation Successful, Executing ./bin/main8 \n")
    # run the binary file
    os.system("./bin/main8 ")


def get_avg_times_of_all_algo(avg_wt,avg_tat,avg_rt,out1,out2,out3,out4,out5,out6,out7,out8) :
    
    for i in range(1,9):
        
        op_dir = "./output/out"
       
        # open output file(rgb_out.txt)
        op_fp = open(op_dir + str(i)+".txt", "r")

        # read the dimension of the image from the file
        x = 0
        lines = op_fp.readlines()
        for j in lines:
            if x == 0:
                y = j[8:]
                avg_tat.append(float(y))
            elif x == 1:
                y = j[8:]
                avg_wt.append(float(y))
            elif x == 2:
                y = j[8:]
                avg_rt.append(float(y)) 
            elif(i == 1):
                out1.append(j)
            elif(i == 2):
                out2.append(j)
            elif(i == 3):
                out3.append(j)
            elif(i == 4):
                out4.append(j)
            elif(i == 5):
                out5.append(j)
            elif(i == 6):
                out6.append(j)
            elif(i == 7):
                out7.append(j)
            elif(i == 8):
                out8.append(j)
            
                

            x+=1
        # close the output file
        op_fp.close()

def get_table(out, table_name):
    df = pd.DataFrame(out)
    table = Table(title=table_name, show_header=True,
                      header_style="bold magenta", row_styles=["none", "dim"])
    table = to_table(df, table)
    console.print(table)
avg_wt = []
avg_tat = []
avg_rt = []
out1,out2,out3,out4,out5,out6,out7,out8 = [],[],[],[],[],[],[],[]

compile_and_run_cpp()
get_avg_times_of_all_algo(avg_wt,avg_tat,avg_rt,out1,out2,out3,out4,out5,out6,out7,out8)

def get_rr(x,y,z):
   


    for j in  range(1,5):
        os.system("g++ ./Round_Robin.cpp -o main6 -std=c++20")
        # run the binary file
        path = "./Input/" +str(j*2) + ".txt"
       
        os.system("./main6 " + path)
        op_fp = open("./output/out6"+".txt", "r")
        lines = op_fp.readlines()
        for i in range(3):
            if i == 0:
                x.append(float(lines[i][8:]))
            if i == 1:
                y.append(float(lines[i][8:]))
            if i == 2:
                z.append(float(lines[i][8:]))
        op_fp.close()


print("Press 1 for FCFS table:")
print("Press 2 for MLFQ table:")
print("Press 3 for MLQ table:")
print("Press 4 for PR_prem table:")
print("Press 5 for PR table:")
print("Press 6 for RR table:")
print("Press 7 for SJF_prem table:")
print("Press 8 for SJF table:")
print("Press 9 for Analytic Graph:")
print("Press 0 for EXIT:")
n = 1
while(n):
    n = int(input("Give input Here: "))
    if(n == 0):
        continue
    elif(n == 1):
        get_table(out1,'FCFS')
    elif(n == 2):
        get_table(out2,'MLFQ')
    elif(n == 3):
        get_table(out3,'MLQ')
    elif(n == 4):
        get_table(out4,'PR_preem')
    elif(n == 5):
        get_table(out5,'PR')
    elif(n == 6):
        get_table(out6, 'RR')
    elif(n == 7):
        get_table(out7,'SJF_preem')
    elif(n == 8):
        get_table(out8, 'SJF')
    elif(n == 9):
        x = ['FCFS', 'MLFQ', 'MLQ', 'Pr_preem', 'Pr','RR','SJF_preem','SJF']
        

        plot1 = plt.subplot2grid((3, 3), (0, 0), colspan=3)
        plot2 = plt.subplot2grid((3, 3), (1, 0) , colspan=3)
        plot3 = plt.subplot2grid((3,3), (2, 0) , colspan=3)



        plot1.plot(x, avg_wt, color='green', linestyle='dashed', linewidth = 1,
                marker='o', markerfacecolor='blue', markersize=12)


        # plotting a bar chart
        plot1.bar(x, avg_wt,
                width = 0.4, color = ['red', 'green','blue','yellow','black','lime','pink'])


        # naming the y axis
        plot1.set_ylabel('Average Waiting Time')


        plot2.plot(x, avg_tat, color='green', linestyle='dashed', linewidth = 1,
                marker='o', markerfacecolor='blue', markersize=12)


        
        # plotting a bar chart
        plot2.bar(x, avg_tat,
                width = 0.4, color = ['red', 'green','blue','yellow','black','lime','pink'])


        # naming the y axis
        plot2.set_ylabel('Average TAT Time')


        plot3.plot(x, avg_rt, color='green', linestyle='dashed', linewidth = 1,
                marker='o', markerfacecolor='blue', markersize=12)

        # labels for bars
        tick_label = ['FCFS', 'MLFQ', 'MLQ', 'PR_prem', 'PR','RR','SJF_prem','SJF']
        
        # plotting a bar chart
        plot3.bar(x, avg_rt, tick_label = tick_label,
                width = 0.4, color = ['red', 'green','blue','yellow','black','lime','pink'])

        # naming the x axis
        plot3.set_xlabel('Scheduling Algorithms')
        # naming the y axis
        plot3.set_ylabel('Average RT Time')
        plt.show()
    if n == 10:
        Avg_rr_wt,Avg_rr_tat,Avg_rr_rt = [],[],[]
        get_rr(Avg_rr_tat,Avg_rr_wt,Avg_rr_rt)
        x = ['RR1', 'RR2', 'RR3', 'RR4']
        

        plot1 = plt.subplot2grid((3, 3), (0, 0), colspan=3)
        plot2 = plt.subplot2grid((3, 3), (1, 0) , colspan=3)
        plot3 = plt.subplot2grid((3,3), (2, 0) , colspan=3)



        # plot1.plot(x, avg_wt, color='green', linestyle='dashed', linewidth = 1,
        #         marker='o', markerfacecolor='blue', markersize=12)


        # plotting a bar chart
        plot1.bar(x, Avg_rr_wt,
                width = 0.4, color = [ 'green','blue','yellow','black','lime','pink'])


        # naming the y axis
        plot1.set_ylabel('Average Waiting Time')


        # plot2.plot(x, avg_tat, color='green', linestyle='dashed', linewidth = 1,
        #         marker='o', markerfacecolor='blue', markersize=12)


        
        # plotting a bar chart
        plot2.bar(x, Avg_rr_tat,
                width = 0.4, color = ['green','blue','yellow','black'])


        # naming the y axis
        plot2.set_ylabel('Average TAT Time')


        # plot3.plot(x, avg_rt, color='green', linestyle='dashed', linewidth = 1,
        #         marker='o', markerfacecolor='blue', markersize=12)

        # # labels for bars
        # tick_label = ['FCFS', 'MLFQ', 'MLQ', 'PR_prem', 'PR','RR','SJF_prem','SJF']
        
        # plotting a bar chart
        plot3.bar(x, Avg_rr_rt, 
                width = 0.4, color = ['green','blue','yellow','black'])

        # naming the x axis
        plot3.set_xlabel('Scheduling Algorithms')
        # naming the y axis
        plot3.set_ylabel('Average RT Time')
        plt.show()





