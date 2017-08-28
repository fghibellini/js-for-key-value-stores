
export VEIGHT=/nix/store/mrv9b54w3b55swz9v2mdkzwk2hqkffsf-v8-5.4.232

hello-world : ./hello-world.cc
	bash ./build.sh
	#third_party/icu/libicu{uc,i18n},src/inspector/libinspector}.a \
