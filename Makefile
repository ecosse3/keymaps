USER = ecosse3
KEYBOARDS = sofle

# Keymap path
PATH_sofle = sofle

# Keyboard name
NAME_sofle = sofle

all: $(KEYBOARDS)

.PHONY: $(KEYBOARDS)
$(KEYBOARDS):
	# Init submodule
	git submodule update --init --recursive
	git submodule foreach git pull origin master
	git submodule foreach make git-submodule 


	# Cleanup old symlinks
	rm -rf qmk_firmware/keyboards/$(PATH_$@)/keymaps/$(USER)
	# rm -rf qmk_firmware/users/$(USER) # I don't have user yet

	# Add new symlinks
	# ln -s $(shell pwd)/user qmk_firmware/users/$(USER)
	ln -s $(shell pwd)/$@ qmk_firmware/keyboards/$(PATH_$@)/keymaps/$(USER)

	# Run lint check
	cd qmk_firmware; qmk lint -km $(USER) -kb $(NAME_$@) --strict

	# Run build
	make BUILD_DIR=$(shell pwd)/build -j1 -C qmk_firmware $(NAME_$@):$(USER)

	# Cleanup symlinks
	rm -rf qmk_firmware/keyboards/$(PATH_$@)/keymaps/$(USER)
	# rm -rf qmk_firmware/users/$(USER)

clean:
	rm -rf ./qmk_firmware/
	rm -rf ./build/
	rm -rf qmk_firmware/keyboards/$(PATH_sofle)/keymaps/$(USER)
	# rm -rf qmk_firmware/users/$(USER)
