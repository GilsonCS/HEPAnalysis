path = 'Datasets/Files/'

# ID digits:
# 1st-2nd = 16(2016),17(2017),18(2018)                      # Year
# 3th-4th = 00(Data),01(MC-signal),02-13(MC-bkg)            # Type
# 5th-6th = 00(none),...                                    # Bkg -> Exclusive interval 
# 5th-6th = 00(none),11(250_30),12(250_40),55(1250_100)     # Signal -> Phisical process
# 5th-6th = 00(none),01(A),02(B),03(C)                      # Data -> Era

Bkg_16 = [
["TTTo2L2Nu_16"]          + ['160200', path+"files_TTTo2L2Nu_xrootd.txt", 98],
["DYJetsToMuMU_16"]       + ['160300', path+"files_DYJetsToMuMu_xrootd.txt", 94],
]

