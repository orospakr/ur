# libmodplug Makefile.  Builds libmodplug into an .a file

CPP  = g++
CC   = gcc
ARCHIVE = ar
OBJ  = fastmix.o load_669.o load_amf.o load_ams.o load_dbm.o load_dmf.o load_dsm.o load_far.o load_it.o load_j2b.o load_mdl.o load_med.o load_mod.o load_mt2.o load_mtm.o load_okt.o load_psm.o load_ptm.o load_s3m.o load_stm.o load_ult.o load_umx.o load_wav.o load_xm.o mmcmp.o modplug.o snd_dsp.o sndfile.o snd_flt.o snd_fx.o sndmix.o tables.o
LIBS =  
INCS =  
BIN  = libmodplug
CXXFLAGS = $(INCS) -g -Wall -Wno-deprecated

.PHONY: all all-before all-after clean clean-custom

all: all-before libmodplug all-after


clean: clean-custom
	rm -f $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(ARCHIVE) rvs "libmodplug.a"  $(OBJ) 

ur.o: ur.cpp
	$(CPP) -c ur.cpp -o ur.o $(CXXFLAGS)

fastmix.o: fastmix.cpp
	$(CPP) -c fastmix.cpp -o fastmix.o $(CXXFLAGS)

load_669.o: load_669.cpp
	$(CPP) -c load_669.cpp -o load_669.o $(CXXFLAGS)

load_amf.o: load_amf.cpp
	$(CPP) -c load_amf.cpp -o load_amf.o $(CXXFLAGS)

load_ams.o: load_ams.cpp
	$(CPP) -c load_ams.cpp -o load_ams.o $(CXXFLAGS)

load_dbm.o: load_dbm.cpp
	$(CPP) -c load_dbm.cpp -o load_dbm.o $(CXXFLAGS)

load_dmf.o: load_dmf.cpp
	$(CPP) -c load_dmf.cpp -o load_dmf.o $(CXXFLAGS)

load_dsm.o: load_dsm.cpp
	$(CPP) -c load_dsm.cpp -o load_dsm.o $(CXXFLAGS)

load_far: load_far.cpp
	$(CPP) -c load_far.cpp -o load_far.o $(CXXFLAGS)

load_it.o: load_it.cpp
	$(CPP) -c load_it.cpp -o load_it.o $(CXXFLAGS)

load_j2b.o: load_j2b.cpp
	$(CPP) -c load_j2b.cpp -o load_j2b.o $(CXXFLAGS)

load_mdl.o: load_mdl.cpp
	$(CPP) -c load_mdl.cpp -o load_mdl.o $(CXXFLAGS)

load_med.o: load_med.cpp
	$(CPP) -c load_med.cpp -o load_med.o $(CXXFLAGS)

load_mod.o: load_mod.cpp
	$(CPP) -c load_mod.cpp -o load_mod.o $(CXXFLAGS)

load_mt2.o: load_mt2.cpp
	$(CPP) -c load_mt2.cpp -o load_mt2.o $(CXXFLAGS)

load_mtm.o: load_mtm.cpp
	$(CPP) -c load_mtm.cpp -o load_mtm.o $(CXXFLAGS)

load_okt.o: load_okt.cpp
	$(CPP) -c load_okt.cpp -o load_okt.o $(CXXFLAGS)

load_psm.o: load_psm.cpp
	$(CPP) -c load_psm.cpp -o load_psm.o $(CXXFLAGS)

load_ptm.o: load_ptm.cpp
	$(CPP) -c load_ptm.cpp -o load_ptm.o $(CXXFLAGS)

load_s3m.o: load_s3m.cpp
	$(CPP) -c load_s3m.cpp -o load_s3m.o $(CXXFLAGS)

load_stm.o: load_stm.cpp
	$(CPP) -c load_stm.cpp -o load_stm.o $(CXXFLAGS)

load_ult.o: load_ult.cpp
	$(CPP) -c load_ult.cpp -o load_ult.o $(CXXFLAGS)

load_umx.o: load_umx.cpp
	$(CPP) -c load_umx.cpp -o load_umx.o $(CXXFLAGS)

load_wav.o: load_wav.cpp
	$(CPP) -c load_wav.cpp -o load_wav.o $(CXXFLAGS)

load_xm.o: load_xm.cpp
	$(CPP) -c load_xm.cpp -o load_xm.o $(CXXFLAGS)

mmcmp.o: mmcmp.cpp
	$(CPP) -c mmcmp.cpp -o mmcmp.o $(CXXFLAGS)

modplug.o: modplug.cpp
	$(CPP) -c modplug.cpp -o modplug.o $(CXXFLAGS)

snd_dsp.o: snd_dsp.cpp
	$(CPP) -c snd_dsp.cpp -o snd_dsp.o $(CXXFLAGS)

sndfile.o: sndfile.cpp
	$(CPP) -c sndfile.cpp -o sndfile.o $(CXXFLAGS)

snd_flt.o: snd_flt.cpp
	$(CPP) -c snd_flt.cpp -o snd_flt.o $(CXXFLAGS)

snd_fx.o: snd_fx.cpp
	$(CPP) -c snd_fx.cpp -o snd_fx.o $(CXXFLAGS)

sndmix.o: sndmix.cpp
	$(CPP) -c sndmix.cpp -o sndmix.o $(CXXFLAGS)

tables.o: tables.cpp
	$(CPP) -c tables.cpp -o tables.o $(CXXFLAGS)
