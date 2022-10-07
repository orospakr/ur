bin_PROGRAMS = ur
ur_SOURCES = ur.cpp audio/ur_audio.cpp game/ur_map.cpp game/ur_object.cpp ui/ur_menu.cpp ui/ur_titlescreen.cpp graphics/ur_font.cpp graphics/ur_layer.cpp graphics/ur_sprite.cpp

ur_LDADD = $(AM_LDFLAGS)
ur_CPPFLAGS = $(AM_CXXFLAGS)

# now include all the headers in those subdirectories
ur_CPPFLAGS += -I$(srcdir)/audio -I$(srcdir)/game -I$(srcdir)/ui -I$(srcdir)/graphics
