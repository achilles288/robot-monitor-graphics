prefix ?= /usr/local

VERSION = 1.0.0
VERSION_MAJOR = 1

CC = g++
FLAGS = -std=c++14 -O2 -Wno-unused-result -Wno-unused-function -Wno-unused-label \
	-Wno-unused-value -Wno-unused-variable

MACROS = \
	-DNDEBUG \
	-D_GNU_SOURCE \
	-D_POSIX_C_SOURCE=200112L \
	-D_XOPEN_SOURCE=600 \
	-DRMG_RESOURCE_PATH="\"$(prefix)/share/rmg\""

INCLUDES = \
	-Isrc/base \
	-Isrc/config \
	-Isrc/window \
	-Isrc/wx \
	`pkg-config glfw3 --cflags` \
	`pkg-config libpng --cflags` \
	`pkg-config libtiff-4 --cflags` \
	`wx-config --cflags base core gl --toolkit=gtk3`

LIBS = \
	-lGL \
	`pkg-config glfw3 --libs` \
	`pkg-config libpng --libs` \
	`pkg-config libtiff-4 --libs` \
	`wx-config --libs base core gl --toolkit=gtk3`

CFLAGS = $(FLAGS) $(MACROS) $(INCLUDES)
LDFLAGS = $(LIBS)


# 
# Source files
# 
RMG_BASE_SRCS = \
	src/base/bitmap.cpp \
	src/base/bitmap_png.cpp \
	src/base/bitmap_tiff.cpp \
	src/base/camera.cpp \
	src/base/color.cpp \
	src/base/context_container.cpp \
	src/base/context_renderer.cpp \
	src/base/context_world.cpp \
	src/base/cube.cpp \
	src/base/cylinder.cpp \
	src/base/font.cpp \
	src/base/keyboard.cpp \
	src/base/material.cpp \
	src/base/mesh.cpp \
	src/base/mesh_indices.cpp \
	src/base/mesh_normals.cpp \
	src/base/mouse.cpp \
	src/base/line3d.cpp \
	src/base/object.cpp \
	src/base/object2d.cpp \
	src/base/object3d.cpp \
	src/base/object3d_obj.cpp \
	src/base/particle.cpp \
	src/base/sphere.cpp \
	src/base/sprite.cpp \
	src/base/text2d.cpp \
	src/base/math/euler.cpp \
	src/base/math/mat3.cpp \
	src/base/math/mat4.cpp \
	src/base/math/ostream.cpp \
	src/base/math/vec3.cpp \
	src/base/math/vec4.cpp \
	src/base/internal/context_load.cpp \
	src/base/internal/general_shader.cpp \
	src/base/internal/glcontext.cpp \
	src/base/internal/line3d_shader.cpp \
	src/base/internal/object2d_shader.cpp \
	src/base/internal/particle_shader.cpp \
	src/base/internal/shader.cpp \
	src/base/internal/shadow_map_shader.cpp \
	src/base/internal/sprite_load.cpp \
	src/base/internal/texture_load.cpp \
	src/base/internal/vbo_load.cpp

RMG_WINDOW_SRCS = \
	src/window/window.cpp

RMG_WX_SRCS = \
	src/wx/wxcanvas.cpp

RMG_BASE_OBJS = $(patsubst src/base/%.cpp, build/%.o, $(RMG_BASE_SRCS))

RMG_WINDOW_OBJS = $(patsubst src/window/%.cpp, build/%.o, $(RMG_WINDOW_SRCS))

RMG_WX_OBJS = $(patsubst src/wx/%.cpp, build/%.o, $(RMG_WX_SRCS))




all: rmgbase rmgwindow rmgwx
	@ :

mkdir:
	@ mkdir -p build
	@ mkdir -p build/internal
	@ mkdir -p build/math


# 
# RMG base library
# 
rmgbase: mkdir $(RMG_BASE_OBJS)
	$(CC) -shared -Wl,-soname,librmgbase.so.$(VERSION_MAJOR) \
		-o librmgbase.so.$(VERSION) $(RMG_BASE_OBJS) \
		$(LDFLAGS) -shared
	@ ln -sf librmgbase.so.$(VERSION) librmgbase.so.$(VERSION_MAJOR)
	@ ln -sf librmgbase.so.$(VERSION) librmgbase.so
	@ mv librmgbase.so build
	@ mv librmgbase.so.$(VERSION) build
	@ mv librmgbase.so.$(VERSION_MAJOR) build

