.PHONY: build
all: build


clean:
	@echo "clean"
	rm -rf build

build:
	@echo "build"
	mkdir -p build || true
	cd build && cmake .. -DVMwareGemFireNative_ROOT="/usr/local/nativeclient" && cmake --build .
