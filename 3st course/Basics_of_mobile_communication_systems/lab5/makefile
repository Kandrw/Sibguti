

# SRC = item1.c item2.c
# FLG = -lm
# #PROGRAM = item1
# .PHONY: $(SRC)
# all: $(SRC)
# $(SRC):
# #	gcc -o $(PROGRAM) -lm $^
# 	gcc -o $(basename $@) $(FLG)  $@
# %.o: %.c
# 	gcc $< -c -o $@


.PHONY: all
all: item1 item4 item5

item1:
	gcc -DN=29 -o item1 -lm item1.c
item4:
	gcc -DN=259 -o item4 -lm item1.c
item5:
	gcc -DN=250 -o item5 -lm item5.c
	gcc -DN=2500 -o item2500 -lm item5.c
	gcc -DN=20 -DOUT_CRC -DDEBUG -o item20 -lm item5.c
	

	