$(RMG_BASE_OBJS): build/%.o: src/base/%.cpp
	@ $(CC) -fPIC -c $(CFLAGS) -o $@ $<


# 
# RMG GLFW window
# 
rmgwindow: rmgbase $(RMG_WINDOW_OBJS)
	$(CC) -shared -Wl,-soname,librmgwindow.so.$(VERSION_MAJOR) \
		-o librmgwindow.so.$(VERSION) $(RMG_WINDOW_OBJS) \
		$(LDFLAGS) -L./build -lrmgbase -shared
	@ ln -sf librmgwindow.so.$(VERSION) librmgwindow.so.$(VERSION_MAJOR)
	@ ln -sf librmgwindow.so.$(VERSION) librmgwindow.so
	@ mv librmgwindow.so build
	@ mv librmgwindow.so.$(VERSION) build
	@ mv librmgwindow.so.$(VERSION_MAJOR) build

$(RMG_WINDOW_OBJS): build/%.o: src/window/%.cpp
	@ $(CC) -fPIC -c $(CFLAGS) -o $@ $<


# 
# RMG wxWidgets port
# 
rmgwx: rmgbase $(RMG_WX_OBJS)
	$(CC) -shared -Wl,-soname,librmgwx.so.$(VERSION_MAJOR) \
		-o librmgwx.so.$(VERSION) $(RMG_WX_OBJS) \
		$(LDFLAGS) -L./build -lrmgbase -shared
	@ ln -sf librmgwx.so.$(VERSION) librmgwx.so.$(VERSION_MAJOR)
	@ ln -sf librmgwx.so.$(VERSION) librmgwx.so
	@ mv librmgwx.so build
	@ mv librmgwx.so.$(VERSION) build
	@ mv librmgwx.so.$(VERSION_MAJOR) build

$(RMG_WX_OBJS): build/%.o: src/wx/%.cpp
	@ $(CC) -fPIC -c $(CFLAGS) -o $@ $<




