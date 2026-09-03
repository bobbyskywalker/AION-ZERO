# AION-ZERO
Firmware for AION ZERO, a DIY handheld game console built on the Raspberry Pi Pico 2 W.

## Dev
Clone the pico-sdk:
```bash
git clone https://github.com/raspberrypi/pico-sdk
```
then init the submodules inside the cloned repo directory:
```bash
git submodule update --init --recursive   
```

To generate compile commands for the project, create a symlink for the generated compile-commands.json in the root
```bash
ln -sf build/compile_commands.json compile_commands.json    
```

Alongside with zed's lsp settings:

```json
"lsp": {
		"clangd": {
			"binary": {
				"path": "/usr/bin/clangd",
				"arguments": [
					"--query-driver=/usr/bin/arm-none-eabi-g++"
				]
			}
		}
	}
```

To see what's getting printed via USB CDC, run:

```bash
screen /dev/ttyACM0 115200
```