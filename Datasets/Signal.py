path = 'Datasets/Files/'

# ID digits:
# 1st-2nd = 16(2016),17(2017),18(2018)                      # Year
# 3th-4th = 00(Data),01(MC-signal),02-13(MC-bkg)            # Type
# 5th-6th = 00(none),...                                    # Bkg -> Exclusive interval 
# 5th-6th = 00(none),11(250_30),12(250_40),55(1250_100)     # Signal -> Phisical process
# 5th-6th = 00(none),01(A),02(B),03(C)                      # Data -> Era

Signal_16 = [
["Signal_600_150_45_16"]          + ['160111', path+"files_MH600_Ma150_MChi45.txt", 400],
]