install:
	install -Dm 644 share/icons/rmg-app.png \
		$(DESTDIR)$(prefix)/share/rmg/icons/rmg-app.png
	install -Dm 644 share/icons/flat/24/hand.png \
		$(DESTDIR)$(prefix)/share/rmg/icons/flat/24/hand.png
	install -Dm 644 share/icons/flat/24/move.png \
		$(DESTDIR)$(prefix)/share/rmg/icons/flat/24/move.png
	install -Dm 644 share/icons/flat/24/photo.png \
		$(DESTDIR)$(prefix)/share/rmg/icons/flat/24/photo.png
	install -Dm 644 share/icons/flat/24/resize.png \
		$(DESTDIR)$(prefix)/share/rmg/icons/flat/24/resize.png
	install -Dm 644 share/icons/flat/24/rotate.png \
		$(DESTDIR)$(prefix)/share/rmg/icons/flat/24/rotate.png
	install -Dm 644 share/icons/flat/24/sun.png \
		$(DESTDIR)$(prefix)/share/rmg/icons/flat/24/sun.png
	install -Dm 644 share/icons/flat/24/teapot.png \
		$(DESTDIR)$(prefix)/share/rmg/icons/flat/24/teapot.png
	install -Dm 644 share/icons/flat/svg/hand.svg \
		$(DESTDIR)$(prefix)/share/rmg/icons/flat/svg/hand.svg
	install -Dm 644 share/icons/flat/svg/move.svg \
		$(DESTDIR)$(prefix)/share/rmg/icons/flat/svg/move.svg
	install -Dm 644 share/icons/flat/svg/photo.svg \
		$(DESTDIR)$(prefix)/share/rmg/icons/flat/svg/photo.svg
	install -Dm 644 share/icons/flat/svg/resize.svg \
		$(DESTDIR)$(prefix)/share/rmg/icons/flat/svg/resize.svg
	install -Dm 644 share/icons/flat/svg/rotate.svg \
		$(DESTDIR)$(prefix)/share/rmg/icons/flat/svg/rotate.svg
	install -Dm 644 share/icons/flat/svg/sun.svg \
		$(DESTDIR)$(prefix)/share/rmg/icons/flat/svg/sun.svg
	install -Dm 644 share/icons/flat/svg/teapot.svg \
		$(DESTDIR)$(prefix)/share/rmg/icons/flat/svg/teapot.svg
	install -Dm 644 share/models/dragon.obj \
		$(DESTDIR)$(prefix)/share/rmg/models/dragon.obj
	install -Dm 644 share/models/happy_buddha.obj \
		$(DESTDIR)$(prefix)/share/rmg/models/happy_buddha.obj
	install -Dm 644 share/models/teapot.obj \
		$(DESTDIR)$(prefix)/share/rmg/models/teapot.obj
	install -Dm 644 share/shaders/general.fs.glsl \
		$(DESTDIR)$(prefix)/share/rmg/shaders/general.fs.glsl
	install -Dm 644 share/shaders/general.vs.glsl \
		$(DESTDIR)$(prefix)/share/rmg/shaders/general.vs.glsl
	install -Dm 644 share/shaders/particle.fs.glsl \
		$(DESTDIR)$(prefix)/share/rmg/shaders/particle.fs.glsl
	install -Dm 644 share/shaders/line3d.fs.glsl \
		$(DESTDIR)$(prefix)/share/rmg/shaders/line3d.fs.glsl
	install -Dm 644 share/shaders/line3d.vs.glsl \
		$(DESTDIR)$(prefix)/share/rmg/shaders/line3d.vs.glsl
	install -Dm 644 share/shaders/particle.vs.glsl \
		$(DESTDIR)$(prefix)/share/rmg/shaders/particle.vs.glsl
	install -Dm 644 share/shaders/shadow_map.fs.glsl \
		$(DESTDIR)$(prefix)/share/rmg/shaders/shadow_map.fs.glsl
	install -Dm 644 share/shaders/shadow_map.vs.glsl \
		$(DESTDIR)$(prefix)/share/rmg/shaders/shadow_map.vs.glsl
	install -Dm 644 share/shaders/sprite.fs.glsl \
		$(DESTDIR)$(prefix)/share/rmg/shaders/sprite.fs.glsl
	install -Dm 644 share/shaders/sprite.vs.glsl \
		$(DESTDIR)$(prefix)/share/rmg/shaders/sprite.vs.glsl
	install -Dm 644 share/shaders/text2d.fs.glsl \
		$(DESTDIR)$(prefix)/share/rmg/shaders/text2d.fs.glsl
	install -Dm 644 share/shaders/text2d.vs.glsl \
		$(DESTDIR)$(prefix)/share/rmg/shaders/text2d.vs.glsl
	install -Dm 644 share/test/fire.tif \
		$(DESTDIR)$(prefix)/share/rmg/test/fire.tif
	install -Dm 644 share/test/wine.png \
		$(DESTDIR)$(prefix)/share/rmg/test/wine.png
	@ :
	install -Dm 755 build/librmgbase.so.$(VERSION) \
		$(DESTDIR)$(prefix)/lib/librmgbase.so.$(VERSION)
	cp -a build/librmgbase.so \
		$(DESTDIR)$(prefix)/lib/librmgbase.so
	cp -a build/librmgbase.so.$(VERSION_MAJOR) \
		$(DESTDIR)$(prefix)/lib/librmgbase.so.$(VERSION_MAJOR)
	@ :
	install -Dm 755 build/librmgwindow.so.$(VERSION) \
		$(DESTDIR)$(prefix)/lib/librmgwindow.so.$(VERSION)
	cp -a build/librmgwindow.so \
		$(DESTDIR)$(prefix)/lib/librmgwindow.so
	cp -a build/librmgwindow.so.$(VERSION_MAJOR) \
		$(DESTDIR)$(prefix)/lib/librmgwindow.so.$(VERSION_MAJOR)
	@ :
	install -Dm 755 build/librmgwx.so.$(VERSION) \
		$(DESTDIR)$(prefix)/lib/librmgwx.so.$(VERSION)
	cp -a build/librmgwx.so \
		$(DESTDIR)$(prefix)/lib/librmgwx.so
	cp -a build/librmgwx.so.$(VERSION_MAJOR) \
		$(DESTDIR)$(prefix)/lib/librmgwx.so.$(VERSION_MAJOR)
	@ :
	install -Dm 644 rmg.pc \
		$(DESTDIR)$(prefix)/lib/pkgconfig/rmg.pc
	install -Dm 644 src/base/rmg/assert.hpp \
		$(DESTDIR)$(prefix)/include/rmg/assert.hpp
	install -Dm 644 src/base/rmg/assert.inc \
		$(DESTDIR)$(prefix)/include/rmg/assert.inc
	install -Dm 644 src/base/rmg/bitmap.hpp \
		$(DESTDIR)$(prefix)/include/rmg/bitmap.hpp
	install -Dm 644 src/base/rmg/camera.hpp \
		$(DESTDIR)$(prefix)/include/rmg/camera.hpp
	install -Dm 644 src/base/rmg/color.hpp \
		$(DESTDIR)$(prefix)/include/rmg/color.hpp
	install -Dm 644 src/base/rmg/context.hpp \
		$(DESTDIR)$(prefix)/include/rmg/context.hpp
	install -Dm 644 src/base/rmg/cube.hpp \
		$(DESTDIR)$(prefix)/include/rmg/cube.hpp
	install -Dm 644 src/base/rmg/cylinder.hpp \
		$(DESTDIR)$(prefix)/include/rmg/cylinder.hpp
	install -Dm 644 src/base/rmg/font.hpp \
		$(DESTDIR)$(prefix)/include/rmg/font.hpp
	install -Dm 644 src/base/rmg/keyboard.hpp \
		$(DESTDIR)$(prefix)/include/rmg/keyboard.hpp
	install -Dm 644 src/base/rmg/line3d.hpp \
		$(DESTDIR)$(prefix)/include/rmg/line3d.hpp
	install -Dm 644 src/base/rmg/material.hpp \
		$(DESTDIR)$(prefix)/include/rmg/material.hpp
	install -Dm 644 src/base/rmg/math.hpp \
		$(DESTDIR)$(prefix)/include/rmg/math.hpp
	install -Dm 644 src/base/rmg/mesh.hpp \
		$(DESTDIR)$(prefix)/include/rmg/mesh.hpp
	install -Dm 644 src/base/rmg/mouse.hpp \
		$(DESTDIR)$(prefix)/include/rmg/mouse.hpp
	install -Dm 644 src/base/rmg/object.hpp \
		$(DESTDIR)$(prefix)/include/rmg/object.hpp
	install -Dm 644 src/base/rmg/object2d.hpp \
		$(DESTDIR)$(prefix)/include/rmg/object2d.hpp
	install -Dm 644 src/base/rmg/object3d.hpp \
		$(DESTDIR)$(prefix)/include/rmg/object3d.hpp
	install -Dm 644 src/base/rmg/particle.hpp \
		$(DESTDIR)$(prefix)/include/rmg/particle.hpp
	install -Dm 644 src/base/rmg/rmg.hpp \
		$(DESTDIR)$(prefix)/include/rmg/rmg.hpp
	install -Dm 644 src/base/rmg/sphere.hpp \
		$(DESTDIR)$(prefix)/include/rmg/sphere.hpp
	install -Dm 644 src/base/rmg/sprite.hpp \
		$(DESTDIR)$(prefix)/include/rmg/sprite.hpp
	install -Dm 644 src/base/rmg/text2d.hpp \
		$(DESTDIR)$(prefix)/include/rmg/text2d.hpp
	install -Dm 644 src/base/rmg/alignment.hpp \
		$(DESTDIR)$(prefix)/include/rmg/alignment.hpp
	install -Dm 644 src/base/rmg/internal/context_load.hpp \
		$(DESTDIR)$(prefix)/include/rmg/internal/context_load.hpp
	install -Dm 644 src/base/rmg/internal/general_shader.hpp \
		$(DESTDIR)$(prefix)/include/rmg/internal/general_shader.hpp
	install -Dm 644 src/base/rmg/internal/glcontext.hpp \
		$(DESTDIR)$(prefix)/include/rmg/internal/glcontext.hpp
	install -Dm 644 src/base/rmg/internal/line3d_shader.hpp \
		$(DESTDIR)$(prefix)/include/rmg/internal/line3d_shader.hpp
	install -Dm 644 src/base/rmg/internal/object2d_shader.hpp \
		$(DESTDIR)$(prefix)/include/rmg/internal/object2d_shader.hpp
	install -Dm 644 src/base/rmg/internal/particle_shader.hpp \
		$(DESTDIR)$(prefix)/include/rmg/internal/particle_shader.hpp
	install -Dm 644 src/base/rmg/internal/shader.hpp \
		$(DESTDIR)$(prefix)/include/rmg/internal/shader.hpp
	install -Dm 644 src/base/rmg/internal/shadow_map_shader.hpp \
		$(DESTDIR)$(prefix)/include/rmg/internal/shadow_map_shader.hpp
	install -Dm 644 src/base/rmg/internal/sprite_load.hpp \
		$(DESTDIR)$(prefix)/include/rmg/internal/sprite_load.hpp
	install -Dm 644 src/base/rmg/internal/texture_load.hpp \
		$(DESTDIR)$(prefix)/include/rmg/internal/texture_load.hpp
	install -Dm 644 src/base/rmg/internal/vbo_load.hpp \
		$(DESTDIR)$(prefix)/include/rmg/internal/vbo_load.hpp
	install -Dm 644 src/base/rmg/math/angle_unit.hpp \
		$(DESTDIR)$(prefix)/include/rmg/math/angle_unit.hpp
	install -Dm 644 src/base/rmg/math/euler.hpp \
		$(DESTDIR)$(prefix)/include/rmg/math/euler.hpp
	install -Dm 644 src/base/rmg/math/line_equation.hpp \
		$(DESTDIR)$(prefix)/include/rmg/math/line_equation.hpp
	install -Dm 644 src/base/rmg/math/mat3.hpp \
		$(DESTDIR)$(prefix)/include/rmg/math/mat3.hpp
	install -Dm 644 src/base/rmg/math/mat3.inc \
		$(DESTDIR)$(prefix)/include/rmg/math/mat3.inc
	install -Dm 644 src/base/rmg/math/mat4.hpp \
		$(DESTDIR)$(prefix)/include/rmg/math/mat4.hpp
	install -Dm 644 src/base/rmg/math/mat4.inc \
		$(DESTDIR)$(prefix)/include/rmg/math/mat4.inc
	install -Dm 644 src/base/rmg/math/plane_equation.hpp \
		$(DESTDIR)$(prefix)/include/rmg/math/plane_equation.hpp
	install -Dm 644 src/base/rmg/math/vec.hpp \
		$(DESTDIR)$(prefix)/include/rmg/math/vec.hpp
	install -Dm 644 src/base/rmg/math/vec2.hpp \
		$(DESTDIR)$(prefix)/include/rmg/math/vec2.hpp
	install -Dm 644 src/base/rmg/math/vec2.inc \
		$(DESTDIR)$(prefix)/include/rmg/math/vec2.inc
	install -Dm 644 src/base/rmg/math/vec3.hpp \
		$(DESTDIR)$(prefix)/include/rmg/math/vec3.hpp
	install -Dm 644 src/base/rmg/math/vec3.inc \
		$(DESTDIR)$(prefix)/include/rmg/math/vec3.inc
	install -Dm 644 src/base/rmg/math/vec4.hpp \
		$(DESTDIR)$(prefix)/include/rmg/math/vec4.hpp
	install -Dm 644 src/base/rmg/math/vec4.inc \
		$(DESTDIR)$(prefix)/include/rmg/math/vec4.inc
	install -Dm 644 src/config/rmg/config.h \
		$(DESTDIR)$(prefix)/include/rmg/config.h
	install -Dm 644 src/window/rmg/window.hpp \
		$(DESTDIR)$(prefix)/include/rmg/window.hpp
	install -Dm 644 src/window/rmg/internal/window_callback.hpp \
		$(DESTDIR)$(prefix)/include/rmg/internal/window_callback.hpp
	install -Dm 644 src/wx/rmg/wxcanvas.hpp \
		$(DESTDIR)$(prefix)/include/rmg/wxcanvas.hpp

clean:
	-rm -r build

distclean: clean

uninstall:
	-rm -f -r $(DESTDIR)$(prefix)/share/rmg
	-rm -f $(DESTDIR)$(prefix)/lib/librmgbase.so
	-rm -f $(DESTDIR)$(prefix)/lib/librmgbase.so.$(VERSION_MAJOR)
	-rm -f $(DESTDIR)$(prefix)/lib/librmgbase.so.$(VERSION)
	-rm -f $(DESTDIR)$(prefix)/lib/librmgwindow.so
	-rm -f $(DESTDIR)$(prefix)/lib/librmgwindow.so.$(VERSION_MAJOR)
	-rm -f $(DESTDIR)$(prefix)/lib/librmgwindow.so.$(VERSION)
	-rm -f $(DESTDIR)$(prefix)/lib/librmgwx.so
	-rm -f $(DESTDIR)$(prefix)/lib/librmgwx.so.$(VERSION_MAJOR)
	-rm -f $(DESTDIR)$(prefix)/lib/librmgwx.so.$(VERSION)
	-rm -f -r $(DESTDIR)$(prefix)/include/rmg

.PHONY: all remote mpv-remote mpv-play install clean distclean uninstall
