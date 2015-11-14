############### 
# Directories # 
############### 
# Binary Output Directory 
BIN 			=	./bin
 
# Documentation Files/Directory 
DOC 			=	./doc
 
# Source Directory 
SRC 			=	./src
 
######### 
# Other # 
######### 
 
# Source Files 
SOURCES			=	$(SRC)/Pixel.cc $(SRC)/Image.cc 
 
# Zip File Name 
ZIP 			=	project2 
 
# Other Files to add to zip 
ZIP_FILES 		=	./Makefile ./README.md 
 
 
################ 
# Make Modules # 
################ 
 
all: _bin_directory_ s p

_bin_directory_:
	@rm -r -v $(BIN)
	@mkdir -v $(BIN)

sequencial: s
s:
	g++ -o $(BIN)/sequencial $(SOURCES) $(SRC)/sequencial.cc

parallel: p
p:
	mpiCC -o $(BIN)/parallel $(SOURCES) $(SRC)/parallel.cc -fopenmp

runsequencial: rs
rs:
	$(BIN)/sequencial ./doc/inputs/lena_color.ppm ./doc/outputs/lena_color_s.ppm

runparallel: rp
rp:
	mpirun $(BIN)/parallel ./doc/inputs/lena_color.ppm ./doc/outputs/lena_color_p.ppm 2 2 -np 4

zip:
	@zip -r $(ZIP) $(LIB) $(SRC) $(DOC) $(ZIP_FILES)

clear:
	@touch $(ZIP).zip
	@rm -r $(ZIP).zip
	@touch $(BIN) $(OBJ)
	@rm -r $(BIN) $(OBJ) -v
	@touch .dummy~
	@find ./ -name *~ | xargs rm -v
