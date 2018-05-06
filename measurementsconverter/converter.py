def parseLines(line):
    parts = line.split(" ")
    print("packet: ", parts[2])
    print("cpu: ", parts[4])
    print("LPM: ", parts[6])
    print("IRQ: ", parts[8])
    print("transmit: ", parts[10])
    print("listen: ", parts[12])
    return parts[2] + "," + parts[4] + "," + parts[6] + "," + parts[8] + "," + parts[10] + "," + parts[12]


f = open('../datalogging/converted2_4-5.csv','w')
f.write("packet, cpu, lpm, IRQ, transmit, listen\n")
with open('../datalogging/energest5-2_4.txt') as run:
    for line in run:
        print(line)
        f.write(parseLines(line))
        f.write('\n')
f.close()




