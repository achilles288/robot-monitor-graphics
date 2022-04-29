all:
	@ mkdir -p build/deb
	@ mkdir -p build/bionic
	@ mkdir -p build/focal
	@ cp -r librmg build/deb
	@ cp -r ../../src build/deb/librmg
	@ cp -r ../../share build/deb/librmg
	@ cp -r build/deb/librmg build/focal
	@ cp -r build/deb/librmg build/bionic
	@ cp -r changelog build/deb/librmg/debian/changelog
	@ cp -r changelog.bionic build/bionic/librmg/debian/changelog
	@ cp -r changelog.focal build/focal/librmg/debian/changelog
