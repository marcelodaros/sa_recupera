import binascii


f1 = open("LUC_0260.MOV", "rb")
f2 = open("LUC_0261.MOV", "rb")
f3 = open("TDVF_Teaser_Audio_ProRes_V3.mov", "rb")

head = f1.read(12)
head2 = f2.read(12)
head3 = f3.read(12)

print(binascii.hexlify(head[1]))
print(binascii.hexlify(head2))
print(binascii.hexlify(head3))

