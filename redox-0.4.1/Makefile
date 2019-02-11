# Configuration and variables
include mk/config.mk

all: build/harddrive.bin

live: build/livedisk.bin

iso: build/livedisk.iso

clean:
	cd cookbook && ./clean.sh
	cargo clean --manifest-path cookbook/pkgutils/Cargo.toml
	cargo clean --manifest-path installer/Cargo.toml
	cargo clean --manifest-path kernel/Cargo.toml
	cargo clean --manifest-path kernel/syscall/Cargo.toml
	cargo clean --manifest-path redoxfs/Cargo.toml
	-$(FUMOUNT) build/filesystem/ || true
	rm -rf build

distclean:
	make clean
	cd cookbook && ./unfetch.sh

pull:
	git pull --recurse-submodules
	git submodule sync --recursive
	git submodule update --recursive --init

update:
	cd cookbook && ./update.sh \
		"$$(cargo run --manifest-path ../installer/Cargo.toml -- --list-packages -c ../initfs.toml)" \
		"$$(cargo run --manifest-path ../installer/Cargo.toml -- --list-packages -c ../filesystem.toml)"
	cargo update --manifest-path cookbook/pkgutils/Cargo.toml
	cargo update --manifest-path installer/Cargo.toml
	cargo update --manifest-path kernel/Cargo.toml
	cargo update --manifest-path redoxfs/Cargo.toml

fetch:
	cd cookbook && ./fetch.sh \
		"$$(cargo run --manifest-path ../installer/Cargo.toml -- --list-packages -c ../initfs.toml)" \
		"$$(cargo run --manifest-path ../installer/Cargo.toml -- --list-packages -c ../filesystem.toml)"

# Emulation recipes
include mk/qemu.mk
include mk/bochs.mk
include mk/virtualbox.mk

# Kernel recipes
include mk/kernel.mk

# Filesystem recipes
include mk/initfs.mk
include mk/filesystem.mk

# Disk images
include mk/disk.mk

# Travis target
travis: FORCE
	make INSTALLER_FLAGS= build/harddrive.bin.gz build/livedisk.iso
	rm -rf build/travis
	mkdir build/travis
	mv build/harddrive.bin.gz build/travis/redox_$(TRAVIS_TAG).bin.gz
	mv build/livedisk.iso build/travis/redox_$(TRAVIS_TAG).iso
	cd build/travis && sha256sum -b redox_$(TRAVIS_TAG).bin.gz redox_$(TRAVIS_TAG).iso > SHA256SUM

# An empty target
FORCE:

# A method of creating a listing for any binary
%.list: %
	objdump -C -M intel -D $< > $@

# Wireshark
wireshark: FORCE
	wireshark build/network.pcap
